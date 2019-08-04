// main.wren
import "some/tester" for Tester
import "lib/io/stream" for Stream
import "lib/io/file" for File
import "lib/io/path" for Path
import "lib/sdl" for Sdl
import "lib/sdl/window" for Window
import "lib/sdl/renderer" for Renderer


System.print("This is main.wren")

class Main {
    construct new() {}
    main() { 
	    System.print("Hello world")
        var file = Stream.Create("wren/some/path.txt") 
        file.Write("some text") 
        file.Close()

        var other = Stream.Create("wren/some/other.txt")
        var t = other.Read()
        other.Close()
        System.print("======================================\n")
        System.print(t)
        System.print("======================================\n")

        var path = Path.new(Path.Cwd)

        System.print(Path.Cwd)
        System.print(path.ToString())
        System.print("Absolute %(Path.Absolute)")
        System.print("Relative %(Path.Relative)")
        System.print("Simple %(Path.Simple)")
        System.print("Type = %(path.Type())")
        System.print("======================================\n")


        // Sdl.Init(Sdl.INIT_VIDEO) // | Sdl.INIT_EVENTS | Sdl.INIT_TIMER | Sdl.INIT_AUDIO)
        // var window = Window.Create("SDL Demo", Window.WINDOWPOS_CENTERED, Window.WINDOWPOS_CENTERED,
        //                                 640, 480, Window.WINDOW_SHOWN)
        // // var window = Window.Create("SDL Demo", -1, -1, 640, 480, Window.WINDOW_SHOWN)

        // if (window == null) {
        //     System.print("Could not be opened")
        // } else {
        //     Sdl.Delay(3000)
        // }
        // window.Close()
        // Sdl.Quit()
        
    }

}
