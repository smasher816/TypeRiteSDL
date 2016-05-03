#include <mysql.h>

void db_init();
void db_quit();
//int db_exec(const char *query);
//MYSQL_RES* db_query(const char *query);
int db_login(char *user, char *pass);
void db_write_test(int chars, int errors, int time, int passage);
