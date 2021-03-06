#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define KEY '\\'

/* Lo scopo del programma e' di eseguire uno XOR con una chiave su ciascun 
carattere di una stringa o di un file */

int main(void) {
    int original_char, new_char;

    while((original_char = getchar()) != EOF) {
        new_char = original_char ^ KEY; // XOR between 0 and KEY

        if (isprint(original_char) && isprint(new_char))
            //putchar(new_char);
            printf("%c", new_char);
        else
            //putchar(original_char);
            printf("%c", original_char);
    }

    return(EXIT_SUCCESS);
}

/* 
Encrypt file.txt:
$ ./a.out < file.txt > new_file.txt

Decrypt new_file.txt:
$ ./a.out  < new_file.txt
*/
