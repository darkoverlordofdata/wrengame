#include <stdio.h>
#include <string.h>
#include "dark.h"
#include "wren.h"
#include "vm/config.h"
#include "SDL2/SDL.h"

#include "map.h"


int main(int argc, const char* argv[])
{

    Map* d;
    char buf[512];
    int i;

    d = MapNew();

    Insert(d, "foo", "hello world");
    puts(Search(d, "foo"));
    Insert(d, "foo", "hello world2");
    puts(Search(d, "foo"));
    Delete(d, "foo");
    puts(Search(d, "foo"));
    Delete(d, "foo");
    assert(Search(d, "foo") == 0);
    Delete(d, "foo");

    for (i = 0; i < 10000; i++) {
        sprintf(buf, "%d", i);
        Insert(d, buf, buf);
    }

    Dispose(d);
    return 0;

    // Game* game = GameNew("SdL Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
    //                     600, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );

    Game* game = new(Game, "SdL Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                        600, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );
    // game->Start(game);
    Run(game);
    Dispose(game);

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
