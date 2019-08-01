#!/bin/bash
#
#   compile the static wren lib for emscripten   
#
emcc src/vm/wren_compiler.c src/vm/wren_core.c src/vm/wren_debug.c src/vm/wren_primitive.c src/vm/wren_utils.c src/vm/wren_value.c src/vm/wren_vm.c src/optional/wren_opt_meta.c src/optional/wren_opt_random.c -Isrc/include -Isrc/vm -Isrc/optional -o libwren.bc
