#include<iostream>
#include "./app/include/gameOfLife.hpp"

int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    bool running = true; 

    SDL_Event e;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    
    GOL_SURFACE_T surface_frame_one = GOL_GetLifeSurface();
    GOL_SURFACE_T surface_frame_two = GOL_GetLifeSurface();
    GOL_RenderSurface_rnd(renderer,surface_frame_one);

    SDL_CreateWindowAndRenderer(GOL_WINDOW_WIDTH, GOL_WINDOW_HEIGHT, 0, &window, &renderer);
    
    while(running){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT)
                running = false;
        }
        SDL_SetRenderDrawColor(renderer,46,64,99,255);
        SDL_RenderClear(renderer);
        SDL_RenderSetScale(renderer,4,4);
        GOL_RenderSurface(renderer,surface_frame_one);
        GOL_NextSimulationMove(surface_frame_one);
        SDL_Delay(500);    
    }
    return 0;
}