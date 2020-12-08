/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "Game.h"

#define GAME_PID getpid()

void welcomeMenu() {
    printf("\n\t ############################################ \n");
    printf("\t ###### Bem vindo ao jogo 10-em-linha! ###### \n");
    printf("\t ##### O jogo favorito da tua infancia ###### \n");
    printf("\t ############################################ \n");
    printf("\t ################## Regras ################## \n");
    printf("\t #      -> 1 Linha completa = 1 ponto       # \n");
    printf("\t #      -> Maximo de 2 utilizadores         # \n");
    printf("\t #      -> 2 tipos de caracteres: `x` `o`   # \n");
    printf("\t #      -> Uma jogada de cada vez           # \n");
    printf("\t ############################################ \n");
    printf("\t # O jogo termina, assim que acabar o tempo # \n");
    printf("\t ############################################ \n");
    printf("\t ##### (A) Avançar ########## (S) Sair ###### \n");
    printf("\t ############################################ \n");
}

int main(int argc, char *argv[]) {
    int column = 0;
    int playsCounter = 1;

    welcomeMenu();

    Game *game = createGame(GAME_PID);
    initGame(game);

    while (1) {
        char* pieceToPlay = (playsCounter % 2 == 0) ? PIECE_O : PIECE_X;

        showGameTable(game);

        if(strcmp (pieceToPlay, PIECE_X) == 0){
            printf("\t # Peça: "); 
            printf("\e[38;5;82m");
            printf("%s", pieceToPlay);
            printf("\033[0m|");
            printf(". Coluna (1 - %i): ", NR_OF_COLUMNS);
        }else{
            printf("\t # Peça: "); 
            printf("\033[22;34m");
            printf("%s", pieceToPlay);
            printf("\033[0m|");
            printf(". Coluna (1 - %i): ", NR_OF_COLUMNS);
        }

        
        scanf("%i", &column);

        doPlay(game, pieceToPlay,column - 1);

        playsCounter ++;
    }
    return 0;
}