#include <SDL.h>

typedef struct SCREEN {
	struct SCREEN *prev;
	int bg; int fg;
	void *data;
	void (*init)(void*);
	void (*destroy)(void);
	void (*action)(SDL_Event*);
	void (*loop)(void);
} SCREEN;

void screen_init();
void screen_destroy();

SCREEN* create_screen(SCREEN *prev, int bg, int fg, void *init, void *action);
void show_screen(int index);
void set_screen(SCREEN *screen);
SCREEN* get_screen(int index);

#define SCREEN_COUNT 6
#define SCREEN_LOGIN 0
#define SCREEN_MAIN 1
#define SCREEN_PASSAGE 2
#define SCREEN_GAME 3
#define SCREEN_REPLAY 4
#define SCREEN_UPDATE 5

SCREEN* screen_login();
SCREEN* screen_main();
SCREEN* screen_passage();
SCREEN* screen_game();
SCREEN* screen_replay();
SCREEN* screen_update();

extern SCREEN *current_screen;
