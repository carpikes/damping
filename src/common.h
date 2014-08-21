#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <ctype.h>

#ifdef _WIN32
    #include <windows.h>
    #include <mmsystem.h>
#else
    #include <sys/time.h>
#endif

#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <math.h>

#endif
