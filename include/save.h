#include <stdint.h>
#include "tinydir.h"

#define REPLAY_DIR "./replays"

typedef struct ReplayItem {
	uint8_t letter;
	uint8_t correct;
	uint32_t time;
} ReplayItem;

typedef struct Replay {
	uint8_t passage;
	uint16_t time;
	uint16_t items;
	ReplayItem *data;
} Replay;

tinydir_dir dir;
int replayRunning;

void saveReplay(char *name, Replay replay);
Replay loadReplay(char *name);
void runReplay(char *name);

void getFiles(tinydir_dir *dir, const char *path);
int datesort(const void* file1, const void* file2);

