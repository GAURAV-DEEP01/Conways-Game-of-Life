#include "./app/include/gameOfLife.h"

int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    bool running = true; 

    SDL_Event e;
    SDL_Window *window = SDL_CreateWindow(
        "Game of life",
        100,
        100,
        GOL_WINDOW_WIDTH,
        GOL_WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,0);
    
    GOL_SURFACE_T surface_present = GOL_GetLifeSurface();
    GOL_SURFACE_T surface_future = GOL_GetLifeSurface();
    GOL_RenderSurface_rnd(renderer,surface_present);
    
    int GOL_CurrentWindowWidth = GOL_WINDOW_WIDTH, GOL_CurrentWindowHeight = GOL_WINDOW_HEIGHT;
    float GOL_LifeScale = GOL_LIFE_SCALCE; 
    while(running){
        int width = GOL_CurrentWindowWidth, height = GOL_CurrentWindowHeight;
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT)
                running = false;
            switch(e.window.event){
                case SDL_WINDOWEVENT_MAXIMIZED:
                    SDL_GetWindowSize(window,&GOL_CurrentWindowWidth,&GOL_CurrentWindowHeight);
                    GOL_LifeScale = (GOL_CurrentWindowWidth/width)*GOL_LifeScale+2;   
                    break;
                case SDL_WINDOWEVENT_RESTORED:    
                    SDL_GetWindowSize(window,&GOL_CurrentWindowWidth,&GOL_CurrentWindowHeight);
                    GOL_LifeScale = (GOL_CurrentWindowWidth/width)*GOL_LifeScale+2;
                    break;         
                default:
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer,46,64,99,255);
        SDL_RenderClear(renderer);
        SDL_RenderSetScale(renderer,GOL_LifeScale,GOL_LifeScale);
        GOL_RenderSurface(renderer,surface_present);
        GOL_NextSimulationMove(surface_present, surface_future);
        GOL_SURFACE_T surface_aux = surface_present;
        surface_present = surface_future;
        surface_future = surface_aux;
        SDL_Delay(100);    
    }
    return 0;
}