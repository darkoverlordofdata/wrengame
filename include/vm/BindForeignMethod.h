#pragma once
#include <stdio.h>
#include <string.h>
#include <wren.h>
#include "lib/io/File.h"
#include "lib/sdl/Sdl.h"


/**
 * wren_BindForeignMethod
 */
static inline WrenForeignMethodFn 
wren_BindForeignMethod( WrenVM* vm, 
                        const char* module, 
                        const char* className, 
                        bool isStatic, 
                        const char* signature) 
{

    if (strcmp(module, "lib/io") == 0) 
    {
        if (strcmp(className, "File") == 0) 
        { 
            if (!isStatic && strcmp(signature, "Write(_)") == 0) 
            { 
                return io_file_Write; 
            }

            if (!isStatic && strcmp(signature, "Close()") == 0) 
            { 
                return io_file_Close; 
            } 
        }
    }


    if (strcmp(module, "lib/sdl") == 0) 
    {
        if (strcmp(className, "Sdl") == 0) 
        { 
            if (isStatic && strcmp(signature, "Init(_)") == 0) 
            { 
                return sdl_sdl_Init;
            }
            if (isStatic && strcmp(signature, "Delay(_)") == 0) 
            { 
                return sdl_sdl_Delay;
            }
            if (isStatic && strcmp(signature, "Quit()") == 0) 
            { 
                return sdl_sdl_Quit;
            }
        }

        if (strcmp(className, "Window") == 0) 
        { 
            if (!isStatic && strcmp(signature, "Close()") == 0) 
            { 
                return sdl_window_Close;
            }
        }
    }

    // Unknown method.
    return NULL; 
    
}
