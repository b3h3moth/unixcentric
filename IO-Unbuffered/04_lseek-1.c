#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>  
#include <unistd.h> 
#include <string.h> 

#define MAX_BUF 128
#define PERMS 0644

/*
Legge il contenuto del file 'input_file' e copia MAX_BUF byte in 'output_file';
mediante la lseek si individua l'offset da cui copiare, ossia l'inizio del
file.
*/

int main(int argc, char *argv[], char *envp[])
{
   int fd1, fd2;
   char *input_file = "/etc/passwd";
   char *output_file = "passwd.txt";
   char buf[MAX_BUF];
   int n;

   if ( (fd1 = open(input_file, O_RDONLY)) < 0) {
      printf("Err. apertura %s\n", input_file);
      exit(EXIT_FAILURE);
   }

   if ( (fd2 = open(output_file, O_RDWR | O_CREAT, PERMS)) < 0) {
      printf("Err. apertura %s\n", input_file);
      exit(EXIT_FAILURE);
   }


   /* 
    Legge MAX_BUF byte da 'input_file' e li copia successivamente con la
    write in 'output_file'; si lavora un byte per volta. 
   */
   if ((n=read(fd1, &buf, MAX_BUF)) < 0) {
      fprintf(stderr, "Err. read\n");
      exit(EXIT_FAILURE);
   }

   lseek(fd1, 32, SEEK_SET );
   if (write(fd2, &buf, n) < 0) {
      fprintf(stderr, "Err. write\n");
      exit(EXIT_FAILURE);
   }

   close(fd1);
   close(fd2);
   
   return(EXIT_SUCCESS);
}
