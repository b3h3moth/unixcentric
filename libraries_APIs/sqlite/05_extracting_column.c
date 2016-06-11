#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

/* Lo scopo del programma e' l'estrazione dei dati da una colonna della tabella
mediante la creazione di una 'Prepared Statement'. Il nome del database e' 
fornito in input */

int main(int argc, char *argv[]) {
    sqlite3      *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int          res = 0;
    char         *sql_str = "SELECT * FROM addressbook ORDER by id";
    int          flags = SQLITE_OPEN_READONLY;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <database name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Inizializzazione della libreria
    if (sqlite3_initialize() != SQLITE_OK) {
        fprintf(stderr, "Err. Unable to initialize the library.\n");
        exit(EXIT_FAILURE);
    }

    /* Creazione della connessione al database */
    res = sqlite3_open_v2(argv[1], &db, flags, NULL);

    if (res != SQLITE_OK) {
        fprintf(stderr, "Err. can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    // Creazione della "Prepared Statement".
    if (sqlite3_prepare_v2(db, sql_str,-1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Err. Unable to create Prepared Statement.\n");
        exit(EXIT_FAILURE);
    }

    // Stampa il nome della colonna
    printf("%2s %10s %8s %14s\n", sqlite3_column_name(stmt, 0), \
            sqlite3_column_name(stmt, 1), \
            sqlite3_column_name(stmt, 2), \
            sqlite3_column_name(stmt, 3) );

    /* Estrazione dei dati riga per riga
    La funzione sqlite3_column_text() estrae i dati dalla colonna specificata
    nella 'Prepared Statement', che nel caso specifico e' del testo; ritorna
    un puntatore const di tipo void, per cui il cast e' necessario per evitare
    messaggi di warning del compilatore, o peggio */

    /* 1° tecnica, usando un semplice ciclo while
    const char   *data = NULL;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        data = (const char*)sqlite3_column_text(stmt, 0);
        printf("'%s\'\n", data ? data : "empty");
    }
    */
    
    /* 2° tecnica, un 'for loop' all'interno di un 'while loop', si utilizza
    peraltro la funzione di supporto sqlite3_column_count() per il conteggio
    del numero di colonne da estrarre */
    while (sqlite3_step(stmt) == SQLITE_ROW)
        printf("%2d %10s %8s %14s\n", sqlite3_column_int(stmt, 0), \
                (const char*)sqlite3_column_text(stmt, 1),      \
                (const char*)sqlite3_column_text(stmt, 2),      \
                (const char*)sqlite3_column_text(stmt, 3) );

    /* In questo caso il tipo di dato estratto e' del testo, ma ci possono 
    essere tuttavia dei casi in cui sarebbe oltremodo necessario verificare il
    il tipo dato estratto (storage class) prima di stamparlo, come ad esempio
    SQLITE_TEXT, il cui valore intero e' 3.  */

    // Rilascio delle risorse relative alla Prepared Statement
    if (sqlite3_finalize(stmt) != SQLITE_OK) {
        fprintf(stderr, "Err. Unable to finalize.\n");
        exit(EXIT_FAILURE);
    }

    // Close database connection
    if (sqlite3_close_v2(db) != SQLITE_OK) {
        fprintf(stderr, "Err. Unable to close connection.\n");
        exit(EXIT_FAILURE);
    }

    // Rilascio delle risorse dell'inizializzazione
    sqlite3_shutdown();

    return(EXIT_SUCCESS);
}
