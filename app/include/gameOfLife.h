#ifndef GAMEOFLIFE_HPP
#define GAMEOFLIFE_HPP

#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define GOL_LIFE_SCALCE 2
#define GOL_WINDOW_HEIGHT 700
#define GOL_WINDOW_WIDTH 1000
#define GOL_SURFACE_X GOL_WINDOW_WIDTH/GOL_LIFE_SCALCE
#define GOL_SURFACE_Y GOL_WINDOW_HEIGHT/GOL_LIFE_SCALCE
#define GOL_LIFE true
#define GOL_DEATH false

// typedef struct GOL_RELATIVE_SCALE{
//     unsigned int width , height, surfaceX , surfaceY;
//     short lifeScale;
// }GOL_RELATIVE_SCALE;

// GOL_RELATIVE_SCALE GOL_RelativeScale{
//      GOL_WINDOW_WIDTH,
//      GOL_WINDOW_HEIGHT,
//      GOL_SURFACE_X,
//      GOL_SURFACE_Y,
//      GOL_LIFE_SCALCE
//  };

typedef bool** GOL_SURFACE_T;
extern GOL_SURFACE_T GOL_GetLifeSurface();
extern void GOL_ClearSurface(GOL_SURFACE_T surface);
extern void GOL_RenderSurface(SDL_Renderer *renderer,GOL_SURFACE_T surface);
extern void GOL_RenderSurface_rnd(SDL_Renderer *renderer,GOL_SURFACE_T surface);
extern void GOL_NextSimulationMove(GOL_SURFACE_T surface_present, GOL_SURFACE_T surface_future);

#endif 