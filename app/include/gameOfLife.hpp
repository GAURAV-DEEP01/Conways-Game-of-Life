#ifndef GAMEOFLIFE_HPP
#define GAMEOFLIFE_HPP

#include <cstdlib>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define GOL_LIFE_SCALCE 4
#define GOL_WINDOW_HEIGHT 500
#define GOL_WINDOW_WIDTH 800
#define GOL_SURFACE_X GOL_WINDOW_WIDTH/GOL_LIFE_SCALCE
#define GOL_SURFACE_Y GOL_WINDOW_HEIGHT/GOL_LIFE_SCALCE
#define GOL_LIFE true
#define GOL_DEATH false

typedef bool** GOL_SURFACE_T;
extern bool** GOL_GetLifeSurface();
extern void GOL_RenderSurface(SDL_Renderer *renderer,GOL_SURFACE_T surface);
extern void GOL_RenderSurface_rnd(SDL_Renderer *renderer,GOL_SURFACE_T surface);
extern void GOL_NextSimulationMove(GOL_SURFACE_T surface);

#endif 