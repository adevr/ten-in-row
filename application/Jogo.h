//
// Created by alex on 31/10/20.
//

#ifndef TENINROW_JOGO_H
#define TENINROW_JOGO_H

#define NR_DE_COLUNAS 10
#define NR_DE_LINHAS 10

#define PIECE_X 'X'
#define PIECE_O 'O'
#define EMPTY_CELL_CHAR '_'

typedef struct Jogo {
    int PID;
    int pontos;
    int pointsPerRow;
    /*
     * 1  -> Em execução
     * 0  -> Criado
     * -1 -> Terminado
     */
    int estado;
    int linhas;
    int colunas;

    char tabelaDoJogo[NR_DE_LINHAS][NR_DE_COLUNAS];
} Jogo;

Jogo *criaJogo(int PID);

void iniciaJogo(Jogo *jogo);

void executaJogada(Jogo *jogo, char pieceToVerify, int coluna);

void verifyLines(Jogo *jogo, int line);

void addPoints(Jogo *jogo);

void apresentaTabuleiro(Jogo *jogo);

#endif //TENINROW_JOGO_H
