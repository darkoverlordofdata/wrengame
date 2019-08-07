// main.wren
import "some/tester" for Tester
import "lib/io/stream" for Stream
import "lib/io/file" for File
import "lib/io/path" for Path
import "lib/sdl" for Sdl
import "lib/sdl/window" for Window
import "lib/sdl/renderer" for Renderer
import "lib/xna/game" for Game, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOW_SHOWN


System.print("This is main.wren")

class Main {
    construct new() {}
    main() { 
	    System.print("Hello world")
        var file = Stream.new("wren/some/path.txt") 
        file.Write("some text") 
        file.Close()

        var other = Stream.new("wren/some/other.txt")
        var t = other.Read()
        other.Close()
        System.print("======================================\n")
        System.print(t)
        System.print("======================================\n")

        var path = Path.new(Path.Cwd)

        System.print(Path.Cwd)
        var cwd = path.ToString()
        System.print(cwd)
        System.print("Absolute %(Path.Absolute)")
        System.print("Relative %(Path.Relative)")
        System.print("Simple %(Path.Simple)")
        System.print("Type = %(Path.Type(cwd))")
        System.print("======================================\n")

        var game = Game.new("SdL Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                        600, 480, SDL_WINDOW_SHOWN )
        game.GameLoop()
        game.Dispose()
        
    }

}
