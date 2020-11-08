//
// Created by alex on 31/10/20.
//

#include "Jogo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Game *createGame(int PID) {
    Game *game = malloc(sizeof(Game));

    game->PID = PID;
    game->points = 0;
    game->state = 0;
    game->pointsPerRow = 10;
    game->lines = NR_OF_LINES;
    game->columns = NR_OF_COLUMNS;

    for (int i = 0; i < NR_OF_LINES; i++)
        for(int ii = 0; ii < NR_OF_COLUMNS; ii++)
            game->gameTable[i][ii] = EMPTY_CELL_CHAR;

    return game;
}

void initGame(Game *game) {
    if (game == NULL) return;
    game->state = 1;
}

void executaJogada(Game *game, char piece, int column) {
    if (game == NULL) return;

    for (int i = NR_OF_LINES - 1; i >= 0; i--) {

        if (game->gameTable[i][column] == EMPTY_CELL_CHAR) {
            game->gameTable[i][column] = piece;

            verifyLines(game, i);
            return;
        }
    }

    printf("\n-> Coluna cheia. Selecione outra coluna.\n");
}

void addPoints(Game *game) {
    game->points += game->pointsPerRow;
}

void verifyLines(Game *game, int line) {
    char firstRowPiece = game->gameTable[line][0];

    for(int i = 0; i < NR_OF_COLUMNS; i++){
        if (firstRowPiece != game->gameTable[line][i] || game->gameTable[line][i] == EMPTY_CELL_CHAR)
            return;
    }
    addPoints(game);
    printf("\npoints %i\n", game->points);
}

void apresentaTabuleiro(Game *game) {
    for (int i = 0; i < NR_OF_LINES; i++) {
        printf("|");

        for(int ii = 0; ii < NR_OF_COLUMNS; ii++){
            printf("%c", game->gameTable[i][ii]);
        }

        printf("|\n");
    }
}
