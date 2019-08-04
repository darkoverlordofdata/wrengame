foreign class Sdl { 

    static INIT_TIMER          { 0x00000001 }
    static INIT_AUDIO          { 0x00000010 }
    static INIT_VIDEO          { 0x00000020 }  /**< SDL_INIT_VIDEO implies SDL_INIT_EVENTS */
    static INIT_JOYSTICK       { 0x00000200 }  /**< SDL_INIT_JOYSTICK implies SDL_INIT_EVENTS */
    static INIT_HAPTIC         { 0x00001000 }
    static INIT_GAMECONTROLLER { 0x00002000 }  /**< SDL_INIT_GAMECONTROLLER implies SDL_INIT_JOYSTICK */
    static INIT_EVENTS         { 0x00004000 }
    static INIT_SENSOR         { 0x00008000 }

    static RENDERER_ACCELERATED { 0x00000002 }
    foreign static Init(flags) 
    foreign static Delay(ms)
    foreign static Quit()
}

