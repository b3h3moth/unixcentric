#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main(int argc, char *argv[]) {
    sqlite3 *db;
    int rc;
    char *err_msg = NULL;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <db> <SQL statement>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Apertura del database fornito come argomento
    rc = sqlite3_open(argv[1], &db);

    if (rc) {
        fprintf(stderr, "Err: Can't open DB %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    // Invio di una query SQL al database, ricevuta come argomento
    rc = sqlite3_exec(db, argv[2], callback, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Err: Can't execute SQL statement %s\n", err_msg);
        sqlite_free(err_msg);
    }


    return(EXIT_SUCCESS);
}

/* How to compile the program wih sqlite3 header:
$   gcc -std=c11 -Wall -pedantic -lsqlite3 open_database.c -o opendb
$ clang -std=c11 -Wall -pedantic -lsqlite3 open_database.c -o opendb
*/
