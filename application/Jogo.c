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

// TODO retornar 1 se a jogada for executada com sucesso e 0 no caso contrário
void executaJogada(Jogo *jogo, char piece, int coluna) {
    if (jogo == NULL) return;

    for (int i = NR_DE_LINHAS - 1; i >= 0; i--) {

        if (jogo->tabelaDoJogo[i][coluna] == EMPTY_CELL_CHAR) {
            jogo->tabelaDoJogo[i][coluna] = piece;
            return;
        }

    }

    printf("\n-> Coluna cheia. Selecione outra coluna.\n");
}

void verifyLines(Jogo *jogo, char pieceToVerify) {
    //char firstRowPiece = jogo->tabelaDoJogo[]
    for (int indiceDaLinha = 0; indiceDaLinha < NR_DE_LINHAS; indiceDaLinha++) {
        printf("|");

        for(int indiceDaColuna = 0; indiceDaColuna < NR_DE_COLUNAS; indiceDaColuna++){
            printf("%c", jogo->tabelaDoJogo[indiceDaLinha][indiceDaColuna]);
        }

        printf("|\n");
    }
}

void addPoints(Jogo *jogo, int points);

void apresentaTabuleiro(Jogo *jogo) {
    for (int indiceDaLinha = 0; indiceDaLinha < NR_DE_LINHAS; indiceDaLinha++) {
        printf("|");

        for(int indiceDaColuna = 0; indiceDaColuna < NR_DE_COLUNAS; indiceDaColuna++){
            printf("%c", jogo->tabelaDoJogo[indiceDaLinha][indiceDaColuna]);
        }

        printf("|\n");
    }

}