//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

#include "rogue.h"

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main( int argc, char* args[] ) {
  //Initialize SDL
  if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
  } else {
    //Create window
    rogue::window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( rogue::window == NULL ) {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }

    else {
      //Get window surface
      SDL_Surface* screenSurface = SDL_GetWindowSurface(rogue::window);

      //Fill the surface white
      SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

      //Update the surface
      SDL_UpdateWindowSurface(rogue::window);

      //Wait two seconds
      SDL_Delay(2000);
    }
  }

  //Destroy window
  SDL_DestroyWindow(rogue::window);

  //Quit SDL subsystems
  SDL_Quit();

  return 0;
}
