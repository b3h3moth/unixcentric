#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Lo scopo del programma e' di leggere uno o piu' file in input e di stampare
su stdout i caratteri speciali */

int main(int argc, char *argv[]) {
    int ch;
    int strip = 0; // taglia dalla visione i caratteri speciali

    while (argc > 1 && argv[1][0] == '-') {
        switch (argv[1][1]) {
            case 's':
                strip = 1;
                break;
            default:
                fprintf(stderr, "%s: Unknow argument %s\n", argv[0], argv[1]);
                exit(EXIT_FAILURE);
        }
    }

    return(EXIT_SUCCESS);
}

void visible_chars(FILE *fp) {
    while ((ch = getchar()) != EOF) {
        if (isascii(ch) && (isprint(ch) || ch == '\n' || ch == '\t' || ch == ' '))
            fputc(ch, stdout);
        else if (!strip)
            printf("\\%03o", ch);
    }
}

