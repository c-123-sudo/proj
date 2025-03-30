#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <stdio.h>
#include <math.h> 
//gcc sdlsample.c -o sdlsample.exe -I"C:\msys64\mingw64\include" -L"C:\msys64\mingw64\lib" -lmingw32 -lSDL2main -lSDL2
//gcc sdl1.c -o sdl1.exe -I"C:\msys64\mingw64\include" -L"C:\msys64\mingw64\lib" -lmingw32 -lSDL2main -lSDL2


void  draw( SDL_Renderer* renderer, int cx,int cy,int z,int w)
{ if (z <= 0) return;
	 double p = M_PI / 180;
    

    int x = 500, y = 300;  // Original vector
    double length = sqrt(x*x + y*y);

    // Normalize and scale to 100
    double scale = w / length;
    x *= scale;
    y *= scale;

    int n = 6;
    while (n-->0) {
        double angle = 60 * n * p;

        // Rotation transformation
        double x1 = x * cos(angle) + y * sin(angle);
        double y1 = -x * sin(angle) + y * cos(angle);

        int x_final = cx + (int)x1;
        int y_final = cy + (int)y1;

        //printf("%d %d\n", x_final, y_final);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, cx, cy, x_final, y_final);
		SDL_RenderPresent(renderer);
		//printf("lol %d" ,z);
	
		SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return; // Exit drawing if window close requested
            }
        }
        
        SDL_RenderPresent(renderer);
       // SDL_Delay(10); // Small delay to see the drawing progress
        z--;
        // Recursively draw the next level
        draw(renderer, x_final, y_final, z, w/3);
		z++;
		
    }
	
	
	
	
}
int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 Color Display",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          1000, 1000, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    int running = 1;
    SDL_Event event;

    //while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Set render color to red (RGBA: 255, 0, 0, 255)
      //  SDL_SetRenderDrawColor(renderer, 255, 0, 255, 125);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer); // Fill the screen with the color
		
		
		
		
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		draw(renderer,500,500,5,300);
		
		SDL_Delay(5000);

         // Limit frame rate
   // }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

 /*
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <stdio.h>
#include <math.h> 

// A flag to track if drawing is complete
int drawingComplete = 0;

void draw(SDL_Renderer* renderer, int cx, int cy, int z, int w) {
    if (z <= 0) return;
    
    double p = M_PI / 180;
    
    int x = 500, y = 300;  // Original vector
    double length = sqrt(x*x + y*y);
    // Normalize and scale
    double scale = w / length;
    x *= scale;
    y *= scale;
    
    int n = 6;
    while (n-->0) {
        double angle = 60 * n * p;
        // Rotation transformation
        double x1 = x * cos(angle) + y * sin(angle);
        double y1 = -x * sin(angle) + y * cos(angle);
        int x_final = cx + (int)x1;
        int y_final = cy + (int)y1;
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, cx, cy, x_final, y_final);
        
        // Process events during drawing to prevent freezing
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return; // Exit drawing if window close requested
            }
        }
        
        SDL_RenderPresent(renderer);
        //SDL_Delay(10); // Small delay to see the drawing progress
        
        // Recursively draw the next level
        draw(renderer, x_final, y_final, z-1, w/2);
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    
    SDL_Window* window = SDL_CreateWindow("Fractal Drawing",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          800, 700, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    int running = 1;
    SDL_Event event;
    
    // Initial screen clear
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    
    // Draw the fractal
    draw(renderer, 400, 300, 6, 200);
    printf("Drawing complete. Click the window close button to exit.\n");
    drawingComplete = 1;
    
    // Keep window open until user closes it
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        SDL_Delay(100); // Reduce CPU usage while waiting
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}*/
