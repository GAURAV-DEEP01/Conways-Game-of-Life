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


void GOL_UserInterface(SDL_Renderer *renderer){
    bool onmenu = true ;

    TTF_Font* Pixl1 = TTF_OpenFont("./assets/PixelsplitterBold-ErDW.ttf",DM.w/20); 
    TTF_Font* Pixl = TTF_OpenFont("./assets/PixelsplitterBold-ErDW.ttf",DM.w/40); 
    if (!Pixl) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return;
    }

    SDL_Rect Heading, userScale, instruction;
    SDL_Color White = {255, 255, 255, 0};
    SDL_Surface* surfaceHeading = TTF_RenderText_Solid(Pixl1, "Conways Game of life", White);
    SDL_Surface* surfaceUserScale = TTF_RenderText_Solid(Pixl,"2",White);
    SDL_Surface* surfaceInstruction = TTF_RenderText_Solid(Pixl,"Press 'Space' to Start the simulation",White);

    if (!surfaceHeading) {
        printf("Failed to create surface: %s\n", TTF_GetError());
        TTF_CloseFont(Pixl);
        return;
    }

    SDL_Texture* headingMessage = SDL_CreateTextureFromSurface(renderer, surfaceHeading);
    SDL_Texture* userScaleMessage = SDL_CreateTextureFromSurface(renderer, surfaceUserScale);
    SDL_Texture* instructionMessage = SDL_CreateTextureFromSurface(renderer, surfaceInstruction);
    if (!headingMessage || !userScaleMessage || !instructionMessage) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surfaceHeading);
        SDL_FreeSurface(surfaceUserScale);
        SDL_FreeSurface(surfaceInstruction);
        TTF_CloseFont(Pixl);
        return;
    }

    while (onmenu) {
        while (SDL_PollEvent(&GOL_GlobalEvent)) {
            if (GOL_UI_IfCloseWindow(GOL_GlobalEvent)) {
                SDL_DestroyTexture(headingMessage);
                SDL_FreeSurface(surfaceHeading);
                TTF_CloseFont(Pixl);
                SDL_Quit();
                exit(0);
            }

            if (GOL_GlobalEvent.key.type == SDL_KEYDOWN) {
                switch (GOL_GlobalEvent.key.keysym.sym) {
                    case SDLK_UP:
                        printf("up");
                        if (GOL_SurfaceScale.lifeScale != 10)
                            GOL_SurfaceScale.lifeScale++;
                        break;
                    case SDLK_DOWN:
                        printf("down");
                        if (GOL_SurfaceScale.lifeScale != 2)
                            GOL_SurfaceScale.lifeScale--;
                        break;
                    case SDLK_SPACE:
                        printf("space");
                        onmenu = false;
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 225);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 90, 90, 90, 255);
        SDL_GetClipRect(surfaceHeading, &Heading);
        SDL_GetClipRect(surfaceUserScale, &userScale);
        SDL_GetClipRect(surfaceInstruction, &instruction);
        Heading.x = userScale.x = instruction.x = 20;
        Heading.y = 200;
        userScale.y = 350;
        instruction.y = 450;
        
        SDL_RenderCopy(renderer, headingMessage, NULL, &Heading);
        SDL_RenderCopy(renderer, userScaleMessage, NULL, &userScale);
        SDL_RenderCopy(renderer, instructionMessage, NULL, &instruction);

    
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 60);
    }

    SDL_DestroyTexture(headingMessage);
    SDL_FreeSurface(surfaceHeading);
    TTF_CloseFont(Pixl);
}