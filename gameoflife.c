#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define p  5
#define h1 100
#include <stdbool.h>
#define w1 100
//gcc gameoflife.c -o gameoflife.exe -I"C:\msys64\mingw64\include" -L"C:\msys64\mingw64\lib" -lmingw32 -lSDL2main -lSDL2
float a[h1][w1];
   int ar[h1][w1];
   int ar2[h1][w1];
int rand_lim(int limit) {
/* return a random number between 0 and limit inclusive.
 */

    int divisor = RAND_MAX/(limit+1);
    int retval;

    do { 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}
bool exist(int a,int b){ 
int poo[3]={0,1,2};
int x=0;
int m=a;
int n=b;
int flag,flag2=0;
for(int i=0;i<=2;i++)
 { 

for(int j=0;j<=2;j++)
	 { 
 m=a;
 n=b;
  if (poo[j]==0 )
	   m=m-1; 
	  else if(poo[j]==1)
		 m=m+0;
	  else m=m+1;
	  if (poo[i]==0 )
	   n=n-1; 
	  else if(poo[i]==1)
		 n=n+0;
	  else n=n+1;
	
	  if(poo[i]==1 && poo[j]==1 )
	  continue;
  
   if(m< 0) m= h1 - 1;
            if(m >= h1) m = 0;
            if(n < 0) n = w1 - 1;
            if(n >= w1) n = 0;
  if(ar[m][n]==1)
    x++;

 
 }
 } 
  
 if(ar[a][b]==1){
  switch(x){
	  case 0:
	   case 1:
	  
	  return false;
	  
	  break;
	 
	  case 2:
      case 3:
      return true;
     case 4:
     case 5:
case 6:
case 7:
case 8:
return false;	 
	  
  }
 }
 
 if(ar[a][b]==0){
  switch(x){
	  case 0:
	  case 1:
	    case 2:
	  return false;
	  break;
	  
	
      case 3:
      return true;
     case 4:
     case 5:
case 6:
case 7:
case 8:
return false;	 
	  
  }
 }
  
  


}
int main(int argc,  char* argv[])
{
	
if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Game of life",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          600, 600, SDL_WINDOW_SHOWN);
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
	SDL_Rect rect;
	  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);
	srand((unsigned int)time(NULL));
	for(int i=0;i<h1;i++)
	{
		for(int j=0;j<w1;j++)
		{			
			
			ar[i][j]=rand_lim(1);

         	
	rect.x=j*p;
	rect.y=i*p;
	rect.h=p;
	rect.w=p;

	SDL_SetRenderDrawColor(renderer,255, 255, 255,(int)(ar[i][j] * 255));
	
    SDL_RenderFillRect( renderer,&rect);
	}
		
		
	}
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);
	int n=1000;
	 SDL_Event e;
    bool quit = false;
 while(n-- > 0 && !quit) {
        // Handle events
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                quit = true;
                break;
            }
        }
	  // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    // SDL_RenderClear(renderer);
	
	for(int i=0;i<h1;i++)
	
		for(int j=0;j<w1;j++)				
		{ar2[i][j]=exist(i,j)?1:0;
		
	    
		}
	
 	for(int i=0;i<h1;i++)
	{
		for(int j=0;j<w1;j++)
		{			
			
	rect.x=j*p;
	rect.y=i*p;
	rect.h=p;
	rect.w=p;
	int al=0;
	if (ar2[i][j]==1)
		al=255;
	SDL_SetRenderDrawColor(renderer,255, 255, 255,al);
	
    SDL_RenderFillRect( renderer,&rect);
	}
		
	}
	SDL_RenderPresent(renderer);
 
   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);
		
	for(int i=0;i<h1;i++)
	
		for(int j=0;j<w1;j++)	
	     ar[i][j]=ar2[i][j];
	 SDL_Delay(50);
 }
 
   
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}	
