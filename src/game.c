#include <SDL.h>
#include <time.h>

#include "config.h"
#include "game.h"
#include "passages.h"
#include "font.h"
#include "event.h"
#include "database.h"
#include "save.h"
#include "screen.h"

#define PADDING 5

Passage passage;
int passageID;
int passageTime;

int line;
int line_pos;
SDL_Point _pos;

//SDL_TimerID timer;
Uint32 startTime,endTime;
int charCount;
int errCount;
int finished;

Replay replay;
ReplayItem *replay_items = NULL;

Uint32 complete(Uint32 interval, void *param);
void finish();

void print_line() {
	//line_pos=0;
	SDL_Point pos = getpos();

	mvabs(PADDING, pos.y);
	dprints((*passage.text)[line]);
	mvabs(PADDING, pos.y+1);
	dprintc('_'); printc('\b');
}

void start_timer() {
	//timer = SDL_AddTimer(passageTime*1000, complete, NULL);
	startTime = SDL_GetTicks();
	endTime = startTime+(passageTime*1000);
	charCount=0;
	errCount=0;
	finished = 0;
}

void start_test() {
	line_pos=0;

	cls();
	if (replayRunning) {
		color(0,0xC);
		mvabs(SCREEN_WIDTH-6,24); dprints("REPLAY");
		color(0,7);
	}
	mvabs(PADDING,1);
	dprints("Type this:");
	mvabs(PADDING, 3);

	print_line();
}

void game_init(GameInfo *info) {
	SDL_StopTextInput();
	passage = *(info->passage);
	passageID = info->passageID;
	passageTime = info->time;
	line = 0;

	if (replay_items == NULL) {
		replay_items = malloc(4096*sizeof(ReplayItem)); //overwrites menu items...
	}

	color(0,7);
	start_test();
	start_timer();
	redraw();
	SDL_StartTextInput();
}

void game_destroy() {
	if (replay_items != NULL) {
		free(replay_items);
		replay_items = NULL;
	}
}

void game_input(unsigned char c) {
	SDL_Point pos;
	charCount++;
#ifdef CAN_BACKSPACE
	if (c=='\b') {
		//DECREASE ERRORS?
		line_pos--;
		pos = getpos();
		dprintc(' ');
		mvabs(pos.x-1,pos.y+1); dprintc(' ');
		mvabs(pos.x-1,pos.y); dprintc(' ');
		mvabs(pos.x-1,pos.y);
		dprintc('_'); printc('\b');
		redraw();
		return;
	}
#endif
	if (c<32 || c>127) {
#ifdef IGNORE_BAD_CHAR
		return;
#else
		printf("INVALID '%c' (%i)\n",c,c);
		c = 251;;
#endif
	}
	if (line_pos==0 && c==' ') {
		return;
	}

	char *content = (*passage.text)[line];

	//printf("%i) '%c'='%c' (%i)",pos,c,correct,correct);
	dprintc(c);

	char correct = content[line_pos];
#ifdef SPACE_NEWLINE
	if (correct=='\0') {
		correct=' ';
	}
#endif

	replay_items[charCount-1].letter = c;
	replay_items[charCount-1].time = SDL_GetTicks()-startTime;
	replay_items[charCount-1].correct = 1;

	if (c!=correct) {
		replay_items[charCount-1].correct = 0;
		errCount++;
		pos = getpos();
		mvabs(pos.x-1, pos.y+1);
		dprintc(254);
		mvabs(pos.x, pos.y);
	}

#ifdef SPACE_NEWLINE
	if (content[line_pos]==0) {
#else
	if (content[line_pos+1]==0) {
#endif
		line_pos=0;
		line++;

		pos = getpos();
		if (pos.y>=SCREEN_HEIGHT-5) {
			cls();
			if (replayRunning) {
				color(0,0xC);
				mvabs(SCREEN_WIDTH-6,24); dprints("REPLAY");
				color(0,7);
			}
			pos.y=0;
		} else {
			pos.y+=3;
		}

		if (line>=passage.length) {
			line=0;
		}
		mvabs(PADDING, pos.y);
		print_line();
	} else {
		dprintc('_'); printc('\b');
		line_pos++;
	}

	redraw();
}

void game_event(SDL_Event *e) {
	if (e->type==EVENT_FINISHED) {
		finish();
		return;
	}
	if (e->type==EVENT_REPLAY) {
		game_input(e->user.code);
		return;
	}

	switch(e->type) {
		case SDL_KEYDOWN: {
			if (e->key.keysym.sym==SDLK_ESCAPE) {
				//SDL_RemoveTimer(timer);
				if (replayRunning) {
					replayRunning = 0;
					show_screen(SCREEN_REPLAY);
				} else {
					setEventHandler(screenEvent, NULL);
				}
				return;
			}

			if (replayRunning) {
				break; //Don't allow keypresses in replay
			}
			if(finished) {
				if (e->key.keysym.sym==SDLK_s && !replayRunning) {
					char name[255];
					time_t now = time(NULL);
					struct tm *t = localtime(&now);
					sprintf(name, "replays/%04i%02i%02i %02i-%02i-%02i.sav", 1900+t->tm_year,1+t->tm_mon,t->tm_mday, t->tm_hour,t->tm_min,t->tm_sec);
					printf("Saving replay %s\n", name);
					saveReplay(name, replay);
					mvabs(1,24); dprints("Replay Saved");
					redraw();
				}
				if (SDL_GetTicks()>endTime+SAFETY_TIME) {
					if (e->key.keysym.sym==SDLK_n) {
						setEventHandler(screenEvent, NULL);
					} else if (e->key.keysym.sym==SDLK_y) {
						color(0,7);
						#ifdef CONTINUE_SAME_LINE
							black(_pos.y+4);
							mvabs(_pos.x, _pos.y);
						#else
							cls();
							mvprints(PADDING,1, "Type this:");
							mvabs(PADDING, 3);
							line++; line_pos=0;
							print_line();
						#endif
						start_timer();
						printc('_'); printc('\b');
						redraw();
					}
				}
				return;
			}
			break;
		case SDL_TEXTINPUT:
			if (finished||replayRunning) return;
			for (int i=0; e->text.text[i]!='\0'; i++) {
				char code = e->text.text[i];
				if (code!=0) {
					if (code<32) break;
					game_input(code);
				}
			}
			break;
		}
	}
}


Uint32 complete(Uint32 interval, void *param) {
	printf("Done!\n");
	SDL_Event e;
	SDL_zero(e);
	e.type = EVENT_FINISHED;
	SDL_PushEvent(&e);
	return 0;
}

void finish() {
	finished = 1;
	printf("Test finshed. chars: %i, errors: %i, time: %i\n", charCount, errCount, passageTime);

	int wpm = (charCount/WORD_SIZE/(passageTime/60.0f));
	int errors = errCount;
	//int errors = errCount*2;
#ifdef NEW_WPM
	int net=((charCount-errors*ERROR_WEIGHT)/WORD_SIZE/(passageTime/60.0f));
#else
	int net = wpm-errors;
#endif
	if (net<0) {net=0;}

	SDL_Point pos = getpos();
	if (pos.y>SCREEN_HEIGHT-14) {
		scroll(17-(SCREEN_HEIGHT-pos.y));
	}
	_pos = getpos();
	int y=_pos.y+4;

	color(0,0xC);
	mvabs(35,y); prints("TIME'S UP");
	mvabs(29,y+2); prints("Your average is:      %i",wpm);
	mvabs(29,y+4); prints("Errors: %3i     =     %i",errCount,errors);
	mvabs(29,y+6); prints("Your net score is:    %i  words per minute",net);
	if (!replayRunning) {
		mvabs(29,y+10); prints("Do you want to continue?");
		mvprints(1,24,"S Save");
	}
	redraw();
#ifdef USE_DB
	db_write_test(charCount, errCount, passageTime, passageID+1);
#endif
	replay.passage = passageID;
	replay.time = passageTime;
	replay.items = charCount;
	replay.data = replay_items;
	return;
}

void game_loop() {
	if (!finished && SDL_GetTicks()>endTime) {
		finish();
	}
}

SCREEN* screen_game() {
	SCREEN *screen = create_screen(NULL, 0x0,0x7, game_init, game_event);
	screen->data = malloc(sizeof(GameInfo));
	screen->destroy = game_destroy;
	screen->loop = game_loop;
	return screen;
}

//Event gameEvent = {(void*)game_init,game_event, no_loop};
