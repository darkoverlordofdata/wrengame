#include <stdio.h>
#include <string.h>
#include "dark.h"
#include "wren.h"
#include "vm/config.h"
#include "SDL2/SDL.h"
#if __EMSCRIPTEN__
#include <emscripten/emscripten.h>
char* strdup(const char* s) {
    size_t len = strlen(s)+1;
    void* new = malloc(len);
    if (new == NULL) return NULL;
    return (char*)memcpy(new, s, len);
}
#endif
// #include "tglm.h"

typedef struct Game Game;
typedef void (*GameFn)(Game* game);
static void Game_Update(Game*);
static void Game_Render(Game*);
static void Game_Tick(Game*);
static void Game_Dispose(Game*);
static void Game_HandleEvents(Game*);
static void Game_GameLoop(Game*);

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
    GameFn GameLoop;
    SDL_Window *window;
    SDL_Renderer *renderer;
    char* title;
    int x;
    int y;
    int h;
    int w;
    Uint32 flags;
    bool running;
    int sdlVersion;
    int ticks;
    int fps;
    float factor;
    float delta;
    float mark1;
    float mark2;
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
    SDL_SetRenderDrawColor(game->renderer, 100, 149, 237, 255);
    SDL_RenderClear(game->renderer);
    SDL_RenderPresent(game->renderer);
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

/**
 * Tick
 */
static inline void Game_Tick(Game* game) {
    game->HandleEvents(game);
    game->Update(game);
    game->Render(game);
}

/**
 * Dispose
 */
static inline void Game_Dispose(Game* game) {
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    free(game->title);
    free(game->keys);
    free(game);
    SDL_Quit();
}

/**
 * GameLoop
 */
static inline void Game_GameLoop(Game* game) {
#if __EMSCRIPTEN__
    emscripten_set_main_loop_arg((em_arg_callback_func)game->Tick, (void*)game, -1, 1);
#else
    while (true) {
        game->Tick(game);
        // printf("Start game loop %x\n", game->running);
        if (!game->running) break;
    }
#endif
}


/**
 * New Game
 */
static inline Game* GameNew(char* title, int x, int y, int w, int h, int flags)
{
    // if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_AUDIO ) < 0) {
    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
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
    game->sdlVersion = version;
    game->title = strdup(title);
    game->x = x;
    game->y = y;
    game->w = w;
    game->h = h;
    game->flags = flags;
    game->running = true;
    game->keys = calloc(256, sizeof(bool));
    game->window = SDL_CreateWindow(title, x, y, w, h, flags);
    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);

    // write up the methods
    game->Update = Game_Update;
    game->Render = Game_Render;
    game->Tick = Game_Tick;
    game->HandleEvents = Game_HandleEvents;
    game->Dispose = Game_Dispose;
    game->GameLoop = Game_GameLoop;
    return game;
}
