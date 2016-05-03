#include "passages.h"

typedef struct GameInfo {
	Passage *passage;
	int passageID;
	int time;

} GameInfo;

void set_passage_details(int passage, int time);
void game_init(GameInfo *info);
void game_destroy();
//void print_line();
void game_event(SDL_Event *e);
