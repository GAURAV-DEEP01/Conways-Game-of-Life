#include <stdio.h>
#include "./app/include/gameOfLife.h"
#include "./app/include/golUI.h"

int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    bool running = true; 
    if(TTF_Init() == -1)
        printf("failed to initialize\n");
    SDL_Window *window = SDL_CreateWindow(
        "Game of life",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        GOL_WINDOW_WIDTH,
        GOL_WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
    );
    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_GetCurrentDisplayMode(0, &DM);

    GOL_UserInterface(renderer);

    GOL_SurfaceScale.surfaceX = DM.w / GOL_SurfaceScale.lifeScale; 
    GOL_SurfaceScale.surfaceY = DM.h / GOL_SurfaceScale.lifeScale; 

    GOL_SURFACE_T surface_present = GOL_GetLifeSurface();
    GOL_SURFACE_T surface_future = GOL_GetLifeSurface();
    GOL_RenderSurface_rnd(renderer,surface_present);
    
    // UI takes renderer, display mode and sdl_event 
    

    while(running){
        while(SDL_PollEvent(&GOL_GlobalEvent)){
            running = GOL_UI_IfCloseWindow(GOL_GlobalEvent) ? false : true;
        }
        SDL_SetRenderDrawColor(renderer,46,64,99,255);
        SDL_RenderClear(renderer);
        SDL_RenderSetScale(renderer,GOL_SurfaceScale.lifeScale,GOL_SurfaceScale.lifeScale);
        GOL_RenderSurface(renderer,surface_present);
        GOL_NextSimulationMove(surface_present, surface_future);
        GOL_SURFACE_T surface_aux = surface_present;
        surface_present = surface_future;
        surface_future = surface_aux;
        SDL_Delay(1000/60);    
    }
    SDL_Quit();
    return 0;
}