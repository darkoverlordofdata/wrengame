#pragma once
#include <stdio.h>
#include <string.h>
#include "wren.h"
#include "SDL2/SDL.h"

static inline void logSDLError(const char* msg)
{
    printf("%s error: %s", msg, SDL_GetError());
}

/**
 *  sdl/sdl::Allocate
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
 *  sdl/sdl::Finalize
 * 
 */
static inline void sdl_window_Finalize(void* data) 
{ 
    printf("window finalize %x\n", (int)data);
    SDL_DestroyWindow((SDL_Window*) data);
    printf("1close: %s\n", SDL_GetError());
    SDL_Quit();
    printf("1quit: %s\n", SDL_GetError());
}

/**
 *  io/file::Close
 * 
 */
static inline void sdl_window_Close(WrenVM* vm) 
{ 
    SDL_Window** window = (SDL_Window**)wrenGetSlotForeign(vm, 0); 
    printf("window close %x\n", (Uint32)*window);
    SDL_DestroyWindow((SDL_Window*) window);
    printf("2close: %s\n", SDL_GetError());
}

/**
 *  sdl/sdl::Init
 * 
 */
static inline void sdl_sdl_Init(WrenVM* vm) 
{
    long flags = (long)wrenGetSlotDouble(vm, 1);

    printf("SDL_Init - %x\n", (Uint32)flags); 
    if (SDL_Init(flags) < 0) {
        logSDLError("Init SDL");
    }
}

/**
 *  sdl/sdl::Delay
 * 
 */
static inline void sdl_sdl_Delay(WrenVM* vm) 
{
    long ms = (long)wrenGetSlotDouble(vm, 1);
    SDL_Delay(ms);
    printf("%s\n", SDL_GetError());

}

/**
 *  sdl/sdl::Quit
 * 
 */
static inline void sdl_sdl_Quit(WrenVM* vm) 
{
    SDL_Quit();

}