//Using SDL and standard IO
#include <stdio.h>

#include <SDL.h>
#include <GL/glew.h>

#include "debug.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

SDL_Window* window = nullptr;
SDL_GLContext gl_context;

void run() {
  u8 running = 1;
  while (running) {
    // Input
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);

      if (event.type == SDL_QUIT) {
        running = 0;
      }

      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            running = 0;
          break;

          case SDLK_r:
            clear_color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
          break;

          case SDLK_g:
            clear_color = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
          break;

          case SDLK_b:
            clear_color = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
          break;
        }
      }
    }

    // Rendering
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    show_debug_window(window);

    SDL_GL_SwapWindow(window);
  }
}

void setup() {
  if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    exit(1);
  }

  // GL context

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  window = SDL_CreateWindow("Codename Rogue",
                                        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                        SCREEN_WIDTH, SCREEN_HEIGHT,
                                        SDL_WINDOW_OPENGL);

  if (window == nullptr) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    exit(1);
  }

  gl_context = SDL_GL_CreateContext(window);

  SDL_GL_MakeCurrent(window, gl_context);
  SDL_GL_SetSwapInterval(1);

  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize OpenGL loader!\n");
    exit(1);
  }

  setup_debug(window, gl_context);
}

void cleanup() {
  cleanup_debug();

  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main(int argc, char* args[]) {
  setup();
  run();
  cleanup();

  return 0;
}
