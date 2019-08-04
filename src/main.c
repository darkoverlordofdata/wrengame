#include <stdio.h>
#include <string.h>
#include "dark.h"
#include "wren.h"
#include "vm/Config.h"
#include "vm/BindForeignClass.h"
#include "vm/BindForeignMethod.h"
#include "SDL2/SDL.h"

int main(int argc, const char* argv[])
{
    // if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    // }
    // char* title = "SdL Demo";
    // int x = SDL_WINDOWPOS_UNDEFINED;
    // int y = SDL_WINDOWPOS_UNDEFINED;
    // int h = 480;
    // int w = 640;
    // Uint32 flags = SDL_WINDOW_SHOWN;
    // SDL_Window* window = SDL_CreateWindow(title, x, y, w, h, flags);

    // SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // while (true)
    // {
        
    //     SDL_Event event;
    //     if (SDL_PollEvent(&event)) {
    //         if (event.type == SDL_QUIT)
    //             break;
    //     }
    //     SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
    //     SDL_RenderClear(renderer);
    //     SDL_RenderPresent(renderer);
    // }
    // SDL_DestroyRenderer(renderer);
    // printf("renderer - %s\n", SDL_GetError());
    // SDL_DestroyWindow(window);
    // printf("window - %s\n", SDL_GetError());
    // SDL_Quit();
    // return 0;

    WrenConfiguration config;
    wrenInitConfiguration(&config);
    config.loadModuleFn         = wren_LoadModule;
    config.writeFn              = wren_Write;
    config.errorFn              = wren_Error;
    config.bindForeignClassFn   = wren_BindForeignClass;
    config.bindForeignMethodFn  = wren_BindForeignMethod;
    
    WrenVM* vm = wrenNewVM(&config);

    const char* bootstrap = "import \"main\" for Main\nvar app = Main.new()\napp.main()\n";

    WrenInterpretResult result = wrenInterpret(vm, "wrengame", bootstrap);

    switch (result) {
    case WREN_RESULT_SUCCESS:
        fputs("Ok\n", stdout);
        break;
    case WREN_RESULT_COMPILE_ERROR:
        fputs("wrenInterpret(): ", stdout);
        fputs("compile error\n", stdout);
        break;
    case WREN_RESULT_RUNTIME_ERROR:
        fputs("wrenInterpret(): ", stdout);
        fputs("runtime error\n", stdout);
        break;
    }

    wrenFreeVM(vm);
    return 0;
}
