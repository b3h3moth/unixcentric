#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct point {
    int x;
    int y;
};

// Function prototypes
struct point init(int x, int y);
struct point sum(struct point sp1, struct point sp2);
void random(struct point *sptr);

int main(void) {

    struct point my_sp_a;
    struct point my_sp_b;
    struct point my_sp_ab;
    struct point my_sp_rd;
    struct point *my_sp_prd;

    // Inizializzazione della prima struttura my_sp_a
    my_sp_a = init(10, 20);
    printf("my_sp_a.x = %d, my_sp_a.y = %d\n",my_sp_a.x, my_sp_a.y);
    
    // Inizializzazione della seconda struttura my_sp_b
    my_sp_b = init(30, 40);
    printf("my_sp_b.x = %d, my_sp_b.y = %d\n",my_sp_b.x, my_sp_b.y);

    // Somma dei membri delle strutture precedenti
    my_sp_ab = sum(my_sp_a, my_sp_b);
    printf("my_sp_ab.x = %d, my_sp_ab.y = %d\n",my_sp_ab.x, my_sp_ab.y);

    // Inizializza i membri della struttura con valori (pseudo) casuali
    random(&my_sp_rd);
    printf("my_sp_rd.x = %d, my_sp_rd.y = %d\n",my_sp_rd.x, my_sp_rd.y);

    return(EXIT_SUCCESS);
}

// Inizializza e restituisce la struttura point
struct point init(int val1, int val2) {
    
    /* Un modo potrebbe essere di creare una struttura, inizializzarne i
    membri e infine restuirla al chiamante:
    
    struct point temp;
    temp.x = val1;
    temp.y = val2;
    
    return temp; 

    Oppure si fa ritornare direttamente una struttura anonima i cui membri 
    saranno inizializzati mediante, per l'appunto, gli inizializzatori 
    designati (designated initializers) */

    return (struct point) {.x = val1, .y = val2};
}

/* Somma i membri delle strutture sp1 e sp2, e restituisce il risultato sotto
forma di struttura di tipo point */
struct point sum(struct point sp1, struct point sp2) {

    /* Come nel caso della funzione init() la somma di due strutture e la
    relativa restituzione puo' essere eseguita mediante:

    struct point temp;
    
    temp.x = sp1.x + sp2.x;
    temp.y = sp1.y + sp2.y;

    return temp;

    Oppure utilizzando nuovamente gli inizializzatori designati con una
    struttura anonima: */

    return (struct point) { .x = sp1.x + sp2.x, .y = sp1.y + sp2.y};
}

// Assegna ai membri della struttura puntata da *sptr valori random
void random(struct point *sptr) {
    // Inizializzazione del generatore di numeri (pseudo) casuali
    srand(time(NULL));

    sptr->x = rand() % 10;
    sptr->y = rand() % 10;
}
