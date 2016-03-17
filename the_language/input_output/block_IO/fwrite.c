#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(void) {
    int val = 255;

    FILE *fp;

    if ((fp = fopen("data.bin", "ab+")) == NULL) {
        fprintf(stderr, "Err. open stream with fopen(), %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Scrive quattro byte dell'intero 'val' nel file
    fwrite(&val, sizeof(int), 1, fp);

    fclose(fp);
    return(EXIT_SUCCESS);
}
