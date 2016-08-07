#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sqlite3.h>

// Function Prototypes
static int create_table(sqlite3 *db);
static int write_blob(sqlite3* db, void *blb_data, int blb_sz);

int main(int argc, char *argv[]) {
    // Connessione al database
    sqlite3        *db = NULL;
    // 1 = scrivere BLOB nel DB | 0 = leggere BLOB dal DB
    bool is_write = 0; 
    // Il file descriptor
    int fd = 0;
    // Il risultato delle chiamate
    int rc = 0;
    // Datbase flags
    int flags = SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE;
    // Il peso del file da inserire nel database
    struct stat fstatus = {0};
    // Il peso del tipo di dato blob
    int blob_size = 0;
    // Salva il tipo di dato blob
    unsigned char *data_blob = NULL;
    // Il filename del database
    char const *file_db = NULL;
    // Il file da scrivere nel database o da leggere dal database stesso
    char const *file_wr = NULL;

    // Verifica gli argomenti della linea di comando
    if (argc != 4) {
        fprintf(stderr, "Usage: %s [DB name] (write | read) [FILE]\n", argv[0]);
        return 1;
    }

    file_db = argv[1];
    file_wr = argv[3];

    /* Verifica la prima lettera del terzo argomento, nel caso di esito 
    positivo si imposta la variabile is_write ad 1, ovvero che si procedera'
    alla scrittura di un dato binario nel database.  */
    if (argv[2][0] == 's' || argv[2][0] == 'S') {
        is_write = 1;
    }

    // Apre una connessione al database
    rc = sqlite3_open_v2(file_db, &db, flags, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Err. Open Database Connection failed: %d - %s\n", \
                sqlite3_errcode(db), sqlite3_errmsg(db));
        return 1;
    }

    if (is_write) {
        create_table(db);

        // Apertura del file ricevuto come argomento e infine calcolo del peso
        fd = open(file_wr, O_RDONLY);
        if (fd < 0) {
            fprintf(stderr, "Err. Open file: %s - %s\n", \
                    strerror(errno), file_wr);
            return 1;
        }

        if (fstat(fd, &fstatus) != 0) {
            fprintf(stderr, "Err. Stat file: %s - %s\n", \
                    strerror(errno), file_wr);
            return 1;
        }

        blob_size = fstatus.st_size;

        /* Allocazione dello spazio necessario per il file 'file_wr', lettura e
        infine chiusura dello stesso */
        data_blob = malloc(blob_size);
        if (blob_size != read(fd, data_blob, blob_size)) {
            fprintf(stderr, "Err. Read file: %s - %s\n", \
                    strerror(errno), data_blob);
            return 1;
        }

        close(fd);

        /* Scrive il tipo di dato BLOB nel database, rilascia inoltre la memoria
        precedentemente allocata */
        if (SQLITE_OK != write_blob(db, file_wr, data_blob, blob_size)) {
            fprintf(stderr, "Err. Write BLOB to database %d:%s\n", \
                    sqlite3_errcode(db), sqlite3_errmsg(db));
            return 1;
        }

        free(data_blob);
    }


    return(EXIT_SUCCESS);
}

// Crea la tabella nel database 'db'
static int create_table(sqlite3 *db) {
    const char *sql = "CREATE TABLE blobs(id INTEGER PRIMARY KEY, data BLOB)";
    return sqlite3_exec(db, sql, 0, 0, 0);
}

// Scrive il tipo BLOB nel database
static int write_blob(sqlite3* db, void *blb_data, int blb_sz) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO blobs(id, data) VALUES(?, ?)";
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Err. Unable to create Prepared Statement %d:%s\n", \
                sqlite3_errcode(db), sqlite3_errmsg(db));
        return 1;
    }


