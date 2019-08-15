# playing with wrenscript

it works in emscripten, too.




link_directories( ${CMAKE_SOURCE_DIR}/lib/ )

## I want a new C...

Yeah, I said that.
I'm using clang's c overload attributes as multi-methods. That with type inferencing (c11) and lambda's ( (using ObjC's BlockRuntime) plus some convenience macros and funtions in a header library to create a more modern c.

```c
Map* m = new(Map);

Put(m, "foo", "hello world");
println("%s", Get(m, "foo"));
Put(m, "foo2", "hello world2");
println("%s", Get(m, "foo2"));

Dispose(m);

var xx = $(100);
println("typeof(xx) = %s", typeof(xx) );
println("xx = %s", ToString(xx));


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

```