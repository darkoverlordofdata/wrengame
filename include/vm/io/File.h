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

static inline void test() 
{
    char cwd[PATH_MAX];

    if (GetCwd(cwd, sizeof(cwd)) != nullptr) {
       printf("Current working dir: %s\n", cwd);
    } else {
       perror("getcwd() error");
       return;
    }
    Path* cwdPath = pathNew(cwd);
    pathNormalize(cwdPath);
    pathDirName(cwdPath);
    // pathRemoveExtension(cwdPath);

    printf("searchDirectory = %s\n", pathToString(cwdPath));

}