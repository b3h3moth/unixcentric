#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Lo scopo del programma e' di verificare la correttezza della somma algebrica
tra due valori in complemento a due, e quindi di segnalare un eventuale
overflow, sia positivo sia negativo */

int check_overflow(int x, int y);
int sum(int x, int y);

int main(void) {
    int val1 = 2147483646;
    int val2 = 1;
    int val3 = 2;

    printf("MAX_INT: %11d\n", INT_MAX);
    printf("MIN_INT: %11d\n", INT_MIN);

    int res1 = check_overflow(val1, val2);
    printf("%d + %d = %11d (returns: %d)\n", val1, val2, val1+val2, res1);

    int res2 = check_overflow(val1, val3);
    printf("%d + %d = %11d (resturns: %d - overflow)\n", \
            val1, val3, val1+val3, res2);

    int res3 = sum(val1, val2);
    printf("%d + %d = %11d (returns: %d)\n", val1, val2, val1+val2, res3);
    
    int res4 = sum(val1, val3);
    printf("%d + %d = %11d (resturns: %d - overflow)\n", \
            val1, val3, val1+val3, res4);

    return(EXIT_SUCCESS);
}

/* La funzione check_overflow() ritorna 0 nel caso si dovesse verificare un
overflow, ritorna 1 nel caso la somma fosse corretta */
int check_overflow(int x, int y) {
    int sum = x + y;

    /* Just another method
    return (INT_MAX <= sum || sum < INT_MIN); */

    int negative_overflow = x < 0 && y < 0 && sum >= 0;
    int positive_overflow = x >= 0 && y >= 0 && sum < 0;

    /* Se si sommano due numeri dello stesso segno, allora si ha overflow se e 
    solo se il risultato ha segno opposto */

    return !negative_overflow && !positive_overflow;
}

/* La funzione sum() ritorna 1 nel caso la somma fosse corretta, ritorna 0
nel caso di un overflow */ 
int sum(int x, int y) {
    return (!check_overflow(x, y));
}

/* In pratica si utilizza direttamente la funzione sum() per verfificare il 
risultato, avendo comunque a supporto la funzione check_overflow() per la 
correttezza */
