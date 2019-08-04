#pragma once
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#ifdef _WIN32
#include <direct.h>
#include <limits.h>
#define GetCwd _getcwd
#define PATH_MAX MAX_PATH
#else
// #include <linux/limits.h>
#define PATH_MAX 4096
#define GetCwd getcwd
#endif
#include "path.h"

/**
 *  io/path::Allocate
 */
static inline void io_path_Allocate(WrenVM* vm) 
{ 
    Path** path = (Path**)wrenSetSlotNewForeign(vm, 0, 0, sizeof(Path*));
    const char* value = wrenGetSlotString(vm, 1); 
    *path = pathNew(value); 
}

/**
 *  io/path::Finalize
 * 
 */
static inline void io_path_Finalize(void* data) 
{ 
    Path** path = data;
    pathFree((Path**) *path);
}

static inline void io_path_Absolute(WrenVM* vm)
{
    wrenSetSlotDouble(vm, 0, PATH_TYPE_ABSOLUTE);
}
static inline void io_path_Relative(WrenVM* vm)
{
    wrenSetSlotDouble(vm, 0, PATH_TYPE_RELATIVE);
}
static inline void io_path_Simple(WrenVM* vm)
{
    wrenSetSlotDouble(vm, 0, PATH_TYPE_SIMPLE);
}

static inline void io_path_Cwd(WrenVM* vm)
{
    char cwd[PATH_MAX];

    if (GetCwd(cwd, sizeof(cwd)) == nullptr) 
    { 
        wrenSetSlotString(vm, 0, "No CWD!"); 
        wrenAbortFiber(vm, 0); 
        return; 
    }
    wrenSetSlotString(vm, 0, cwd);
}
/**
 *  io/path::Type
 * 
 *  Categorizes what form a path is.
 */
static inline void io_path_Type(WrenVM* vm) 
{ 
    Path** path = (Path**)wrenGetSlotForeign(vm, 0);
    wrenSetSlotDouble(vm, 0, pathType(*path));
}
/**
 *  io/path::DirName
 * 
 *  Strips off the last component of the path name.
 */
static inline void io_path_DirName(WrenVM* vm)
{
    Path** path = (Path**)wrenGetSlotForeign(vm, 0);
    pathDirName(*path);
}

/**
 *  io/path::RemoveExtension
 * 
 *  Strips off the file extension from the last component of the path.
 */
static inline void io_path_RemoveExtension(WrenVM* vm)
{
    Path** path = (Path**)wrenGetSlotForeign(vm, 0);
    pathRemoveExtension(*path);
}

/**
 *  io/path::Join
 * 
 *  Appends [string] to [path].
 */
static inline void io_path_Join(WrenVM* vm)
{
    Path** path = (Path**)wrenGetSlotForeign(vm, 0);
    const char* value = wrenGetSlotString(vm, 1); 
    pathJoin(*path, value);
}

/**
 *  io/path::AppendChar
 * 
 *  Appends [c] to the path, growing the buffer if needed.
 */
static inline void io_path_AppendChar(WrenVM* vm)
{
    Path** path = (Path**)wrenGetSlotForeign(vm, 0);
    const char* value = wrenGetSlotString(vm, 1); 
    pathAppendChar(*path, value);
}

/**
 *  io/path::AppendString
 * 
 *  Appends [string] to the path, growing the buffer if needed.
 */
static inline void io_path_AppemdString(WrenVM* vm)
{
    Path** path = (Path**)wrenGetSlotForeign(vm, 0);
    const char* value = wrenGetSlotString(vm, 1);
    pathAppendString(*path, value);
}

/**
 *  io/path::Normalize
 * 
 *  Simplifies the path string as much as possible.
 *
 *  Applies and removes any "." or ".." components, collapses redundant "/"
 *  characters, and normalizes all path separators to "/".
 */
static inline void io_path_Normalize(WrenVM* vm)
{
    Path** path = (Path**)wrenGetSlotForeign(vm, 0);
    pathNormalize(*path);
}

/**
 *  io/path::ToString
 * 
 *  Allocates a new string exactly the right length and copies this path to it.
 */
static inline void io_path_ToString(WrenVM* vm)
{
    Path** path = (Path**)wrenGetSlotForeign(vm, 0);
    char* value = pathToString(*path);
    wrenSetSlotString(vm, 0, value);

}
