#pragma once

#include <SDL.h>

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#include "types.h"

void setup_debug(SDL_Window*, SDL_GLContext);
void cleanup_debug();

void show_debug_window(SDL_Window*);
