#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <grp.h>
#include <sys/types.h>

/*
La lettura del database dei gruppi /etc/group e' gestita da funzioni del tutto
analoghe concettualmente a quelle utilizzate per il database delle password 
/etc/passwd, la differenza sta nel fatto che si lavora sulla struttura 'group'
definita nell'header <grp.h>:

struct group
{
    char *gr_name;	    "Group name"
    char *gr_passwd;	"Password"
    __gid_t gr_gid;	    "Group ID"
    char **gr_mem;	    "Member list"
};


HEADER    : <grp.h>
PROTOTYPE : struct group *getgrgid(gid_t gid);
            struct group *getgrnam(const char *name);
SEMANTICS : La funzione getgrgid() restituisce il campo ottenuto fornendo il
            'gid' dell'utente; la funzione getgrnam() il campo ottenuto fornendo
	        il nome dell'utente indicato da 'name'.
RETURNS   : Un puntatore alla struttura group in caso di successo, NULL in caso
            di errore
--------------------------------------------------------------------------------
La struttura 'group' utilizzata dalle funzioni in oggetto e' allocata
staticamente, per cui il contenuto e' sovrascritto ad ogni nuova chiamata; esse 
sono utili qualora dovesse servire uno dei campi del file /etc/group, se
invece si volesse analizzare il file nel suo complesso dovrebbero essere
utilizzate altre funzioni quali getgrent(), setgrent(), endgrent().

Nota storica: Le prime implementazioni di UNIX prevedevano che ciascun utente
appartenesse a un gruppo per volta. Grazie all'avvento di 4.2BSD fu introdotto
il concetto di appartenenza a piu' gruppi. */

int main(int argc, char *argv[]) {
   struct group *grp, *grp2;
   uid_t my_uid = getuid();
   char *grname = "video";
   int i = 0;

   grp = getgrgid(my_uid);
   if (grp == NULL) {
       if (errno == 0) {
           fprintf(stderr, "Account Not Found.\n");
           return 1;
       } else {
           fprintf(stderr, "Err. %s getgrgid(%d)\n", strerror(errno), my_uid);
           return 1;
       }
   }

   printf("         gr_name: %s\n", grp->gr_name);
   printf("         gr_pass: %s\n", grp->gr_passwd);

   grp2 = getgrnam(grname);
   if (grp2 == NULL) {
       if (errno == 0) {
           fprintf(stderr, "Account Not Found.\n");
           return 1;
       } else {
           fprintf(stderr, "Err. %s getgrnam(%s)\n", strerror(errno), grname);
           return 1;
       }
   }

   printf("           gr_ID: %d\n", grp2->gr_gid);
   printf("  gr_member list: ");

   // Se il gruppo 'grname' ha piu' di un utente, lo stampa
   do {
       printf("%s, ", grp2->gr_mem[i++]);
   } while (grp2->gr_mem[i] != NULL);

   return(EXIT_SUCCESS);
}
