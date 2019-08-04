//Using SDL and standard IO
#include <stdio.h>

#include <SDL.h>
#include <GL/glew.h>

#include "rogue.h"

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void run() {
  u8 running = 1;
  while (running) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = 0;
      }

      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            running = 0;
          break;

          case SDLK_r:
            glClearColor(1.0, 0.0, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            SDL_GL_SwapWindow(rogue::window);
          break;

          case SDLK_g:
            glClearColor(0.0, 1.0, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            SDL_GL_SwapWindow(rogue::window);
          break;

          case SDLK_b:
            glClearColor(0.0, 0.0, 1.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            SDL_GL_SwapWindow(rogue::window);
          break;
        }
      }

    }
  }
}

int main( int argc, char* args[] ) {
  if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  rogue::window = SDL_CreateWindow("Codename Rogue",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SCREEN_WIDTH,
                                   SCREEN_HEIGHT,
                                   SDL_WINDOW_OPENGL);

  if (rogue::window == nullptr) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                      SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  auto gl_context = SDL_GL_CreateContext(rogue::window);

  SDL_GL_SetSwapInterval(1);

  run();

  // Destroy window
  SDL_DestroyWindow(rogue::window);

  //Quit SDL subsystems
  SDL_Quit();

  return 0;
}
