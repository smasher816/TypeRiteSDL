#include "config.h"
#ifdef RAINBOW
#include <SDL.h>
#include <math.h>
#include "font.h"
#include "game.h"

int ponies=0;
int unicorns=0;

SDL_Renderer *renderer;
SDL_Texture *overlay;
int fg = 9;

void rainbow_init(SDL_Renderer *renderer, SDL_Texture **o) {
	overlay = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, RES_X, RES_Y);
	SDL_SetRenderTarget(renderer, overlay);
	//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(overlay, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 255,255,255, 255);
	SDL_RenderFillRect(renderer, NULL);
	SDL_SetTextureAlphaMod(overlay, 0);
	*o = overlay;
}

void phaseShift(int r, int g, int b) {
	//printf("phaseShift: %i,%i,%i\n", r,g,b);
	SDL_SetTextureColorMod(overlay, r,g,b);//c.r,c.g,c.b);
	//SDL_SetRenderTarget(renderer, NULL);
	//SDL_RenderCopy(renderer, display, NULL, NULL);
	//SDL_RenderPresent(renderer);
	//redraw();
}

void countPonies(SDL_Keycode sym) {
	//printf(" - %i\n", sym);
	     if (ponies==0 && sym==SDLK_UP) {ponies++;}
	else if (ponies==1 && sym==SDLK_UP) {ponies++;}
	else if (ponies==2 && sym==SDLK_DOWN) {ponies++;}
	else if (ponies==3 && sym==SDLK_DOWN) {ponies++;}
	else if (ponies==4 && sym==SDLK_LEFT) {ponies++;}
	else if (ponies==5 && sym==SDLK_RIGHT) {ponies++;}
	else if (ponies==6 && sym==SDLK_LEFT) {ponies++;}
	else if (ponies==7 && sym==SDLK_RIGHT) {ponies++;}
	else if (ponies==8 && sym==SDLK_b) {ponies++;}
	else if (ponies==9 && sym==SDLK_a) {ponies++;}
	else if (ponies==10 && sym==SDLK_RETURN) {
		unicorns=!unicorns;
		if (unicorns==0) {
			SDL_SetTextureAlphaMod(overlay, 0);
			//phaseShift(0,0,0);
		} else {
			SDL_SetTextureAlphaMod(overlay, 127);
			printf("OMG PONIEEEZZZZZ!!!!\n");
		}
	} else {
		ponies=0;
	}
	//printf("P: %i\n", ponies);
}

void oooPretty() {
	if (unicorns) {
		/*Cursor_Color cursor = getcolor();
		fg++;
		if (fg==cursor.bg) {
			fg++;
		}
		if (fg>0xF) {
			fg=9;
		}*/
		float freq = 0.001;
		Uint32 t = SDL_GetTicks();
		int r = sin(freq*t + 0) * 127 + 127;
		int g = sin(freq*t + 2) * 127 + 127;
		int b = sin(freq*t + 4) * 127 + 127;
		phaseShift(r,g,b);
		redraw();
	} else {
		//redraw();
	}
}
#endif
