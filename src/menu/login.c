#include "SDL.h"
#include "font.h"
#include "event.h"
#include "menu.h"
#include "config.h"
#include "database.h"

int menu_index;

char username[20], password[20];
int length;

void login_menu(int index) {
	menu_index = index;
	length = 0;
	if (index==0) {
		color(0,7);
		mvabs(25,9); dprints("Username: ");
	} else if (index==1) {
		mvabs(25,11); dprints("Password: ");
	}
	redraw();
}

void login(char *username, char *password) {
	int userID = db_login(username,password);
	if (userID) {
		//setEventHandler(menuEvent, NULL);
	} else {
		cls();
		printf("Bad login\n");
		color(0,0xC); mvabs(25,7); dprints("Incorrect Username or Password.");
		login_menu(0);
	}
}

void login_init() {
	color(0,0xF); cls();
	mvabs(25,7); dprints(TITLE); dprints(" Login");
	login_menu(0);
#ifdef DB_AUTO_AUTH
	login(DB_AUTH_USER, DB_AUTH_PASSWORD);
#endif
}

void login_event(SDL_Event *e) {
	switch(e->type) {
		case SDL_KEYDOWN: {
			SDL_Keycode key = e->key.keysym.sym;
			Uint16 code = e->key.keysym.sym; //unicode;
			if (menu_index==0) {
				if (key==SDLK_BACKSPACE && length>0) {
					printc('\b'); dprintc(' '); printc('\b');
					redraw();
					username[length] = '\0';
					length--;
				} else if (key==SDLK_RETURN) {
					login_menu(1);
				} else if (code>32 && code<126 && length<20) {
					dprintc(code);
					redraw();
					username[length] = code;
					length++;
				}
			} else if (menu_index==1) {
				if (key==SDLK_ESCAPE) {
					cls();
					login_menu(0);
				} else if (key==SDLK_BACKSPACE && length>0) {
					printc('\b'); dprintc(' '); printc('\b');
					redraw();
					password[length] = '\0';
					length--;
				} else if (key==SDLK_RETURN) {
					login(username,password);
				} else if (code>32 && code<126 && length<20) {
					dprintc('*');
					redraw();
					password[length] = code;
					length++;
				}
			}
			break;
		}
	}
}

SCREEN *screen_login() {
	SCREEN *screen = create_screen(NULL, 0x0,0x7, login_init, login_event);
	return screen;
}

