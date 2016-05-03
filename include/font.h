#include <SDL.h>
#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16
#define TAB_SIZE 2

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

/*typedef struct SDL_Point {
	int x;
	int y;
} SDL_Point;*/

typedef struct Cursor_Color {
	int bg;
	int fg;
} Cursor_Color;
SDL_Color getSDLColor(int code);

//SDL_Window *window;
//SDL_Renderer *renderer;

void font_init(SDL_Window *window, unsigned char* bmp);
void draw_char(char c);
void font_test();

void redraw();
void cls();
void black(int y);
void scroll(int lines);
void color(int bg, int fg);
Cursor_Color getcolor();

void mvabs(int x, int y);
void mvrel(int x, int y);
SDL_Point getpos();

void printc(char c);
void dprintc(char c);
void mvprintc(int x, int y, char c);
void prints(char* format, ...);
void dprints(char* format, ...);
void mvprints(int x, int y, char* str);
void font_test();

void pressAnyKey();
