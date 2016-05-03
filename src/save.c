#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <SDL.h>

#include "save.h"
#include "portable_endian.h"
#include "event.h"
#include "font.h"
#include "menu.h"
#include "passages.h"
#include "game.h"

#if defined(__WINDOWS__)
#include <direct.h>
#elif defined __GNUC__
#include <sys/stat.h>
#endif

//int replayCount = 0;
//char **replayList;
int replayRunning = 0;
SDL_Thread *thread;

void createDir(char *dir) {
#if defined(__WINDOWS__)
	_mkdir(dir);
#elif defined __GNUC__
	mkdir(dir, 0777);
#endif
}

void saveReplay(char *name, Replay replay) {
	unsigned char header[3] = {'T','R','S'};
	uint8_t passage = replay.passage; //htobe8(replay.passage);
	uint16_t time = htobe16(replay.time);
	uint16_t items = htobe16(replay.items);

	createDir(REPLAY_DIR);
	FILE *file = fopen(name, "wb");
	fwrite(&header, 1, 3, file);
	fwrite(&passage, 1, 1, file);
	fwrite(&time, 2, 1, file);
	fwrite(&items, 2, 1, file);

	int i;
	for (i=0; i<replay.items; i++) {
		uint32_t time = htobe32(replay.data[i].time);
		fwrite(&replay.data[i].letter, 1, 1, file);
		fwrite(&replay.data[i].correct, 1, 1, file);
		fwrite(&time, 4, 1, file);
	}
	fclose(file);
	//printf("Saved replay %s!\n", name);
}

Replay loadReplay(char *name) {
	FILE *file = fopen(name, "rb");
	Replay replay;

	unsigned char header[3];
	fread(&header, 1, 3, file);
	if (!(header[0]=='T'&&header[1]=='R'&&header[2]=='S')) {
		printf("Warning: Bad Header '%c%c%c'\n", header[0],header[1],header[2]);
		replay.items = 0;
		return replay;
	}

	uint8_t passage; uint16_t time; uint16_t items;
	fread(&passage, 1, 1, file);
	fread(&time, 2, 1, file);
	fread(&items, 2, 1, file);

	replay.passage = passage; //be8toh(passage);
	replay.time = be16toh(time);
	replay.items = be16toh(items);

	printf("Passage: %i, Time: %i, Items: %i\n", replay.passage, replay.time, replay.items);

	int i;
	replay.data = malloc(replay.items*sizeof(ReplayItem));
	for (i=0;i<replay.items;i++) {
		uint32_t time;
		fread(&((replay.data[i]).letter), 1, 1, file);
		fread(&((replay.data[i]).correct), 1, 1, file);
		fread(&time, 4, 1, file);
		replay.data[i].time = be32toh(time);
	}
	fclose(file);

	return replay;
}

static int replay_thread(void *ptr) {
	Replay replay = *((Replay*)ptr);
	//printf("Replay Thread Started! - %i events\n", replay.items);
	SDL_Event e;
	SDL_zero(e);
	e.type = EVENT_REPLAY;
	for (int i=0; i<replay.items+1; i++) {
		e.user.code = replay.data[i].letter;
		if (replayRunning) {
			SDL_PushEvent(&e);
			SDL_Delay(replay.data[i+1].time-replay.data[i].time);
		} else {
			break;
		}
	}
	free(replay.data);
	return 0;
}

void runReplay(char *name) {
	printf("Loading replay: %s\n", name);
	Replay replay = loadReplay(name);

	if (replay.items>0) {
		//GameInfo info;
		replayRunning = 1;
		SCREEN *screen = get_screen(SCREEN_GAME);
		GameInfo *info = screen->data;
		info->passage = passages[replay.passage];
		info->passageID = replay.passage;
		info->time = replay.time;
		set_screen(screen);
		//setEventHandler(gameEvent, &info);

		thread = SDL_CreateThread(replay_thread, "replay", (void*)(&replay));
	}
}

int datesort(const void* file1, const void* file2) {
	struct stat info1, info2;
	stat(((tinydir_file*)file1)->path, &info1);
	stat(((tinydir_file*)file2)->path, &info2);

	double diff = difftime(info2.st_mtime, info1.st_mtime);
	if (diff<0) {return -1;}
	if (diff>0) {return 1;}
	if (diff==0) {return 0;}
	return diff;
}

//based upon tinydir_open_sorted
void getFiles(tinydir_dir *dir, const char *path) {
	//count number of files
	size_t n_files = 0;
	tinydir_open(dir, path);
	while (dir->has_next) {
		n_files++;
		tinydir_next(dir);
	}
	tinydir_close(dir);

	//populate data
	tinydir_open(dir, path);
	dir->n_files = 0;
	dir->_files = (tinydir_file*)malloc(n_files * (sizeof *dir->_files));
	while (dir->has_next) {
		tinydir_file *file;
		file = &dir->_files[dir->n_files];
		tinydir_readfile(dir, file);
		if (strcmp(file->extension, "sav") == 0) {
			dir->n_files++;
		}
		tinydir_next(dir);
	}
}

//Event replayEvent = {replay_init,replay_event,no_loop};
