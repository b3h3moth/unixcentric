#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sqlite3.h>

/* Lo scopo del programma e' di inserire all'interno di un database una
immagine - tipo di dato blob - ottenuta in input. */

int main(int argc, char *argv[]) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    FILE *fp = NULL;
    int flags = SQLITE_OPEN_READWRITE;
    int flen = 0;
    int size = 0;
    int rc = 0;
    char *err_msg = 0;
    char *sql = NULL;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Per i tipi di dato 'blob' si deve lavorare con file binary
    fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        fprintf(stderr, "Err. Cannot open image: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    /* Sposta il 'file position indicator' alla fine del file, sara' utile per
    calcolare il peso dell'immagine, dopodiche' si verifica che il risultato
    sia privo di errori. */
    fseek(fp, 0, SEEK_END);

    if (ferror(fp)) {
        fprintf(stderr, "Err. fseek() failed.\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    /* La funzione ftell() ritorna la posizione corrente del 'file position
    indicator', che corrisponde anche al numero di byte del file. */
    flen = ftell(fp);

    if (flen == -1) {
        fprintf(stderr, "Err. ftell() failed: %s\n", strerror(errno));
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    // L'array che conterra' l'immagine
    char image[flen+1];

    // Lettura dal file pointer e inizializzazione dell'array
    size = fread(image, 1, flen, fp);

    if (ferror(fp)) {
        fprintf(stderr, "Err. fread() failed: %s\n", strerror(errno));
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    // Chiusura del file handler
    fclose(fp);

    rc = sqlite3_open_v2("test.db", &db, flags, NULL);

    return(EXIT_SUCCESS);
}
