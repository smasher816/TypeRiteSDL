#include "config.h"
#include "event.h"
#include <stdlib.h>

#define CURL_STATICLIB
#include <curl/curl.h>
#include <curl/easy.h>

#if defined __linux__
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#elif defined __WINDOWS__
#include <windows.h>
#elif defined __APPLE__
#include <mach-o/dyld.h>
#include <unistd.h>
#include <sys/stat.h>
#endif

#include "updater.h"

struct buffer {
	char *data;
	int len;
};

size_t write_data(void *ptr, size_t size, size_t nmemb, struct buffer *stream) {
    const size_t len = size*nmemb;
	//printf("stream: %p, %i\n", stream->data, stream->len);
    memcpy(stream->data+stream->len, ptr, len);
    stream->len += len;
    return len;
}

char* getCurrentFile() {
#if defined __linux__
	//char procdata[1024];
	//FILE *fp = fopen("/proc/self/exe", "r");
	//fgets(procdata, sizeof(procdata), fp);
	//printf("exe: %s\n", procdata);
	char *path = realpath("/proc/self/exe", NULL);
	//*path = tmp;
	//int len = readlink("/proc/self/exe", *path, sizeof(path-1)); //procdata
	//path[len] = '\0';
	printf("abs: %s\n", path);
	return path;
#elif defined __APPLE__
	char *path = malloc(1024);
	uint32_t size = 1024; //sizeof(path);
	_NSGetExecutablePath(path, &size);
	printf("abs: %s\n", path);
	return path;
#else
	return NULL;
#endif
}

int checkUpdate(char *url) {
	printf("Checking for update - %s\n", url);
	struct buffer stream; stream.data=malloc(4096); stream.len=0;
	//printf("INIT CURL\n");
	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &stream);
	//printf("stream: %p, %i\n", stream.data, stream.len);
	//printf("Calling.\n");
	CURLcode res = curl_easy_perform(curl);
	//printf("Cleaning curl\n");
	curl_easy_cleanup(curl);
	//printf("Done\n");

	stream.data[stream.len] = '\0';

	int ret;
	if (res==CURLE_OK) {
		printf("Data: %s\n", stream.data);
		int version = atoi(stream.data);
		printf("Version: %i?%i=%i\n", version, VERSION, version>VERSION);
		ret = (version>VERSION);
	} else {
		printf("Error\n");
		ret = -1;
	}

	free(stream.data);
	return ret;
}

int downloadUpdate(char *url, char *file) {
	printf("Downloading update from - %s  ->  %s\n", url, file);
	FILE *fp = fopen(file, "wb");
	printf("FP: %p\n", fp);
	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
	CURLcode res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	fclose(fp);
	return (res==CURLE_OK);
}

void installUpdate(char *file) {
#ifdef __WINDOWS__
	TCHAR current[MAX_PATH];
	printf("Getting name.");
	GetModuleFileName(NULL, current, MAX_PATH);
	printf(" = %s\n", current);

	printf("Moving original. %s->%s\n", current, BACKUP_NAME);
	MoveFileEx(current, BACKUP_NAME, MOVEFILE_REPLACE_EXISTING);
	printf("Moving update. %s->%s\n", file, current);
	MoveFileEx(file, current, MOVEFILE_REPLACE_EXISTING);
	printf("Move complete\n");

	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi));

	printf("Launching update. %s\n", current);
	CreateProcess(current, NULL,
			NULL,NULL,FALSE,
			0,NULL,NULL,
			&si, &pi);
	printf("Commiting suicide\n");
	active = 0;
	ExitProcess(0);
#else
	//Linux+Mac are both POSIX
	char *current = getCurrentFile();
	printf("unlinking original: %s\n", current);
	unlink(current);
	printf("moving update %s->%s\n", file, current);
	rename(file, current);
	printf("chmod +x %s\n", current);
	chmod(current, S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);//S_IEXEC);

	int pid=fork();
	if (pid==0) {
		printf("Child exec new - %s\n", current);
		execl(current, current, NULL);
	} else {
		printf("Parent dies\n");
		free(current);
		exit(0);
	}
#endif
}


