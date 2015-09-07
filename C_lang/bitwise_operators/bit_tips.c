#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* Si imposta ciascun bit a 1 con l'operatore di complemento, si sta
    operando su un unsigned short di due byte, ovvero 16 bit. Nel caso
    specifico quindi si sta impostando il valore massimo permesso da quel tipo
    di dato, ovvero 65535. */
    unsigned short us_num1 = ~0; // da 0000000000000000 a 1111111111111111

    /* E se provassi ad assegnare ad una variabile 'unsigned short' un valore 
    maggiore di una sola unita' rispetto al massimo consentito? 
    O uno o cento non fa differenza, si sara' superato il limite massimo
    (overflow), per cui sia il compilatore GCC sia il compilatore Clang (LLVM)
    troncheranno il valore della variabile impostandolo 0, il tutto condito da
    un messaggio di warning sullo stdout. */
    unsigned short us_num2 = 65536;
    unsigned short us_num3 = us_num1 + 1;

    printf("%d %d %d\n", us_num1, us_num2, us_num3);
    
    return(EXIT_SUCCESS);
}
