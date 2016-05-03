#include "config.h"
#include "screen.h"
#include "font.h"
#include "save.h"

#define PAGE_SIZE 9
tinydir_dir dir;
int page;

void listReplays(int _page) {
	/*replayCount = 0;
	if (replayList!=NULL) {
		free(replayList);
		replayList = NULL;
	}*/

	page = _page;
	getFiles(&dir, REPLAY_DIR);
	qsort(dir._files, dir.n_files, sizeof(tinydir_file), datesort);

	//replayList = malloc(dir.n_files*sizeof(char*));
	color(0x7,0x4); cls();
	mvprints(20,1,"Choose a replay to view\n");
	SDL_Point pos = getpos();
	for (int i=0; page*PAGE_SIZE+i<dir.n_files && i<PAGE_SIZE; i++) {
		mvabs(32,pos.y+i+1);
		prints("%i  %s\n", i+1, dir._files[page*PAGE_SIZE+i].name);
	}
	mvabs(20,pos.y+PAGE_SIZE+2); prints("Showing page %i of %i", page+1, (dir.n_files/PAGE_SIZE)+1);
	mvprints(20,pos.y+PAGE_SIZE+4,"<- PREV    NEXT ->");
	redraw();
}

void replay_init() {
	listReplays(page);
}

void replay_event(SDL_Event *e) {
	switch(e->type) {
		case SDL_KEYDOWN: {
			SDL_Keycode key = e->key.keysym.sym;
			if (key==SDLK_ESCAPE) {
				//setEventHandler(menuEvent, NULL);
				page=0;
				tinydir_close(&dir);
				return;
			}
			if (key==SDLK_LEFT || key==SDLK_UP || key==SDLK_PAGEUP || key==SDLK_p) {
				if (page>0)
					listReplays(page-1);
			}
			if (key==SDLK_RIGHT || key==SDLK_DOWN || key==SDLK_PAGEDOWN || key==SDLK_n) {
				if (PAGE_SIZE*(page+1)<=dir.n_files)
					listReplays(page+1);
			}
			int index = (int)(key-'1');
			if (index>=0 && index<dir.n_files) {
				runReplay(dir._files[page*9+index].path);
			}
		}
	}
}

void replay_cleanup() {
	//free(dir->_files);
	tinydir_close(&dir);
}

SCREEN *screen_replay() {
	SCREEN *screen = create_screen(NULL, 0x7,0x4, replay_init, replay_event);
	screen->prev = get_screen(SCREEN_MAIN);
	return screen;
}
