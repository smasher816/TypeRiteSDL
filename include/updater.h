#define BACKUP_NAME "typerite.bak"

//void doUpdate();
int checkUpdate(char *url);
int downloadUpdate(char *url, char *file);
void installUpdate(char *file);
