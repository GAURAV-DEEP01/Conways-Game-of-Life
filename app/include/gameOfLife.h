#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include "shared.h"

#define GOL_SURFACE_X GOL_WINDOW_WIDTH/GOL_LIFE_SCALE
#define GOL_SURFACE_Y GOL_WINDOW_HEIGHT/GOL_LIFE_SCALE
#define GOL_LIFE true
#define GOL_DEATH false

typedef bool** GOL_SURFACE_T;
extern GOL_SURFACE_T GOL_GetLifeSurface();
extern void GOL_ClearSurface(GOL_SURFACE_T surface);
extern void GOL_RenderSurface(SDL_Renderer *renderer,GOL_SURFACE_T surface);
extern void GOL_RenderSurface_rnd(SDL_Renderer *renderer,GOL_SURFACE_T surface);
extern void GOL_NextSimulationMove(GOL_SURFACE_T surface_present, GOL_SURFACE_T surface_future);

#endif 