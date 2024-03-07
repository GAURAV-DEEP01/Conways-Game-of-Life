#include "../include/golUI.h"
#include <stdio.h>
SDL_Event GOL_GlobalEvent;
SDL_DisplayMode DM;

bool GOL_UI_IfCloseWindow(){
    if(GOL_GlobalEvent.type == SDL_QUIT){
        SDL_Quit();
        return true;
    }
    return false;
}


SDL_Surface* GOL_GetSurfaceFromText(SDL_Renderer *renderer,char *GOL_Text,int size){
    TTF_Font *pixel = TTF_OpenFont("./assets/PixelsplitterBold-ErDW.ttf", DM.w/size);
    if (!pixel) {
        printf("Failed to load font: %s\n", TTF_GetError());
        TTF_CloseFont(pixel);
        return NULL;
    }
    SDL_Color white = {235, 235, 235, 0};
    SDL_Surface *surface = TTF_RenderText_Solid(pixel,GOL_Text,white);
    if (!surface) {
        printf("Failed to create surface: %s\n", TTF_GetError());
        TTF_CloseFont(pixel);
        return NULL;
    }
    TTF_CloseFont(pixel);
    return surface;
}

void GOL_RenderText(SDL_Renderer *renderer, SDL_Surface *surface, SDL_Rect *rect) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }
    SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h);
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_DestroyTexture(texture);
}

void GOL_UserInterface(SDL_Renderer *renderer){
    bool onMenu = true ;

    SDL_Rect Heading, userScale, instruction ,scale;
    Heading.x = userScale.x = instruction.x = scale.x = 20;
    Heading.y = 100;
    scale.y = 340;
    userScale.y = 400;
    instruction.y = 550;
        
    SDL_Surface* surfaceHeading =  GOL_GetSurfaceFromText(renderer,"Conways Game of life",20);
    SDL_Surface* surfaceScale = GOL_GetSurfaceFromText(renderer,"Life Scale (press the UP or DOWN arrow)",40);
    SDL_Surface* surfaceInstruction =  GOL_GetSurfaceFromText(renderer,"Press 'Space' to Start the simulation",40);

    int instructionBlinker=0, blinkerDuration = 35;

    while (onMenu) {
        while (SDL_PollEvent(&GOL_GlobalEvent)) {
            if (GOL_UI_IfCloseWindow(GOL_GlobalEvent)) {
                SDL_FreeSurface(surfaceHeading);
                SDL_FreeSurface(surfaceScale);
                SDL_FreeSurface(surfaceInstruction);
                SDL_Quit();
                exit(0);
            }

            if (GOL_GlobalEvent.key.type == SDL_KEYDOWN) {
                switch (GOL_GlobalEvent.key.keysym.sym) {
                    case SDLK_UP:
                        if (GOL_SurfaceScale.lifeScale != 10)
                            GOL_SurfaceScale.lifeScale++;
                        break;
                    case SDLK_DOWN:
                        if (GOL_SurfaceScale.lifeScale != 2)
                            GOL_SurfaceScale.lifeScale--;
                        break;
                    case SDLK_SPACE:
                        GOL_SurfaceScale.surfaceX = DM.w / GOL_SurfaceScale.lifeScale; 
                        GOL_SurfaceScale.surfaceY = DM.h / GOL_SurfaceScale.lifeScale;
                        onMenu = false;
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 21, 21, 21, 225);
        SDL_RenderClear(renderer);
        char scaleInChar[3];  
        sprintf(scaleInChar, "%d", (int)GOL_SurfaceScale.lifeScale);
        SDL_Surface* surfaceUserScale = GOL_GetSurfaceFromText(renderer,scaleInChar,40);      
        
        SDL_SetRenderDrawColor(renderer, 90, 90, 90, 255);
        
        GOL_RenderText(renderer,surfaceHeading,&Heading);
        GOL_RenderText(renderer,surfaceScale,&scale);
        GOL_RenderText(renderer,surfaceUserScale,&userScale);

        if(instructionBlinker++ <= blinkerDuration )
            GOL_RenderText(renderer,surfaceInstruction,&instruction);
        else if(instructionBlinker == blinkerDuration*2)
            instructionBlinker = 0;

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 60);
        SDL_FreeSurface(surfaceUserScale);
    }
    SDL_FreeSurface(surfaceHeading);
    SDL_FreeSurface(surfaceInstruction);
    SDL_FreeSurface(surfaceScale);
}