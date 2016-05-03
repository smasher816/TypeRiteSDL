#pragma once

typedef struct Passage {
	char code;
	char *name;
	char *(*text)[];
	int length;
} Passage;

/*extern char *text_A[];
extern char *text_C[];
extern char *text_D[];
extern char *text_E[];
extern char *text_G[];
extern char *text_H[];
extern char *text_I[];
extern char *text_J[];
extern char *text_L[];
extern char *text_M[];
extern char *text_N[];
extern char *text_O[];
extern char *text_P[];
extern char *text_S[];
extern char *text_T[];
extern char *text_W[];

Passage passage_A;
Passage passage_C;
Passage passage_D;
Passage passage_E;
Passage passage_G;
Passage passage_H;
Passage passage_I;
Passage passage_J;
Passage passage_L;
Passage passage_M;
Passage passage_N;
Passage passage_O;
Passage passage_P;
Passage passage_S;
Passage passage_T;
Passage passage_W;*/

extern Passage *passages[];
