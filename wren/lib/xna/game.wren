

var SDL_WINDOWPOS_UNDEFINED = 0x1FFF0000 
var SDL_WINDOWPOS_CENTERED = 0x2FFF0000 
var SDL_WINDOW_FULLSCREEN = 0x00000001          /**< fullscreen window */
var SDL_WINDOW_OPENGL = 0x00000002              /**< window usable with OpenGL context */
var SDL_WINDOW_SHOWN = 0x00000004               /**< window is visible */
var SDL_WINDOW_HIDDEN = 0x00000008              /**< window is not visible */
var SDL_WINDOW_BORDERLESS = 0x00000010          /**< no window decoration */
var SDL_WINDOW_RESIZABLE = 0x00000020           /**< window can be resized */
var SDL_WINDOW_MINIMIZED = 0x00000040           /**< window is minimized */
var SDL_WINDOW_MAXIMIZED = 0x00000080           /**< window is maximized */
var SDL_WINDOW_INPUT_GRABBED = 0x00000100       /**< window has grabbed input focus */
var SDL_WINDOW_INPUT_FOCUS = 0x00000200         /**< window has input focus */
var SDL_WINDOW_MOUSE_FOCUS = 0x00000400         /**< window has mouse focus */
var SDL_WINDOW_FULLSCREEN_DESKTOP  = 0x00000001 | 0x00001000 
var SDL_WINDOW_FOREIGN = 0x00000800             /**< window not created by SDL */
var SDL_WINDOW_ALLOW_HIGHDPI = 0x00002000       /**< window should be created in high-DPI mode if supported.
//                                                  On macOS NSHighResolutionCapable must be set true in the
//                                                  application's Info.plist for this to have any effect. */
var SDL_WINDOW_MOUSE_CAPTURE = 0x00004000       /**< window has mouse captured (unrelated to INPUT_GRABBED) */
var SDL_WINDOW_ALWAYS_ON_TOP = 0x00008000       /**< window should always be above others */
var SDL_WINDOW_SKIP_TASKBAR  = 0x00010000       /**< window should not be added to the taskbar */
var SDL_WINDOW_UTILITY       = 0x00020000       /**< window should be treated as a utility window */
var SDL_WINDOW_TOOLTIP       = 0x00040000       /**< window should be treated as a tooltip */
var SDL_WINDOW_POPUP_MENU    = 0x00080000       /**< window should be treated as a popup menu */
var SDL_WINDOW_VULKAN        = 0x10000000       /**< window usable for Vulkan surface */

var SDL_INIT_TIMER          = 0x00000001 
var SDL_INIT_AUDIO          = 0x00000010 
var SDL_INIT_VIDEO          = 0x00000020            /**< SDL_INIT_VIDEO implies SDL_INIT_EVENTS */
var SDL_INIT_JOYSTICK       = 0x00000200            /**< SDL_INIT_JOYSTICK implies SDL_INIT_EVENTS */
var SDL_INIT_HAPTIC         = 0x00001000 
var SDL_INIT_GAMECONTROLLER = 0x00002000            /**< SDL_INIT_GAMECONTROLLER implies SDL_INIT_JOYSTICK */
var SDL_INIT_EVENTS         = 0x00004000 
var SDL_INIT_SENSOR         = 0x00008000 

var SDL_RENDERER_ACCELERATED = 0x00000002 

/**
 * Internal Implementation 
 */
foreign class GameImpl { 
    construct new(title, x, y, w, h, flags) {}
    foreign Update()
    foreign Render()
    foreign Tick()
    foreign Dispose()
    foreign HandleEvents()
    foreign Start()
    foreign Run()
}

/**
 * Base Game Class 
 */
class Game {
    construct new(title, x, y, w, h, flags) {
        _impl = GameImpl.new(title, x, y, w, h, flags)
    }

    Start() {
        _impl.Start()
    }

    Update() {
        _impl.Update()
    }

    Render() {
        _impl.Render()
    }

    Tick() {
        _impl.Tick()
    }

    Dispose() {
        _impl.Dispose()
    }

    HandleEvents() {
        _impl.HandleEvents()
    }

    Run() {
        _impl.Run()
    }
}