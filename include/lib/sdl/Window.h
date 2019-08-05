#pragma once
#include <stdio.h>
#include <string.h>
#include "wren.h"
#include "SDL2/SDL.h"


/**
 *  sdl/window::Allocate
 */
static inline void sdl_window_Allocate(WrenVM* vm) 
{ 
    SDL_Window** window = (SDL_Window**)wrenSetSlotNewForeign(vm, 0, 0, sizeof(SDL_Window*));
    const char* title = wrenGetSlotString(vm, 1); 
    const int x = wrenGetSlotDouble(vm, 2);
    const int y = wrenGetSlotDouble(vm, 3);
    const int w = wrenGetSlotDouble(vm, 4);
    const int h = wrenGetSlotDouble(vm, 5);
    const Uint32 flags = wrenGetSlotDouble(vm, 6);
    printf("%s, %d, %d, %d, %d, %x\n", title, x, y, w, h, flags);
    *window = SDL_CreateWindow(title, x, y, w, h, flags);
    printf("create %x - %s\n", (Uint32)*window, SDL_GetError());
}

/**
 *  sdl/window::Finalize
 * 
 */
static inline void sdl_window_Finalize(void* data) 
{ 
    SDL_Window** window = data;
    if (*window != nullptr) {
        SDL_DestroyWindow((SDL_Window**) *window);
    }
}

/**
 *  io/window::Close
 * 
 */
static inline void sdl_window_Close(WrenVM* vm) 
{ 
    SDL_Window** window = (SDL_Window**)wrenGetSlotForeign(vm, 0); 
    SDL_DestroyWindow((SDL_Window*) window);
    *window = nullptr;
}

