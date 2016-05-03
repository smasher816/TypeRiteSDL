#include "config.h"
#include "screen.h"
#include "font.h"
#include "updater.h"

void run_update() {
	char *update = "typer-update.exe";
#if defined __linux__
	#define OS "linux"
#elif defined __APPLE__
	#define OS "mac"
#elif defined __WINDOWS__
	#define OS "windows"
#endif

	prints("Checking for updates.\n"); redraw();
	if (checkUpdate("http://" DB_HOST "/bin/version")<1) {
		prints("No update available :(\n"); redraw();
		return;
	}
	prints("Downloading update.\n");
	if (!downloadUpdate("http://" DB_HOST "/bin/download.php?os=" OS, update)) {
		prints("ERRROR: Could not download update.\n"); redraw();
		return;
	}
	prints("Installing update...\n"); redraw();
	installUpdate(update);
}

SCREEN* screen_update() {
	SCREEN *screen = create_screen(NULL, 0x0,0x7, run_update, NULL);
	return screen;
}

