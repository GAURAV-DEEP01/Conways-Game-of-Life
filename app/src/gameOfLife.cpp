#include "../include/gameOfLife.hpp"

GOL_SURFACE_T GOL_GetLifeSurface(){
	GOL_SURFACE_T surface = (GOL_SURFACE_T)calloc(GOL_SURFACE_Y,sizeof(bool*));
	if(!surface) exit(0);
	for(int i=0; i < GOL_SURFACE_Y; i++){
		surface[i] = (bool*)calloc(GOL_SURFACE_X, sizeof(bool));
		if(!surface[i])		
			exit(0);
	}
	return surface;
}
void GOL_ClearSurface(GOL_SURFACE_T surface){
	for(int i = 0;i<GOL_SURFACE_Y;i++)
		for(int j = 0; j < GOL_SURFACE_X; j++)
			surface[i][j] = false;
}

void GOL_RenderSurface(SDL_Renderer *renderer,GOL_SURFACE_T surface){
	SDL_SetRenderDrawColor(renderer,255,255,255,255);
	for(int i = 0; i < GOL_SURFACE_Y; i++)
		for(int j = 0; j < GOL_SURFACE_X; j++)
			if(surface[i][j] == GOL_LIFE )
				SDL_RenderDrawPoint(renderer,j,i);

	SDL_RenderPresent(renderer);
}

void GOL_RenderSurface_rnd(SDL_Renderer *renderer, GOL_SURFACE_T surface){
	SDL_SetRenderDrawColor(renderer,255,255,255,255);
	for(int i = 0; i < GOL_SURFACE_Y; i++)
		for(int j = 0; j < GOL_SURFACE_X; j++){
			bool live = rand() % 9 == 0 ? true: false;
			if(live)
				surface[i][j] = true;
		}
	SDL_RenderPresent(renderer);
}
void GOL_NextSimulationMove(GOL_SURFACE_T surface_present, GOL_SURFACE_T surface_future){	
	for(int i = 0; i < GOL_SURFACE_Y; i++){
		for(int j = 0; j < GOL_SURFACE_X; j++){
			int s1 = i - 1;
			int s2 = j - 1;
			short livingNeighbours = 0;
			bool thisCell = surface_present[i][j];
			for(int h = s1; h < s1 + 3; h++)
				for(int w = s2; w < s2 + 3; w++)
					if(((h >= 0 && h < GOL_SURFACE_Y) && (w >= 0 && w < GOL_SURFACE_X )) && !( h == i && w == j))
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

