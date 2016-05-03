#include "config.h"
#include "menu.h"
#include "font.h"

#include <stdlib.h>
#include <string.h>
#include <SDL.h>

void print_centered(int y, char *text) {
	int len = strlen(text);
	mvprints((SCREEN_WIDTH-len)/2,y, text);
}

void draw_menu(void *data) {
	MENU *menu = (MENU*)(data);
	if (menu->title!=NULL) {
		print_centered(2, menu->title);
	}

	if (menu->items!=NULL) {
		for (int i=0; menu->items[i].text!=NULL; i++) {
			mvabs(menu->x,menu->y+i*((menu->flags&MENU_NO_SPACES)?1:2));
			if (menu->flags&MENU_AUTO_INDEX) {
				prints("%c\t", '1'+i);
				menu->items[i].code = '1'+i;
			} else if (menu->items[i].code!='\0' && !(menu->flags&MENU_HIDE_INDEX)) {
				prints("%c\t", menu->items[i].code);
			} else {
				//do nothing  //prints(" \t");
			}
			prints("%s", menu->items[i].text);
		}
	}

	if (menu->footer!=NULL) {
		mvabs(1,24);
		for (int i=0; menu->footer[i].text!=NULL; i++) {
			prints("%c %s\t\t", menu->footer[i].code, menu->footer[i].text);
		}
	}
}

void menu_event(SDL_Event *e) {
	MENU *current_menu = current_screen->data;

	switch(e->type) {
		case SDL_KEYDOWN: {
			SDL_Keycode key = e->key.keysym.sym;
			char c;

			if (current_menu->items!=NULL) {
				for (int i=0; ((c=current_menu->items[i].code)!='\0'); i++) {
					if (key==c || key==(c|32)) { //make lowercase
						printf("Selected item '%c'\n", c);
						current_menu->select_item(c);
						return;
					}
				}
			}

			if (current_menu->footer!=NULL) {
				for (int i=0; ((c=current_menu->footer[i].code)!='\0'); i++) {
					if (key==c || key==(c|32)) { //make lowercase
						printf("Selected action '%c'\n", c);
						current_menu->select_footer(c);
						return;
					}
				}
			}
			break;
		}
	}
}

SCREEN* create_menu(char *title, int bg, int fg, int x, int y, int flags, MENU_ITEM *items, MENU_ITEM *footers) {
	MENU *menu = malloc(sizeof(MENU));
	menu->title=title;
	menu->x=x; menu->y=y;
	menu->flags = flags;
	menu->items=items; menu->footer=footers;

	SCREEN *screen = create_screen(NULL, bg, fg, draw_menu, menu_event);
	screen->data = menu;
	return screen;
}

