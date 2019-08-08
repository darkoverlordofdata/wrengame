#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _POSIX_C_SOURCE	199309L
#include <time.h>
#include <unistd.h>
#include "dark.h"
#include "wren.h"
#include "vm/config.h"
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#if __EMSCRIPTEN__
#include <emscripten/emscripten.h>
static inline char* strdup(const char* s) {
    size_t len = strlen(s)+1;
    void* new = malloc(len);
    if (new == NULL) return NULL;
    return (char*)memcpy(new, s, len);
}
#else
#define GLEW_STATIC
#include <GL/glew.h>
#endif
// #include "tglm.h"


// 100,149,237,255
#define bgd_r 0.392156f
#define bgd_g 0.584313f
#define bgd_b 0.929411f
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 0
#endif

#define period_den 1000000000L

static float time_factor = 0.000000001f;
static float time_fps = 0.01667f;
static float MS_PER_UPDATE = 0.01667f;

static inline long getNanos(){
    static struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    long result = (long)ts.tv_sec * period_den + ts.tv_nsec;
    return result;
}
/**
 * this wont work for nanosec
 * the double64 format holds 16 digits.
 * we need 19 digits to store a UTC time to nanoseconds.
 * 16 digits can only express it to millisconds
 * 
 * have to save time as a timespec struct, and compute the diff between 2 structs for delta
 */
static inline double getCurrentTime(){
    static struct timespec ts;
    static double multiplier = 1.0   / (1.e9);
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return  ts.tv_sec + (ts.tv_nsec * multiplier);
}

typedef struct Game Game;
typedef void (*GameFn)(Game* game);
static void Game_Update(Game*);
static void Game_Render(Game*);
static void Game_Tick(Game*);
static void Game_Dispose(Game*);
static void Game_HandleEvents(Game*);
static void Game_Run(Game*);

/**
 * The game object
 */
typedef struct Game
{
    GameFn Update;
    GameFn Render;
    GameFn Tick;
    GameFn Dispose;
    GameFn HandleEvents;
    GameFn Run;
    GameFn Start;
    SDL_Window *window;
    SDL_GLContext context;
    char* title;
    int x;
    int y;
    int h;
    int w;
    Uint32 flags;
    bool running;
    int sdlVersion;
    int gl_major_version;
    int gl_minor_version;
    int ticks;
    int fps;
    float factor;
    float delta;
    float elapsed;
    float current;
    float previous;
    float lag;
    long mark1;
    long mark2;
    int mouseX;
    int mouseY;
    bool mouseDown;
    bool *keys;
} Game;

static inline void LogSDLError(const char* msg)
{
    printf("%s error: %s", msg, SDL_GetError());
}

/**
 * Update
 */
static inline void Game_Update(Game* game){
    if (game->keys[SDLK_ESCAPE]) {
        game->running = false;
    }
}

/**
 * Render
 */
static inline void Game_Render(Game* game) {
    glClearColor(bgd_r, bgd_g, bgd_b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(game->window);
}

/**
 * HandleEvents
 */
static inline void Game_HandleEvents(Game* game) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            game->running = false;
            return;
            break;
        case SDL_KEYDOWN: 
            game->keys[ event.key.keysym.sym & 0xff ] = true;
            break;
        case SDL_KEYUP:   
            game->keys[ event.key.keysym.sym & 0xff ] = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            game->mouseDown = true;
            break;
        case SDL_MOUSEBUTTONUP:
            game->mouseDown = false;
            break;
        case SDL_MOUSEMOTION:
            game->mouseX = event.motion.x;
            game->mouseY = event.motion.y;
            break;

        }
    }
}


static inline void Game_Start(Game* game) {
    printf("Game::Start\n");
    game->running = true;
    game->factor = time_factor;
    // game->mark1 = getNanos();
    game->previous = getCurrentTime();
    game->lag = 0.0f;

    struct timespec t_info;
    static struct timespec res_info = {.tv_nsec = 0, .tv_sec = 0};
    static double multiplier;
    clock_getres(CLOCK_MONOTONIC, &res_info);
    multiplier = 1.0   / (1.e9 / res_info.tv_nsec);    
    multiplier = 1.0   / (1.e9);    

    printf("mul = %d\n", res_info.tv_nsec);
    clock_gettime(CLOCK_MONOTONIC, &t_info);
    long ii;
    for (ii = 0; ii < 1000000000; ii++);
    for (ii = 0; ii < 1000000000; ii++);
    for (ii = 0; ii < 1000000000; ii++);
    for (ii = 0; ii < 1000000000; ii++);
    for (ii = 0; ii < 1000000000; ii++);
    double tt = getCurrentTime();
    printf("%20.10f, %20.10f\n", t_info.tv_sec + (t_info.tv_nsec * multiplier), tt);

}
/**
 * Tick
 */
static inline void Game_Tick(Game* game) {

    game->current = getCurrentTime();
    game->elapsed = game->current - game->previous;
    game->previous = game->current;
    game->lag += game->elapsed;
    // printf("%f - %f - %f\n", game->current, game->previous, game->lag);
    game->HandleEvents(game);
    game->Update(game);
    while (game->lag >= MS_PER_UPDATE) {
        game->Update(game);
        game->lag -= MS_PER_UPDATE;
        // printf("%1.10f\n", game->lag);
    }
    game->Render(game);

    // game->mark2 = getNanos();
    // game->delta += (double)(game->mark2 - game->mark1) * game->factor;
    // game->ticks += 1;
    // game->HandleEvents(game);
    // game->mark1 = game->mark2;
    // if (game->delta >= time_fps) {
    //     long mark1 = getNanos();
    //     game->Update(game);
    //     game->Render(game);
    //     long mark2 = getNanos();
    //     printf("%1.10f\n", game->delta);
    //     game->ticks = 0;
    //     game->delta = 0.0f;
        
    // } else { 
    //     /* sleep until the end of this frame  */
    //     float nsec = time_fps - game->delta;
    //     // printf("%1.10f\n", nsec);
    //     static struct timespec wait;
    //     static struct timespec rem;
    //     static struct timespec retry;
    //     wait.tv_sec = 0;
    //     wait.tv_nsec = nsec * (float)period_den;
    //     if (nanosleep(&wait, &rem)) {
    //         // printf("rem = %d\n", rem.tv_nsec);
    //         nanosleep(rem, retry);

    //     }

    // }
}

/**
 * Dispose
 */
static inline void Game_Dispose(Game* game) {
    SDL_DestroyWindow(game->window);
    free(game->title);
    free(game->keys);
    free(game);
    IMG_Quit();
    SDL_Quit();
}

/**
 * GameLoop
 */
static inline void Game_Run(Game* game) {
#if __EMSCRIPTEN__
    emscripten_set_main_loop_arg((em_arg_callback_func)game->Tick, (void*)game, -1, 1);
#else
    while (true) {
        game->Tick(game);
        if (!game->running) break;
    }
#endif
}


/**
 * New Game
 */
static inline Game* GameNew(const char* title, int x, int y, int w, int h, int flags)
{
    if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_AUDIO ) < 0) {
        LogSDLError("Unable to initialize SDL2");
        return nullptr;
    }
    SDL_version sversion;
    SDL_GetVersion(&sversion);
    int version = 100 * sversion.major + 10 * sversion.minor + sversion.patch;
    if (version <= 204) {
        printf("Please use SDL 2.0.5 or higher.\n");
    } else {
        printf("Using SDL Vesion %d.%d.%d\n", sversion.major, sversion.minor, sversion.patch);
    }

    Game* game = malloc(sizeof(Game));
    game->title = strdup(title);
    game->x = x;
    game->y = y;
    game->w = w;
    game->h = h;
    game->flags = flags;
    game->running = false;
    game->mark1 = getNanos();
    game->keys = calloc(256, sizeof(bool));
    game->sdlVersion = version;
    game->gl_major_version = 3;
    #ifdef __EMSCRIPTEN__
    game->gl_minor_version = 0;
    #else
    game->gl_minor_version = 3;
    #endif

    /* Request opengl 3.3 context.*/
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, game->gl_major_version);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, game->gl_minor_version);

    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    game->window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );
    game->context = SDL_GL_CreateContext(game->window);

    #ifdef __EMSCRIPTEN__
    const int img_flags = IMG_INIT_PNG;
    #else
    const int img_flags = IMG_INIT_PNG | IMG_INIT_JPG;
    #endif
    if (IMG_Init(img_flags) != img_flags) { 
        LogSDLError("Init image");
    }
    TTF_Init();
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        LogSDLError("Init mixer");
    }

    #ifndef __EMSCRIPTEN__
    // Load OpenGL EntryPoints for desktop
    glewExperimental = GL_TRUE;
    glewInit();
    glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.
    #endif

    // OpenGL configuration
    glViewport(0, 0, game->w, game->h);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // wrire up the methods
    game->Update        = Game_Update;
    game->Render        = Game_Render;
    game->Tick          = Game_Tick;
    game->HandleEvents  = Game_HandleEvents;
    game->Dispose       = Game_Dispose;
    game->Run           = Game_Run;
    game->Start         = Game_Start;
    return game;
}

//////////////////////////////////////////////////////////////////////////////////
///////  wren bindings 
//////////////////////////////////////////////////////////////////////////////////

/**
 *  xna/game::Allocate
 */
static inline void xna_game_Allocate(WrenVM* vm) 
{
    Game** game = (Game**)wrenSetSlotNewForeign(vm, 0, 0, sizeof(Game*));
    const char* title = wrenGetSlotString(vm, 1); 
    const int x = wrenGetSlotDouble(vm, 2);
    const int y = wrenGetSlotDouble(vm, 3);
    const int w = wrenGetSlotDouble(vm, 4);
    const int h = wrenGetSlotDouble(vm, 5);
    const int flags = wrenGetSlotDouble(vm, 6);

    *game = GameNew(title, x, y, w, h, flags); 
}

/**
 *  xna/game::Finalize
 */
static inline void xna_game_Finalize(void* data) 
{
    Game** game = (Game**)data;
    if (*game != nullptr) {
        Game_Dispose(*game);
    }
}

/**
 *  xna/game::Update
 */
static inline void xna_game_Update(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    Game_Update(*game);
}

/**
 *  xna/game::Render
 */
static inline void xna_game_Render(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    Game_Render(*game);
}

/**
 *  xna/game::Tick
 */
static inline void xna_game_Tick(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    Game_Tick(*game);
}

/**
 *  xna/game::Dispose
 */
static inline void xna_game_Dispose(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    Game_Dispose(*game);
    *game = nullptr;
}
/**
 *  xna/game::HandleEvents
 */
static inline void xna_game_HandleEvents(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    Game_HandleEvents(*game);
}

/**
 *  xna/game::Start
 */
static inline void xna_game_Start(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    Game_Start(*game);
}

/**
 *  xna/game::Run
 */
static inline void xna_game_Run(WrenVM* vm) 
{
    Game** game = (Game**)wrenGetSlotForeign(vm, 0);
    Game_Run(*game);
}
