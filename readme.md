# playing with wrenscript

it works in emscripten, too.




link_directories( ${CMAKE_SOURCE_DIR}/lib/ )

## I want a new C...

Yeah, I said that. 

To play with embedding wren script, I need some c code to embed with. I've repurposed the 
example from DarkSTEP. As it turns out, the runtime was overkill, and needed a horrendus 
amount of boilerplate. All I really needed was multi-methods.