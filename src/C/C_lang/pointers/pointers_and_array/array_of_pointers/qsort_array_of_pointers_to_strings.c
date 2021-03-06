#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ARR_SIZE ( sizeof(country) / sizeof(country[0]) )

static int compare(const void *str1, const void *str2) {
    return strcmp (*(const char **) str1, *(const char **) str2);
}

/* Lo scopo del programma e' di ordinare un array di puntatori a stringhe
mediante la funzione qsort(), dichiara in stdlib.h */

int main(void) {
    int i;
    const char *country[] = {
        "Italy", "Serbia",
        "Spain", "Iraq",
        "Greece", "Kenya",
        "USA", "Laos",
        "France", "Bolivia",
        "UK", "Australia",
        "China", "South Africa",
        "Japan", "Chile",
        "Zimbabwe", "Zambia",
        "Russia", "Pakistan",
        "Afghanistan", "Nepal",
        "Jamaica", "Ghana",
    };
    
    qsort (country, ARR_SIZE, sizeof(char *), compare);
    
    for (i=0; i<ARR_SIZE; i++) {
        printf ("[%.2d %12s]\n", i, country[i]);
    }

    return(EXIT_SUCCESS);
}
