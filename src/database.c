#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <mysql.h>
#include <font.h>

#include "config.h"
#include "database.h"

#define DB_FLAGS 0 //CLIENT_MULTI_STATEMENTS
MYSQL *sql;

int userID = -1;
int studentID = -1;

void error(int fatal) {
	int errnum = mysql_errno(sql);
	fprintf(stderr, "SQL error %i: %s\n", errnum, mysql_error(sql));
	if (fatal) {
		mysql_close(sql);
		exit(errnum);
	}
}

void printResult(MYSQL_RES *result) {
	int fields = mysql_num_fields(result);

	int col;
	MYSQL_ROW row;
	MYSQL_FIELD *field;

	while ((row = mysql_fetch_row(result))) {
		for(col=0; col<fields; col++) {
			if (col==0) {
				while((field = mysql_fetch_field(result))) {
					printf("| %s ", field->name);
				}
				printf("|\n");
			}
			printf("| %s ", row[col] ? row[col]:"NULL");
		}
		printf("|\n");
	}

	//mysql_free_result(result);
}

void db_init() {
	color(0x4, 0x7); cls();
	mvabs(20,7); dprints("Connecting to server...");
	redraw();

	sql = mysql_init(0);
	if (!mysql_real_connect(sql, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, NULL, DB_FLAGS)) {
		color(0x4, 0x7); cls();
		mvabs(20,7); dprints("Error connecting to server.");
		mvabs(20,9); dprints("Please restart the program and try again later.");
		redraw();
		pressAnyKey();
		error(1);
	}

	printf("MySQL connection opened: %s\n", mysql_get_host_info(sql));
}

void db_quit() {
	mysql_close(sql);
	printf("MySQL connection closed.\n");
}

int db_exec(const char *query, ...) {
	char buffer[255];
	va_list args;
    va_start(args,query);
    vsprintf(buffer,query,args);
    va_end(args);

	if (mysql_query(sql, buffer)!=0) {
		fprintf(stderr, "Error in SQL: %s\n", buffer);
		return 1;
	}
	return 0;
}

MYSQL_RES* db_query(const char *query) {
	if (db_exec(query)) {
		MYSQL_RES *result = mysql_store_result(sql);
		printResult(result);
		mysql_free_result(result);
		//return result;
	}
	return NULL;
}

int db_login(char *username, char *password) {
	db_exec("SELECT UserID FROM User WHERE UserName=\"%s\" AND Password=PASSWORD(\"%s\")",username, password);
	MYSQL_RES *user = mysql_store_result(sql);

	MYSQL_ROW row = mysql_fetch_row(user);
	if (row!=NULL) {
		userID = atoi(row[0]);
		mysql_free_result(user);

		db_exec("SELECT StudentID FROM Student WHERE Student.UserID=%i",userID);
		MYSQL_RES *student = mysql_store_result(sql);
		row = mysql_fetch_row(student);
		studentID = atoi(row[0]);
		mysql_free_result(student);
		printf("Logged In. UserID=%i, StudentID=%i\n", userID, studentID);
		return userID;
	} else {
		printf("Invalid Username/Password\n");
		return 0;
	}
}

void db_write_test(int chars, int errors, int time, int passage) {
	db_exec("INSERT INTO Test (StudentID, Time, CharCount, ErrorCount, Duration, PassageID) VALUES (%i, NOW(), %i, %i, %i, %i)", studentID, chars, errors, time, passage);
}
