#include <stdio.h>
#include "sqlite3.h"

int sqliate3_main(int argc, char* argv[])
{
	sqlite3 *database;
	if(sqlite3_open("second.db", &database) != SQLITE_OK) {
		sqlite3_close(database);
		printf("error\n");
	}
	return 0;
}
