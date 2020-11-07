#include <stdio.h>

#include "application/Jogo.h"

int main(int argc, char *argv[]) {

    Jogo *jogo = criaJogo();
    iniciaJogo(jogo);

    apresentaTabuleiro(jogo);
    executaJogada(jogo, 1, 1);
    printf("\n\n");
    apresentaTabuleiro(jogo);
    return 0;
}