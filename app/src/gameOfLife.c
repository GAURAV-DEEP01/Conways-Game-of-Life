#include "../include/gameOfLife.h"

GOL_SURFACE_SCALE GOL_SurfaceScale = {
    GOL_SURFACE_X,
    GOL_SURFACE_Y,
    GOL_LIFE_SCALE	
};

GOL_SURFACE_T GOL_GetLifeSurface(){
	GOL_SURFACE_T surface = (GOL_SURFACE_T)calloc(GOL_SurfaceScale.surfaceY,sizeof(bool*));
	if(!surface){
		SDL_Quit();
		exit(0); 
	}
	for(int i=0; i < GOL_SurfaceScale.surfaceY; i++){
		surface[i] = (bool*)calloc(GOL_SurfaceScale.surfaceX, sizeof(bool));
		if(!surface[i]){		
			SDL_Quit();
			exit(0);
		}
	}
	return surface;
}

void GOL_FreeLifeSurface(GOL_SURFACE_T surface){
	for(int i = 0;i<GOL_SurfaceScale.surfaceY;i++)
		free(surface[i]);
	free(surface);
}

void GOL_ClearSurface(GOL_SURFACE_T surface){
	for(int i = 0;i<GOL_SurfaceScale.surfaceY;i++)
		for(int j = 0; j < GOL_SurfaceScale.surfaceX; j++)
			surface[i][j] = false;
}

void GOL_RenderSurface(SDL_Renderer *renderer,GOL_SURFACE_T surface){
	SDL_SetRenderDrawColor(renderer,16,14,0,255);
	for(int i = 0; i < GOL_SurfaceScale.surfaceY; i++)
		for(int j = 0; j < GOL_SurfaceScale.surfaceX; j++)
			if(surface[i][j] == GOL_LIFE )
				SDL_RenderDrawPoint(renderer,j,i);

	SDL_RenderPresent(renderer);
}

void GOL_RenderSurface_rnd(SDL_Renderer *renderer, GOL_SURFACE_T surface){
	srand (time (NULL));
	SDL_SetRenderDrawColor(renderer,46,14,0,255);
	for(int i = 0; i < GOL_SurfaceScale.surfaceY; i++)
		for(int j = 0; j < GOL_SurfaceScale.surfaceX; j++){    
			bool live = rand() % 10 == 0 ? true: false;
			live ? surface[i][j] = GOL_LIFE : 0 ;
		}
	SDL_RenderPresent(renderer);
}
void GOL_NextSimulationMove(GOL_SURFACE_T surface_present, GOL_SURFACE_T surface_future){	
	for(int i = 0; i < GOL_SurfaceScale.surfaceY; i++){
		for(int j = 0; j < GOL_SurfaceScale.surfaceX; j++){
			int s1 = i - 1;
			int s2 = j - 1;
			short livingNeighbours = 0;
			bool thisCell = surface_present[i][j];
			for(int h = s1; h < s1 + 3; h++)
				for(int w = s2; w < s2 + 3; w++)
					if(((h >= 0 && h < GOL_SurfaceScale.surfaceY) && (w >= 0 && w < GOL_SurfaceScale.surfaceX )) && !( h == i && w == j))
						if(surface_present[h][w] == GOL_LIFE)
							livingNeighbours++;

			if(thisCell == GOL_LIFE && livingNeighbours < 2)
                surface_future[i][j] = GOL_DEATH;
			else if (thisCell == GOL_LIFE && (livingNeighbours == 2 || livingNeighbours == 3)) 
                surface_future[i][j] = GOL_LIFE;
			else if(thisCell == GOL_LIFE && livingNeighbours > 3)
			    surface_future[i][j] = GOL_DEATH;
			else if(thisCell == GOL_DEATH && livingNeighbours == 3 )
                surface_future[i][j] = GOL_LIFE;
		}
	}
	GOL_ClearSurface(surface_present);
}


