#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include "config.h"
#include "font.h"

#ifdef RAINBOW
#include "rainbow.h"
SDL_Texture *overlay;
#endif

SDL_Renderer *renderer;
SDL_Texture *display;

SDL_Texture *Font[0xF+1];
SDL_Rect chars[256];
SDL_Color Color[0xF+1] = {
	[0x0] = {0x00, 0x00, 0x00, 0xFF},
	[0x1] = {0x00, 0x00, 0xA8, 0xFF},
	[0x2] = {0x00, 0xA8, 0x00, 0xFF},
	[0x3] = {0x00, 0xA8, 0xA8, 0xFF},
	[0x4] = {0xA8, 0x00, 0x00, 0xFF},
	[0x5] = {0xA8, 0x00, 0xA8, 0xFF},
	[0x6] = {0xA8, 0x54, 0x00, 0xFF},
	[0x7] = {0xA8, 0xA8, 0xA8, 0xFF},
	[0x8] = {0x54, 0x54, 0x54, 0xFF},
	[0x9] = {0x54, 0xFC, 0xFC, 0xFF},
	[0xA] = {0x54, 0xFC, 0x54, 0xFF},
	[0xB] = {0x54, 0xFC, 0xFC, 0xFF},
	[0xC] = {0xFC, 0x54, 0x54, 0xFF},
	[0xD] = {0xFC, 0x54, 0xFC, 0xFF},
	[0xE] = {0xFC, 0xFC, 0x54, 0xFF},
	[0xF] = {0xFC, 0xFC, 0xFC, 0xFF}
};


SDL_Point cursor;
Cursor_Color cursor_color = {0,7}; //0x8,0xA
char buffer[SCREEN_WIDTH];

/*
0 = Black	8 = Gray
1 = Blue	9 = Light Blue
2 = Green	A = Light Green
3 = Aqua	B = Light Aqua
4 = Red		C = Light Red
5 = Purple	D = Light Purple
6 = Yellow	E = Light Yellow
7 = White	F = Bright White
*/

void mvabs(int x, int y) {
	cursor.x = x;
	cursor.y = y;
}

void mvrel(int x, int y) {
	cursor.x += x;
	cursor.y += y;
}

void redraw() {
#ifdef DOUBLEBUF
	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderCopy(renderer, display, NULL, NULL);
	#ifdef RAINBOW
		SDL_RenderCopy(renderer, overlay, NULL, NULL);
	#endif
#endif
	SDL_RenderPresent(renderer);
}

void cls() {
	mvabs(0,0);
	SDL_Color c = Color[cursor_color.bg];
#ifdef DOUBLEBUF
	SDL_SetRenderTarget(renderer, display);
#endif
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
	SDL_RenderClear(renderer);
}

void black(int y) {
	SDL_Rect blk;
	blk.x=0;
	blk.w=RES_X;
	blk.y = CHAR_HEIGHT*y;
	blk.h = CHAR_HEIGHT*(SCREEN_HEIGHT-y);
	SDL_Color c = Color[cursor_color.bg];

	SDL_SetRenderTarget(renderer, display);
	SDL_SetRenderDrawColor(renderer, c.r,c.g,c.b, 255);
	SDL_RenderFillRect(renderer, &blk);
	redraw();
}

void scroll(int lines) {
	SDL_Rect src;
	src.x=0;
	src.w=RES_X;
	src.y = CHAR_HEIGHT*lines;
	src.h = CHAR_HEIGHT*(SCREEN_HEIGHT-lines);

	SDL_Rect dst;
	dst.x=0;
	dst.w=RES_X;
	dst.y = 0;
	dst.h = CHAR_HEIGHT*(SCREEN_HEIGHT-lines);

	SDL_SetRenderTarget(renderer, display);
	SDL_RenderCopy(renderer, display, &src, &dst);
	black(SCREEN_HEIGHT-lines);

	cursor.y -= lines;
	if (cursor.y<0) {
		cursor.y = 0;
	}
}

void color(int _bg, int _fg) {
	cursor_color.bg = _bg;
	cursor_color.fg = _fg;
}

SDL_Color getSDLColor(int code) {
	return Color[code];
}

Cursor_Color getcolor() {
	return cursor_color;
}

void font_init(SDL_Window *window, unsigned char* bmp) {
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	SDL_RenderSetLogicalSize(renderer, RES_X, RES_Y);
#ifdef DOUBLEBUF
	display = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, RES_X, RES_Y);
#endif

	SDL_RWops *z = SDL_RWFromMem(bmp,33914);
	SDL_Surface *image = SDL_LoadBMP_RW(z,1);
	SDL_Surface *LoadFont = SDL_ConvertSurface(image, image->format, (Uint32)0);
	SDL_FreeSurface(image);
	//SDL_RWclose(z);

	int c;
	for(c=0; c<256; c++) {
		chars[c].x = CHAR_WIDTH*(c%16);
		chars[c].y = CHAR_HEIGHT*(c/16);
		chars[c].w = CHAR_WIDTH;
		chars[c].h = CHAR_HEIGHT;
	}

	SDL_SetColorKey(LoadFont,SDL_TRUE,SDL_MapRGB(LoadFont->format, 0x00,0x00,0x00)); //0xFF,0xFF,0xFF));

	int i;
	for(i=0; i<=0xF; i++) {
		//SDL_Surface *s = SDL_ConvertSurface(LoadFont, LoadFont->format, (Uint32)0);
		//SDL_FillRect(s,NULL,SDL_MapRGB(s->format, Color[i].r, Color[i].g, Color[i].b));
		//SDL_BlitSurface(LoadFont,NULL,s,NULL);
		//SDL_SetColorKey(s,SDL_TRUE,SDL_MapRGB(s->format,0,0,0));
		Font[i] = SDL_CreateTextureFromSurface(renderer, LoadFont);//s);
		SDL_SetTextureColorMod(Font[i],Color[i].r, Color[i].g, Color[i].b);
	}
	SDL_FreeSurface(LoadFont);

#ifdef RAINBOW
	rainbow_init(renderer, &overlay);
#endif

	cls();
}

SDL_Point getpos() {
	return cursor;
}

void draw_char(char c) {
	SDL_Rect character;
	character.w = CHAR_WIDTH;
	character.h = CHAR_HEIGHT;
	character.x = CHAR_WIDTH*cursor.x;
	character.y = CHAR_HEIGHT*cursor.y;

	SDL_Rect offset = chars[(unsigned char)c];
	SDL_Color bg = Color[cursor_color.bg];
#ifdef DOUBLEBUF
	SDL_SetRenderTarget(renderer, display);
#endif
	SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
	SDL_RenderFillRect(renderer, &character);
	//SDL_BlitSurface(Font[cursor_color.fg], &offset, screen, &character);*/
	SDL_RenderCopy(renderer, Font[cursor_color.fg], &offset, &character);
}

void printc(char c) {
	if (c=='\b') {
		cursor.x--;
	} else if (c=='\f') {
		cls();
	} else if (c=='\n') {
		cursor.x = 0;
		cursor.y++;
	} else if (c=='\r') {
		cursor.x = 0;
	} else if (c=='\v') {
		cursor.y++;
	} else if (c=='\t') {
		int i;
		for (i=0; i<TAB_SIZE; i++) {
			printc(' ');
		}
	} else {
		draw_char(c);
		cursor.x++;
		if (cursor.x>SCREEN_WIDTH) {
			cursor.x = 0;
			cursor.y++;
		}
		if (cursor.y>=SCREEN_HEIGHT) {
			printf("FORCED CLS\n");
			cls();
			redraw();
		}
	}
}

void dprintc(char c) {
	printc(c);
	//SDL_UpdateRect(screen, CHAR_WIDTH*(cursor.x-1), CHAR_HEIGHT*cursor.y, CHAR_WIDTH, CHAR_HEIGHT);
}

void mvprintc(int x, int y, char c) {
	mvabs(x,y);
	printc(c);
}

void prints(char* format, ...) {
	va_list args;
    va_start(args,format);
    int len = vsprintf(buffer,format,args);
    va_end(args);

	int i;
	for (i=0;i<len;i++) {
		printc(buffer[i]);
	}
}

void dprints(char *format, ...) {
	va_list args;
    va_start(args,format);
    int len = vsprintf(buffer,format,args);
    va_end(args);

	int i;
	for (i=0;i<len;i++) {
		printc(buffer[i]);
	}
	/*SDL_Point _cursor = cursor;

	va_list args;
    va_start(args,format);
    int len = vsprintf(buffer,format,args);
    va_end(args);

	int i;
	for (i=0;i<len;i++) {
		printc(buffer[i]);
	}

	SDL_UpdateRect(screen, CHAR_WIDTH*_cursor.x,CHAR_HEIGHT*_cursor.y,CHAR_WIDTH*(cursor.x-_cursor.x),CHAR_HEIGHT*(cursor.y-_cursor.y+1));*/
}

void mvprints(int x, int y, char* str) {
	mvabs(x,y);
	prints(str);
}

void font_test() {
	cls();
	unsigned char c=' ';
	for (c=0; c<255; c++) {
		printc(c);
		redraw();
		SDL_Delay(100);
	}
	redraw();
}

void pressAnyKey() {
	SDL_Event e;
	while (1) {
		while(SDL_PollEvent(&e)) {
			if (e.type==SDL_KEYDOWN||e.type==SDL_QUIT) {
				return;
			}
		}
	}
}
