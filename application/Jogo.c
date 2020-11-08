//
// Created by alex on 31/10/20.
//

#include "Jogo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Jogo *criaJogo(int PID) {
    Jogo *jogo = malloc(sizeof(Jogo));

    jogo->PID = PID;
    jogo->pontos = 0;
    jogo->estado = 0;
    jogo->pointsPerRow = 10;
    jogo->linhas = NR_DE_LINHAS;
    jogo->colunas = NR_DE_COLUNAS;

    for (int indiceDaLinha = 0; indiceDaLinha < NR_DE_LINHAS; indiceDaLinha++)
        for(int indiceDaColuna = 0; indiceDaColuna < NR_DE_COLUNAS; indiceDaColuna++)
            jogo->tabelaDoJogo[indiceDaLinha][indiceDaColuna] = EMPTY_CELL_CHAR;

    return jogo;
}

void iniciaJogo(Jogo *jogo) {
    if (jogo == NULL) return;
    jogo->estado = 1;
}

void executaJogada(Jogo *jogo, char piece, int coluna) {
    if (jogo == NULL) return;

    for (int i = NR_DE_LINHAS - 1; i >= 0; i--) {

        if (jogo->tabelaDoJogo[i][coluna] == EMPTY_CELL_CHAR) {
            jogo->tabelaDoJogo[i][coluna] = piece;

            verifyLines(jogo, i);
            return;
        }
    }

    printf("\n-> Coluna cheia. Selecione outra coluna.\n");
}

void addPoints(Jogo *jogo) {
    jogo->pontos += jogo->pointsPerRow;
}

void verifyLines(Jogo *jogo, int line) {
    char firstRowPiece = jogo->tabelaDoJogo[line][0];

    for(int i = NR_DE_COLUNAS; i >= 0; i--){
        if (firstRowPiece != jogo->tabelaDoJogo[line][i] || jogo->tabelaDoJogo[line][i] == EMPTY_CELL_CHAR)
            return;
    }
    addPoints(jogo);
    printf("\nPONTOS %i\n", jogo->pontos);
}

void apresentaTabuleiro(Jogo *jogo) {
    for (int indiceDaLinha = 0; indiceDaLinha < NR_DE_LINHAS; indiceDaLinha++) {
        printf("|");

        for(int indiceDaColuna = 0; indiceDaColuna < NR_DE_COLUNAS; indiceDaColuna++){
            printf("%c", jogo->tabelaDoJogo[indiceDaLinha][indiceDaColuna]);
        }

        printf("|\n");
    }
}
