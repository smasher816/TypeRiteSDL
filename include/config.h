#if (defined(_WIN16) || defined(_WIN32) || defined(_WIN64)) && !defined(__WINDOWS__)
#define __WINDOWS__
#endif

#define VERSION 1

#include "setting.h"

//FLAGS
#define RAINBOW 1
#define IGNORE_BAD_CHAR 1
//#define CAN_BACKSPACE 1
//#define SPACE_NEWLINE 1
#define NEW_WPM 1
//#define CONTINUE_SAME_LINE 1

//VIDEO
//#define FULLSCREEN 1
#define DOUBLEBUF
#define RES_X 640
#define RES_Y 400

//TYPING
#define REPEAT_DELAY 250
#define REPEAT_RATE 25
#define SAFETY_TIME 5000

//SCORING
#define WORD_SIZE 5
#define ERROR_WEIGHT WORD_SIZE

//MISC
#define TITLE "TypeR"
#define VIDEO_FLAGS 0 //SDL_OPENGL

//DATABASE
//#define USE_DB 1
#define DB_PORT 0
#define DB_NAME "typerite"
#include "db/development.h"
//#include "db/standrews.h"
//#include "db/stpats.h"

