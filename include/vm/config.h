#pragma once
#include <stdio.h>
#include <string.h>
#include <wren.h>
#include <dark.h>
#include "metadata.h"

/**
 * wren_Write
 */
static inline void 
wren_Write( WrenVM* vm, 
            const char* text) 
{
    fputs(text, stdout);
}


/**
 * wren_LoadModule
 */
static inline char* 
wren_LoadModule(WrenVM* vm, 
                const char* moduleName)
{
    // path <-"wren/" + moduleName + ".wren"
    size_t moduleNameLength = strlen(moduleName);
    char* path = (char*)malloc(moduleNameLength + 11);
    memcpy(path, "wren/", 5);
    memcpy(path + 5, moduleName, moduleNameLength + 5);
    memcpy(path + 5 + moduleNameLength, ".wren", 5);
    path[moduleNameLength + 10] = '\0';

    // Open the file.
    FILE* f = fopen(path, "rb");
    free(path);
    if (f == NULL) {
	    return NULL;
    }

    // Get the file length.
    fseek(f, 0, SEEK_END);
    size_t fileLength = ftell(f);
    rewind(f);

    // Read the file.
    char* fileContent = (char*)malloc(fileLength + 1);
    size_t bytesRead = fread(fileContent, sizeof(char), fileLength, f);
    fclose(f);
    if (fileLength != bytesRead) {
        free(fileContent);
        return NULL;
    }
    fileContent[fileLength] = '\0';

    return fileContent;
}

/**
 * wren_Error
 */
static inline void 
wren_Error( WrenVM* vm,
            WrenErrorType type, 
            const char* module, 
            int line,
            const char* message)
{
    switch (type) {
    case WREN_ERROR_COMPILE:
        fprintf(stderr, "compile time error: %s:%d:%s\n", module, line, message);
        break;
    case WREN_ERROR_RUNTIME:
        fprintf(stderr, "runtime error: %s\n", message);
        break;
    case WREN_ERROR_STACK_TRACE:
        fprintf(stderr, "stack trace: %s:%d:%s\n", module, line, message);
        break;
    }
}

/**
 * wren_BindForeignClass
 */
static inline WrenForeignClassMethods 
wren_BindForeignClass( WrenVM* vm, 
                        const char* module, 
                        const char* className) 
{
    WrenForeignClassMethods methods;
    methods.allocate = nullptr; 
    methods.finalize = nullptr;

    Class* meta = GetMetaData();

    for (int i=0; meta[i].module != nullptr; i++) {
        if (strcmp(module, meta[i].module) != 0) continue;
        if (strcmp(className, meta[i].className) != 0) continue;
        methods.allocate = meta[i].allocate; 
        methods.finalize = meta[i].finalize; 
        return methods; 

    }
    return methods; 
}

/**
 * wren_BindForeignMethod
 */
static inline WrenForeignMethodFn 
wren_BindForeignMethod( WrenVM* vm, 
                        const char* module, 
                        const char* className, 
                        bool isStatic, 
                        const char* signature) 
{
    Class* meta = GetMetaData();

    for (int i=0; meta[i].module != nullptr; i++) {
        if (strcmp(module, meta[i].module) != 0) continue;
        if (strcmp(className, meta[i].className) != 0) continue;
        for (int j=0; meta[i].methods[j].addr != nullptr; j++) {
            bool is_static = (meta[i].methods[j].name[0] == '+');
            if (is_static != isStatic) continue;
            char* name = isStatic ? meta[i].methods[j].name+1 : meta[i].methods[j].name;
            if (strcmp(signature, name) != 0) continue;
            return meta[i].methods[j].addr;
        }
    }
    return nullptr;
}