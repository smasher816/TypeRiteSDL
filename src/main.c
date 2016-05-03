//#include <stdio.h>
#include <SDL.h>

#include "config.h"
#include "icon.h"
#include "font.h"
#include "fontimage.h"
#include "event.h"
#include "database.h"
#include "save.h"
#include "rainbow.h"
#include "updater.h"
#include "screen.h"
#include "game.h"

int active = 1;
SDL_Window *window;

void setEventHandler(Event e, void *data) {
	event = e;
	event.init(data);
}

void noop() {}

void toggleFullscreen(SDL_Window *window) {
	Uint32 flags = SDL_GetWindowFlags(window);
	SDL_SetWindowFullscreen(window, flags^SDL_WINDOW_FULLSCREEN_DESKTOP);
	redraw();
}

int handle_event(SDL_Event *e) {
	switch(e->type) {
		/*case SDL_ActiveEvent:
		case SDL_SYSWMEVENT:
		case SDL_USEREVENT:
			return 0;*/
		case SDL_KEYDOWN:
			if (e->key.keysym.sym==SDLK_RETURN && (e->key.keysym.mod&KMOD_ALT)) {
				toggleFullscreen(window);
				return 1;
			}
			if (e->key.keysym.sym==SDLK_r && (e->key.keysym.mod&KMOD_ALT)) {
				printf("REDRAW!\n"); redraw();
				return 1;
			}
			#ifdef RAINBOW
				countPonies(e->key.keysym.sym);
			#endif
			break;
		/*case SDL_DROPFILE: {
			if (strcmp(e->drop.file+strlen(e->drop.file)-4, ".sav") == 0) {
				runReplay(e->drop.file);
				return 1;
			}
			break;
		}*/
		case SDL_WINDOWEVENT:
			switch (e->window.event) {
				case SDL_WINDOWEVENT_EXPOSED:
				case SDL_WINDOWEVENT_SIZE_CHANGED:
				case SDL_WINDOWEVENT_MAXIMIZED:
				case SDL_WINDOWEVENT_RESTORED:
					redraw();
					return 1;
			}
			break;
		case SDL_QUIT:
			active = 0;
			return 1;
	}
	return 0;
}

int main(int argc, char *argv[]) {
#ifdef __WINDOWS__
	_unlink(BACKUP_NAME);
#endif

	int flags = VIDEO_FLAGS | SDL_WINDOW_RESIZABLE;
#ifdef FULLSCREEN
	flags |= SDL_WINODW_FULLSCREEN_DESKTOP;
#endif
	if (argc==2 && strcmp(argv[1],"--fullscreen")==0) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
	window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 0,0, flags);
	SDL_SetWindowMinimumSize(window, RES_X, RES_Y);

	SDL_Surface *icon = SDL_CreateRGBSurfaceFrom(icon_pixels,16,16,16,16*2,0x0f00,0x00f0,0x000f,0xf000);
	SDL_SetWindowIcon(window, icon);
	SDL_FreeSurface(icon);
	SDL_ShowCursor(SDL_DISABLE);
	userEventTypes = SDL_RegisterEvents(NUM_EVENTS);

	font_init(window, font_bmp);
	screen_init();
#ifdef USE_DB
	db_init();
	//setEventHandler(loginEvent, NULL);
#else
	setEventHandler(screenEvent, NULL);
#endif

	if (argc==2) {
		if (strcmp(argv[1]+strlen(argv[1])-4, ".sav") == 0) {
			runReplay(argv[1]);
		}
	}

	SDL_Event e;
	while (active) {
		while(SDL_PollEvent(&e)) {
			if (handle_event(&e)) {
				continue;
			}
			event.event(&e);
		}
		if (event.loop != NULL) {
			event.loop();
		}
#ifdef RAINBOW
		oooPretty();
#endif
		//redraw();
	}

#ifdef USE_DB
	db_quit();
#endif
	game_destroy(); //remove me
	screen_destroy();
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
