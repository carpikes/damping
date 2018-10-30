#ifndef COMMON_H
#define COMMON_H

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef _WIN32
#include <mmsystem.h>
#include <windows.h>
#else
#include <sys/time.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <math.h>
#include <time.h>

#endif
