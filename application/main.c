//
// Created by ubuntu on 07/11/20.
//

#include <stdio.h>
#include <unistd.h>
#include "Jogo.h"

#define GAME_PID getpid()

void welcomeMenu() {
    printf("\n\t ###### Bem vindo ao jogo 10-em-linha! ###### \n");
    printf("\nO 10-em-linha é um jogo conhecido da nossa infancia que consiste em deixar cair moedinhas\n"
           "de modo a formar uma linha no tabuleiro.");
    printf("\nEste jogo é baseado num sistema de pontuação: quantas mais linhas forem feitas com o mesmo caracter, maior será a pontuação final.");
    printf("\nExistem 2 tipos de caracteres: X e O");
    printf("\nCada caracter será lançado à vez numa coluna escolhida pelo utilizador.");
    printf("\nO jogo termina quando o tempo chegar ao fim.\n\n");
}

int main(int argc, char *argv[]) {
    int column = 0;
    int playsCounter = 1;

    welcomeMenu();

    Jogo *jogo = criaJogo(GAME_PID);
    iniciaJogo(jogo);

    while (1) {
        char pieceToPlay = (playsCounter % 2 == 0) ? PIECE_O : PIECE_X;
        apresentaTabuleiro(jogo);

        printf("\nPeça em jogo %c. Jogar na coluna: ", pieceToPlay);
        scanf("%i", &column);

        executaJogada(jogo, pieceToPlay,column - 1);

        playsCounter ++;
    }
    return 0;
}