#include <stdio.h>
#include <stdlib.h>

#define ROWS    2
#define COLS    3

int main(void) {

    // Array bidimensionale e' sinonimo di matrice
    // Dichiarazione di una matrice di tipo intero
    int matrix_a[ROWS][COLS];

    // Inizializzazione contestualmente alla dichiarazione
    // Valgono comunque le regole per i vettori
    int matrix_b[ROWS][COLS] = { {10, 20, 30},
                                 {40, 50, 60} };

    // Accesso agli elementi
    int num = matrix_b[0][1]; // Si assegna 20

    return(EXIT_SUCCESS);
}
