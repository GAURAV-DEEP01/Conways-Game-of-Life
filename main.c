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

    // UI 
    GOL_UserInterface(renderer);

    GOL_SURFACE_T surface_present = GOL_GetLifeSurface();
    GOL_SURFACE_T surface_future = GOL_GetLifeSurface();
    GOL_RenderSurface_rnd(renderer,surface_present);
    

    while(running){
        while(SDL_PollEvent(&GOL_GlobalEvent)){
            running = GOL_UI_IfCloseWindow(GOL_GlobalEvent) ? false : true;
            if(GOL_GlobalEvent.key.type == SDL_KEYDOWN){
                if(GOL_GlobalEvent.key.keysym.sym == SDLK_ESCAPE){
                    SDL_RenderSetScale(renderer,1,1);
                    GOL_FreeLifeSurface(surface_present);
                    GOL_FreeLifeSurface(surface_future);
                    GOL_UserInterface(renderer); 
                    surface_present = GOL_GetLifeSurface();
                    surface_future = GOL_GetLifeSurface();  
                    GOL_RenderSurface_rnd(renderer,surface_present);
                }
            }
        }
        SDL_SetRenderDrawColor(renderer,132,245,66,255);
        SDL_RenderClear(renderer);
        SDL_RenderSetScale(renderer,GOL_SurfaceScale.lifeScale,GOL_SurfaceScale.lifeScale);
        GOL_RenderSurface(renderer,surface_present);
        GOL_NextSimulationMove(surface_present, surface_future);
        GOL_SURFACE_T surface_aux = surface_present;
        surface_present = surface_future;
        surface_future = surface_aux;
        SDL_Delay(150);    
    }
    GOL_FreeLifeSurface(surface_present);
    GOL_FreeLifeSurface(surface_future);
    SDL_Quit();
    return 0;
}