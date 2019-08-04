#pragma once
#include <stdio.h>
#include <string.h>
#include <wren.h>
#include "lib/io.h"
#include "lib/sdl.h"
/**
 * wren_BindForeignClass
 */
static inline WrenForeignClassMethods 
wren_BindForeignClass( WrenVM* vm, 
                        const char* module, 
                        const char* className) 
{
    WrenForeignClassMethods methods;
    methods.allocate = nullptr; 
    methods.finalize = nullptr; 

    if (strcmp(module, "lib/io/path") == 0) 
    {
        if (strcmp(className, "Path") == 0) 
        { 
            methods.allocate = io_path_Allocate; 
            methods.finalize = io_path_Finalize; 
            return methods; 
        } 
    }

    if (strcmp(module, "lib/io/stream") == 0) 
    {
        if (strcmp(className, "Stream") == 0) 
        { 
            methods.allocate = io_stream_Allocate; 
            methods.finalize = io_stream_Finalize; 
            return methods; 
        } 
    }

    if (strcmp(module, "lib/sdl/window") == 0)
    {
        if (strcmp(className, "Window") == 0)
        {
            methods.allocate = sdl_window_Allocate; 
            methods.finalize = sdl_window_Finalize; 
            return methods; 
        }
    }

    if (strcmp(module, "lib/sdl/renderer") == 0)
    {
        if (strcmp(className, "Renderer") == 0)
        {
            methods.allocate = sdl_renderer_Allocate; 
            methods.finalize = sdl_renderer_Finalize; 
            return methods; 
        }
    }
    return methods; 
}

