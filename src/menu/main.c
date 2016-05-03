#include "menu.h"
#include "updater.h"

#include "config.h"
#include "font.h"
#include "event.h"

MENU_ITEM menu_items[] = {
	{"Timed Test"},
	{"Practice"},
	/*{"Lessons"},*/
	{NULL, '\0'}
};

MENU_ITEM footer[] = {
#ifdef USE_DB
	{"Log out", 'L'},
#endif
	{"Replays", 'R'},
	{"Update", 'U'},
	{NULL, '\0'}
};

void select_item(char code) {
	int index = code-'0';
	switch(index) {
		case 1:
			show_screen(SCREEN_PASSAGE);
			break;
		case 2:
			printf("Practice\n");
			break;
	}
}

void select_footer(char code) {
	switch(code) {
		case 'L':
			show_screen(SCREEN_LOGIN);
			break;
		case 'R':
			show_screen(SCREEN_REPLAY);
			break;
		case 'U':
			show_screen(SCREEN_UPDATE);
			break;
	}
}

SCREEN* screen_main() {
	SCREEN *screen = create_menu("TYPE THE NUMBER OF YOUR CHOICE.", 0x4,0xF, 23,7, MENU_AUTO_INDEX, menu_items,footer);
	((MENU*)screen->data)->select_item = select_item;
	((MENU*)screen->data)->select_footer = select_footer;
	return screen;
}

