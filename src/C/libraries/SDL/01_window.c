#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

// Lo scopo del programma e' di creare una finestra di base con un titolo

int main(int argc, char *argv[]) {
    const int scr_width = 640;
    const int scr_height = 480;
    // La finestra
    SDL_Window *window = NULL;
    
    // Inizializzazione della libreria SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Err. Cannot initialize SDL: %s\n", SDL_GetError());
    } else {
        
        /* Creazione della finestra con specifici parametri
        - titolo della finestra;
        - la posizione x della finestra;
        - la posizione y della finestra;
        - la lunghezza della finestra;
        - l'altezza della finestra;
        - flags a disposizione della finestra, in questo caso indica che la
          finestra sia visibile.
        
          La finestra - window - rappresenta la risoluzione del gioco, lo 
        stato iniziale, ma ancora non c'e' nulla di visibile, se non il titolo
        della finestra stessa. Un flag finale peraltro puo' essere settato a
        SDL_WINDOW_FULLSCREEN_DESKTOP, che sovrascriverebbe ogni valore 
        preesistente. */
        window = SDL_CreateWindow("Take a Walk on The Wild Side",   \
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,     \
                scr_width, scr_height, SDL_WINDOW_SHOWN);

        if (window == NULL)
            fprintf(stderr, "Err. Could not create window: %s\n", SDL_GetError());
    }

    // Pausa di 5000 millisecondi (5 secondi)
    SDL_Delay(5000);

    // Distrugge la finestra
    SDL_DestroyWindow(window);

    // Chiusura della libreria
    SDL_Quit();
    
    return(EXIT_SUCCESS);
}
