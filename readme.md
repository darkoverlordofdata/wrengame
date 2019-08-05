# playing with wrenscript

it works in emscripten, too.




link_directories( ${CMAKE_SOURCE_DIR}/lib/ )

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

