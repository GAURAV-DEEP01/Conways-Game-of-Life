#ifndef SHARED_H
#define SHARED_H

#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#define GOL_LIFE_SCALE 2
#define GOL_WINDOW_HEIGHT 700
#define GOL_WINDOW_WIDTH 1200
//In % paused for now
// #define GOL_MAXDENSITY 50

typedef struct GOL_SURFACE_SCALE{
    int surfaceX , surfaceY;
    float lifeScale;
}GOL_SURFACE_SCALE;
extern GOL_SURFACE_SCALE GOL_SurfaceScale;

#endif