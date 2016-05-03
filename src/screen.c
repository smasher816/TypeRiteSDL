#include "config.h"
#include "screen.h"
#include "font.h"
#include "event.h"

#include <stdlib.h>

SCREEN *screens[SCREEN_COUNT];
SCREEN *current_screen = NULL;

SCREEN* create_screen(SCREEN *prev, int bg, int fg, void *init, void *action) {
	SCREEN *screen = malloc(sizeof(SCREEN));
	screen->prev = prev;
	screen->bg = bg;
	screen->fg = fg;
	screen->init = init;
	screen->action = action;
	screen->loop = NULL;
	screen->destroy = NULL;
	screen->data = NULL;
	return screen;
}

void show_screen(int index) {
	set_screen(screens[index]);
}

void set_screen(SCREEN *screen) {
	if (screen==NULL) {
		current_screen = NULL;
		return;
	}
	if (screen->prev==NULL && current_screen!=NULL) {
		screen->prev = current_screen;
	}
	current_screen = screen;

	color(screen->bg, screen->fg); cls();
	screen->init(screen->data);
	redraw();

	event.loop = screen->loop;
}

SCREEN* get_screen(int index) {
	return screens[index];
}

void screen_prev() {
	if (current_screen->prev != NULL) {
		SCREEN *prev = current_screen->prev;
		current_screen = NULL; //kind of hacky
		set_screen(prev);
	} else {
		active = 0; //TODO: Create exit command
	}
}

void screen_init() {
	screens[SCREEN_LOGIN] = screen_login();
	screens[SCREEN_MAIN] = screen_main();
	screens[SCREEN_PASSAGE] = screen_passage();
	screens[SCREEN_GAME] = screen_game();
	screens[SCREEN_REPLAY] = screen_replay();
	screens[SCREEN_UPDATE] = screen_update();

	set_screen(screens[SCREEN_MAIN]);
}

void screen_destroy() {
	for (int i=0; i<SCREEN_COUNT; i++) {
		if (screens[i]->destroy != NULL) {
			screens[i]->destroy();
		}
		if (screens[i]->data != NULL) {
			free(screens[i]->data);
		}
		free(screens[i]);
	}
}

void screen_event(SDL_Event *e) {
	switch(e->type) {
		case SDL_KEYDOWN: {
			SDL_Keycode key = e->key.keysym.sym;
			if (key==SDLK_ESCAPE) {
				screen_prev();
				return;
			}
		}
	}
	if (current_screen->action!=NULL) {
		current_screen->action(e);
	}
}

Event screenEvent = {noop,screen_event,noop};
