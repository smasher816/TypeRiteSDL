#include <SDL.h>
//#include "menu.h"
//#include "game.h"

int active;

typedef struct Event {
	void (*init)(void*);
	void (*event)(SDL_Event*);
	void (*loop)();
} Event;
Event event;

void setEventHandler(Event e, void *data);
int handle_event(SDL_Event *e);
void noop();

Uint32 userEventTypes;
#define NUM_EVENTS 2
#define EVENT_FINISHED (userEventTypes+0)
#define EVENT_REPLAY (userEventTypes+1)

//Event loginEvent;
Event screenEvent;
//Event gameEvent;
//Event replayEvent;
