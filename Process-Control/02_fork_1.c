#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 
#include <errno.h> 

/*
Un processo esistente puo' creare un nuovo processo chiamando la system call
fork(), il nuovo processo creato dalla fork() e' chiamato "Child Process" 
(Processo figlio), mentre il processo generatore e' chiamato "Parent Process"
(Processo padre); la fork() e' chiamata una volta ma ritorna due volte, una 
volta nel padre e una volta nel figlio, infatti il PID del figlio e' assegnato 
al padre mentre il PID del figlio assume valore 0.

Perche' la fork() ritorna due volte? Un processo puo' avere uno o piu' figli, il
valore di ritorno della fork() e' l'unico modo per individuare l'ultimo 'nato';
un figlio invece ha sempre un solo padre, individuabile mediante getppid(), per
cui gli si assegna pid 0, che nessun altro processo puo' avere.

HEADER    : <unistd.h>
PROTOTYPE : pid_t fork(void);
SEMANTICS : La funzione fork() crea un processo duplicando il processo chiamante
            , il nuovo processo e' chiamato processo figlio, mentre il processo
	    chiamante e' il processo genitore.
RETURNS   : 0 nel figlio, il PID del figlio nel padre in caso di successo, -1 in
            caso di errore
--------------------------------------------------------------------------------

Il Child Process e' una copia del data segment, dello stack e dello heap del 
Parent Process, tale copia e' ad uso e consumo del Child Process e pertanto non
vi e' condivisione col Parent Process; La sezione text segment invece e' 
condivisa tra Parent Process e Child Process.

Il Sistema Operativo assegna due porzioni di memoria private, una per il
Parent Process, l'altra per il Child Process, pertanto qualora uno dei due
processi dovesse modificare una *propria* variabile, tale modifica non
sarebbe visibile ad entrambi; i file aperti invece sono condivisi, per cui 
una eventuale modifica ad un file sarebbe ad entrambi visibile.
    
L'implementazione della SystemCall fork() puo' essere diversa a seconda del
sistema UNIX utilizzato; l'header da utilizzare e' <unistd.h>.

pid_t e' un tipo di dato definito in <sys/types.h>, sarebbe stato lo stesso
se si fosse utilizzato un altro tipo di dato intero, tuttavia e' sempre
consigliabile utilizzare i tipi proposti per una maggiore portabilita'.
*/

int main(int argc, char *argv[]) {
   pid_t pid;

   /* Si crea un processo figlio */
   pid = fork();

   if (pid < 0) {
      fprintf(stderr, "Err.(%s) - fork() failed\n", strerror(errno));
      exit(EXIT_FAILURE);
   } else if (pid == 0) {
      printf("Figlio - getpid() %d - getppid() %d - PID: %d\n", 
      	    getpid(), getppid(), pid);
   } else  {
      printf(" Padre - getpid() %d - getppid() %d - PID: %d\n", 
      	    getpid(), getppid(), pid);
   }


   return(EXIT_SUCCESS);
}
