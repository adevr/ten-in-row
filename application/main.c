//
// Created by ubuntu on 07/11/20.
//

#include <stdio.h>
#include "Jogo.h"

int main(int argc, char *argv[]) {

    // Teste Jogo
    Jogo *jogo = criaJogo();
    iniciaJogo(jogo);

    apresentaTabuleiro(jogo);
    executaJogada(jogo, 1, 1);
    printf("\n\n");
    apresentaTabuleiro(jogo);

    return 0;
}