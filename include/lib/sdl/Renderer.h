#pragma once
#include <stdio.h>
#include <string.h>
#include "wren.h"
#include "SDL2/SDL.h"

/**
 *  sdl/renderer::Allocate
 */
static inline void sdl_renderer_Allocate(WrenVM* vm) 
{
    SDL_Renderer** renderer = (SDL_Renderer**)wrenSetSlotNewForeign(vm, 0, 0, sizeof(SDL_Renderer*));
    SDL_Window** window = (SDL_Window**)wrenGetSlotForeign(vm, 1);
    const int index = wrenGetSlotDouble(vm, 2);
    const Uint32 flags = wrenGetSlotDouble(vm, 3);
    *renderer  = SDL_CreateRenderer(*window, index, flags);

}
/**
 *  sdl/renderer::Finalize
 * 
 */
static inline void sdl_renderer_Finalize(void* data) 
{
    SDL_Renderer** renderer = data;
    SDL_DestroyRenderer(*renderer);
}

static inline void sdl_renderer_DrawColor(WrenVM* vm)
{
    SDL_Renderer** renderer = (SDL_Renderer**)wrenGetSlotForeign(vm, 0); 
    const int r = wrenGetSlotDouble(vm, 1);
    const int g = wrenGetSlotDouble(vm, 2);
    const int b = wrenGetSlotDouble(vm, 3);
    const int a = wrenGetSlotDouble(vm, 4);
    SDL_SetRenderDrawColor(*renderer, r, g, b, a);
    
}

static inline void sdl_renderer_Clear(WrenVM* vm)
{
    SDL_Renderer** renderer = (SDL_Renderer**)wrenGetSlotForeign(vm, 0); 
    SDL_RenderClear(*renderer);
}

static inline void sdl_renderer_Present(WrenVM* vm)
{
    SDL_Renderer** renderer = (SDL_Renderer**)wrenGetSlotForeign(vm, 0); 
    SDL_RenderPresent(*renderer);
}



