#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Lo scopo del programma e' di stampare ciascun elemento dell'array di
puntatori */

int main(int argc, char *argv[]) {
   char *array[] = {"campobasso",
      "roma", "napoli", "venezia",
      "verona","torino", "milano",
      "genova","palermo","catania",
      "bari","firenze"};
   
   int x, y;
   
   /* Calcola il numero degli elementi presenti nel vettore di stringhe */
   int len = sizeof(array) / sizeof(char *);	
   
   for (x=0; x<len; x++) {
      for (y=0; y<=strlen(array[x]); y++)
      	 printf("%c", array[x][y]);
      printf("\n");
   }
   
   return(EXIT_SUCCESS);
}
