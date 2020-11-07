//
// Created by alex on 31/10/20.
//

#ifndef TENINROW_JOGO_H
#define TENINROW_JOGO_H

#define nrDeColunas 10
#define nrDeLinhas 10

//const int nrDeColunas = 10;
//const int nrDeLinhas= 10;

typedef struct Jogo {
    int pontos;

    /*
     * 1  -> Em execução
     * 0  -> Criado
     * -1 -> Terminado
     */
    int estado;

    int linhas;
    int colunas;

    char tabelaDoJogo[10][10];
} Jogo;

Jogo *criaJogo();

void iniciaJogo(Jogo *jogo);

void executaJogada(Jogo *jogo, int linha, int coluna);

void apresentaTabuleiro(Jogo *jogo);

#endif //TENINROW_JOGO_H
