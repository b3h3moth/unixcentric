#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_malloca.h"
#include "my_malloc.h"

int main(void) {
    static const char *title = "The Unix Programming Environment";
    static const unsigned int size = sizeof(title);
    char *ptr;

    // malloc(a) testing function
    // Alloca 'size' byte sullo heap, dopodiche' copia e stampa la stringa
    ptr = malloca(size);
    strcpy(ptr, title);
    printf("%s\n", ptr);

    /* Con la prima funzione per l'allocazione della memoria malloca(), non
    puo' essere usata free() per liberare la memoria, per cui si utilizzera'
    un semplice puntatore a NULL, ma non sara' di certo sufficiente. */
    ptr = NULL;

    return(EXIT_SUCCESS);
}
