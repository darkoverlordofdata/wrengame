import "lib/xna/game" for Game, GameImpl,
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOW_SHOWN


class Main {
    construct new() {}
    main() { 
	    System.print("Hello world")
        System.print("======================================\n")

        var game = Game.new("SdL Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                        600, 480, SDL_WINDOW_SHOWN )
                        
        // game.Start()
        game.Run()
        game.Dispose()

        // Game* game = GameNew("SdL Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        //                     600, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );
        // game->Start(game);
        // game->Rum(game);
        // game->Dispose(game);

    }

}
