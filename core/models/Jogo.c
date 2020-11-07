//
// Created by alex on 31/10/20.
//

#include "Jogo.h"
#include <stdio.h>
#include <stdlib.h>

Jogo *criaJogo() {
    Jogo *jogo = malloc(sizeof(Jogo));

    jogo->pontos = 0;
    jogo->estado = 0;
    jogo->linhas = nrDeLinhas;
    jogo->colunas = nrDeColunas;

    for (int indiceDaLinha = 0; indiceDaLinha < nrDeLinhas; indiceDaLinha++)
        for(int indiceDaColuna = 0; indiceDaColuna < nrDeColunas; indiceDaColuna++)
            jogo->tabelaDoJogo[indiceDaLinha][indiceDaColuna] = '_';

    return jogo;
}

void iniciaJogo(Jogo *jogo) {
    if (jogo == NULL) return;
    jogo->estado = 1;
}

void executaJogada(Jogo *jogo, int linha, int coluna) {
    if (jogo == NULL) return;

    jogo->tabelaDoJogo[linha][coluna] = '0';
}

void apresentaTabuleiro(Jogo *jogo) {
    for (int indiceDaLinha = 0; indiceDaLinha < nrDeLinhas; indiceDaLinha++) {
        printf("|");

        for(int indiceDaColuna = 0; indiceDaColuna < nrDeColunas; indiceDaColuna++){
            printf("%c", jogo->tabelaDoJogo[indiceDaLinha][indiceDaColuna]);
        }

        printf("|\n");
    }

}
