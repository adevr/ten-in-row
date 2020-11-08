/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "Game.h"

#define GAME_PID getpid()

void welcomeMenu() {
    printf("\n\t ###### Bem vindo ao jogo 10-em-linha! ###### \n");
    printf("\nO 10-em-linha é um jogo conhecido da nossa infancia que consiste em deixar cair moedinhas\n"
           "de modo a formar uma linha no tabuleiro.");
    printf("\nEste jogo é baseado num sistema de pontuação: quantas mais linhas forem feitas com o mesmo caracter, maior será a pontuação final.");
    printf("\nExistem 2 tipos de caracteres: X e O.");
    printf("\nCada caracter será lançado à vez numa coluna escolhida pelo utilizador.");
    printf("\nO jogo termina quando o tempo chegar ao fim.\n\n");
}

int main(int argc, char *argv[]) {
    int column = 0;
    int playsCounter = 1;

    welcomeMenu();

    Game *game = createGame(GAME_PID);
    initGame(game);

    while (1) {
        char pieceToPlay = (playsCounter % 2 == 0) ? PIECE_O : PIECE_X;

        showGameTable(game);

        printf("\nPeça em jogo %c. Jogar na coluna (1 - %i): ", pieceToPlay, NR_OF_COLUMNS);
        scanf("%i", &column);

        doPlay(game, pieceToPlay,column - 1);

        playsCounter ++;
        system("clear");

        if(playsCounter == 10){break;}
    }
    return 0;
}