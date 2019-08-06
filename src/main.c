#include <stdio.h>
#include <string.h>
#include "dark.h"
#include "wren.h"
#include "vm/config.h"
#include "SDL2/SDL.h"
#include "game.h"

int main(int argc, const char* argv[])
{
    Game* game = GameNew("SdL Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                        600, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );
    game->GameLoop(game);
    game->Dispose(game);
    return 0;

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
