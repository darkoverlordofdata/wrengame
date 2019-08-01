#pragma once
#include <stdio.h>
#include <string.h>
#include <wren.h>
#include "lib/io/File.h"
#include "lib/sdl/Sdl.h"
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

    if (strcmp(module, "lib/io") == 0) 
    {
        if (strcmp(className, "File") == 0) 
        { 
            methods.allocate = io_file_Allocate; 
            methods.finalize = io_file_Finalize; 
            return methods; 
        } 
    }

    if (strcmp(module, "lib/sdl") == 0)
    {
        if (strcmp(className, "Window") == 0)
        {
            methods.allocate = sdl_window_Allocate; 
            methods.finalize = sdl_window_Finalize; 
            return methods; 
        }
    }

    return methods; 
}

