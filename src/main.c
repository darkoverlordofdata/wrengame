#include <stdio.h>
#include <string.h>
#include "SDL2/SDL.h"
#include "dark.h"
#include "xna/xna.h"
// #include "breakout.h"

/**
 * Extend the List object with an iterator
 */
void method ForEach(List* this, void (^iter)(char*))
{
    for (var curr = this->head; curr != nullptr; curr = curr->next) {
        iter(curr->data);
    }
}

int main(int argc, const char* argv[])
{


    Map* m = new(Map);

    Put(m, "foo", "hello world");
    println("%s", Get(m, "foo"));
    Put(m, "foo2", "hello world2");
    println("%s", Get(m, "foo2"));

    Dispose(m);

    List* l = new(List);

    Add(l, "hello message1");
    Add(l, "hello message2");
    Add(l, "hello message3");
    ForEach(l, ^(char* s) {
        println("item = %d) %s", Length(s), s);
    });

    Dispose(l);

    Game* game = new(Game, "SdL Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                        600, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );

    Run(game);
    Dispose(game);

    return 0;

}
