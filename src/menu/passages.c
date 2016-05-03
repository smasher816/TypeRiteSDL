#include "menu.h"
#include "font.h"
#include "event.h"
#include "game.h"

SCREEN* screen_passage_time();
int passageID;


MENU_ITEM ipassages[] = {
	{"Accountant", 'A'},
	{"Carpenter", 'C'},
	{"Dietitian", 'D'},
	{"Engineer", 'E'},
	{"Geologist", 'G'},
	{"Hotel Manager", 'H'},
	{"Interior Designer", 'I'},
	{"Jeweler", 'J'},
	{"Lawyer", 'L'},
	{"Mechanic", 'M'},
	{"Newcaster", 'N'},
	{"Officer", 'O'},
	{"Paramedic", 'P'},
	{"Systems Analyst", 'S'},
	{"Technologist", 'T'},
	{"Waiter or Waitress", 'W'},
	{NULL, '\0'}
};

MENU_ITEM times[] = {
	{"Press 1 for a three-minute timed writing.", '1'},
	{"Press 3 for a three-minute timed writing.", '3'},
	{"Press 5 for a five-minute timed writing.", '5'},
	{NULL, '\0'}
};

void select_passage(char code) {
	int index = (code-'A');
	printf("Passage %i (%c)\n", index, code);
	if (passages[index]!=NULL) { //index<ARRAYLEN(passages)
		passageID = index;
		set_screen(screen_passage_time());
	} else {
		printf("BAD!\n");
	}
}

void select_time(char code) {
	int time=0;
	if (code=='1') {time=15;}
	else if (code=='3') {time=3*60;}
	else if(code=='5') {time=5*60;}
	printf("Time %i\n", time);
	if (time!=0) {
		//GameInfo info;
		SCREEN *screen = get_screen(SCREEN_GAME);
		GameInfo *info = screen->data;
		info->passage = passages[passageID];
		info->passageID = passageID;
		info->time= time;
		set_screen(screen);
		//setEventHandler(gameEvent, &info);
	}
}

void no_footer(char c) {}

SCREEN* screen_passage() {
	SCREEN *screen = create_menu("Type the letter of the career you choose.", 0x7,0x4, 32,4, MENU_NO_SPACES, ipassages,NULL);
	((MENU*)screen->data)->select_item = select_passage;
	((MENU*)screen->data)->select_footer = no_footer;
	return screen;
}

SCREEN* screen_passage_time() {
	SCREEN *screen = create_menu(NULL, 0x1,0xF, 20,9, MENU_HIDE_INDEX, times,NULL);
	((MENU*)screen->data)->select_item = select_time;
	((MENU*)screen->data)->select_footer = no_footer;
	return screen;
}

