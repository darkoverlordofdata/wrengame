
foreign class Window { 

    static WINDOWPOS_UNDEFINED { 0x1FFF0000 }
    static WINDOWPOS_CENTERED { 0x2FFF0000 }
    static WINDOW_FULLSCREEN { 0x00000001 }         /**< fullscreen window */
    static WINDOW_OPENGL { 0x00000002 }             /**< window usable with OpenGL context */
    static WINDOW_SHOWN { 0x00000004 }              /**< window is visible */
    static WINDOW_HIDDEN { 0x00000008 }             /**< window is not visible */
    static WINDOW_BORDERLESS { 0x00000010 }         /**< no window decoration */
    static WINDOW_RESIZABLE { 0x00000020 }          /**< window can be resized */
    static WINDOW_MINIMIZED { 0x00000040 }          /**< window is minimized */
    static WINDOW_MAXIMIZED { 0x00000080 }          /**< window is maximized */
    static WINDOW_INPUT_GRABBED { 0x00000100 }      /**< window has grabbed input focus */
    static WINDOW_INPUT_FOCUS { 0x00000200 }        /**< window has input focus */
    static WINDOW_MOUSE_FOCUS { 0x00000400 }        /**< window has mouse focus */
    static WINDOW_FULLSCREEN_DESKTOP  { 0x00000001 | 0x00001000 }
    static WINDOW_FOREIGN { 0x00000800 }            /**< window not created by SDL */
    static WINDOW_ALLOW_HIGHDPI { 0x00002000 }      /**< window should be created in high-DPI mode if supported.
    //                                                  On macOS NSHighResolutionCapable must be set true in the
    //                                                  application's Info.plist for this to have any effect. */
    static WINDOW_MOUSE_CAPTURE { 0x00004000 }      /**< window has mouse captured (unrelated to INPUT_GRABBED) */
    static WINDOW_ALWAYS_ON_TOP { 0x00008000 }      /**< window should always be above others */
    static WINDOW_SKIP_TASKBAR  { 0x00010000 }      /**< window should not be added to the taskbar */
    static WINDOW_UTILITY       { 0x00020000 }      /**< window should be treated as a utility window */
    static WINDOW_TOOLTIP       { 0x00040000 }      /**< window should be treated as a tooltip */
    static WINDOW_POPUP_MENU    { 0x00080000 }      /**< window should be treated as a popup menu */
    static WINDOW_VULKAN        { 0x10000000 }      /**< window usable for Vulkan surface */

    construct new(title, x, y, w, h, flags) {}
    foreign Close()

}