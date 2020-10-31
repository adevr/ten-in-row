//
// Created by alex on 31/10/20.
//

#ifndef TENINROW_JOGO_H
#define TENINROW_JOGO_H

typedef struct Jogo {


    int pontos;

    /*
     * 1  -> Em execução
     * 0  -> Criado
     * -1 -> Terminado
     */
    int estado;


    int tabelaDoJogo[10][10]
} Jogo;

Jogo *criaJogo();

void iniciaJogo(Jogo *jogo);

void executaJogada(Jogo *jogo, int linha, int coluna);

void apresentaTabuleiro(Jogo *jogo);

#endif //TENINROW_JOGO_H
