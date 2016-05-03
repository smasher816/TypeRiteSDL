#ifndef _MENU_H
#define _MENU_H

#include "passages.h"
#include "screen.h"
#define C2N(x) (int)(x-'A')
#define ARRAYLEN(x) (sizeof(x) / sizeof(x[0]))

#define MENU_AUTO_INDEX 1<<1
#define MENU_HIDE_INDEX 1<<2
#define MENU_NO_SPACES 1<<3

typedef struct MENU_ITEM {
	char *text;
	char code;
	//int x,y, w,h;
} MENU_ITEM;
//#define END_MENU_ITEMS {'\0', NULL}

typedef struct MENU {
	char *title;
	int x,y;
	MENU_ITEM *items;
	MENU_ITEM *footer;
	int flags;
	void (*select_item)(char);
	void (*select_footer)(char);
} MENU;

SCREEN* create_menu(char *title, int bg, int fg, int x, int y, int flags, MENU_ITEM *items, MENU_ITEM *footer);

/*typedef struct Passage_Item {
	char *title;
	Passage *item;
} Passage_Item;*/

#endif
