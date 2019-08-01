// main.wren
import "some/tester" for Tester
import "lib/io" for File
import "lib/sdl" for Sdl, Window


System.print("This is main.wren")

class Main {
    construct new() {}
    main() { 
	    System.print("Hello world")
        var file = File.Create("wren/some/path.txt") 
        file.Write("some text") 
        file.Close()

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
