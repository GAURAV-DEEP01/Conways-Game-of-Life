
//UI
#include "shared.h"

extern SDL_DisplayMode DM;
extern SDL_Event GOL_GlobalEvent;

extern bool GOL_UI_IfCloseWindow();
extern void GOL_UserInterface(SDL_Renderer *renderer);
extern SDL_Surface* GOL_GetSurfaceFromText(SDL_Renderer *renderer,char *GOL_Text,int size);
extern void GOL_RenderText(SDL_Renderer *renderer, SDL_Surface *surface, SDL_Rect *rect);