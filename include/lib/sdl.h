#pragma once

#include "sdl/Window.h"
#include "sdl/Renderer.h"

static inline void logSDLError(const char* msg)
{
    printf("%s error: %s", msg, SDL_GetError());
}

/**
 *  sdl/sdl::Init
 * 
 */
static inline void sdl_Init(WrenVM* vm) 
{
    long flags = (long)wrenGetSlotDouble(vm, 1);

    if (SDL_Init(flags) < 0) {
        logSDLError("Init SDL");
    }
}

/**
 *  sdl/sdl::Delay
 * 
 */
static inline void sdl_Delay(WrenVM* vm) 
{
    long ms = (long)wrenGetSlotDouble(vm, 1);
    SDL_Delay(ms);
}

/**
 *  sdl/sdl::Quit
 * 
 */
static inline void sdl_Quit(WrenVM* vm) 
{
    SDL_Quit();
}