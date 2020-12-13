/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

// handle do sinal que o arbitro manda e efetuar ações

#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

Game *createGame()
{
    Game *game = malloc(sizeof(Game));

    game->PID = getpid();
    game->points = 0;
    game->state = 0;
    game->pointsPerRow = 10;
    game->lines = NR_OF_LINES;
    game->columns = NR_OF_COLUMNS;

    for (int i = 0; i < NR_OF_LINES; i++)
        for (int ii = 0; ii < NR_OF_COLUMNS; ii++)
            game->gameTable[i][ii] = EMPTY_CELL_CHAR;

    return game;
}

void initGame(Game *game)
{
    if (game == NULL)
        return;
    game->state = 1;
}

void cleanBoard(Game *game)
{
    for (int i = 0; i < NR_OF_LINES; i++)
    {
        for (int j = 0; j < NR_OF_COLUMNS; j++)
        {
            game->gameTable[i][j] = EMPTY_CELL_CHAR;
        }
    }
}
void doPlay(Game *game, char *piece, int column)
{
    if (game == NULL)
        return;

    for (int i = NR_OF_LINES - 1; i >= 0; i--)
    {

        if (game->gameTable[i][column] == EMPTY_CELL_CHAR)
        {
            game->gameTable[i][column] = piece;

            verifyLines(game, i);
            return;
        }
    }
    cleanBoard(game);
    doPlay(game, piece, column);
}

void addPoints(Game *game)
{
    game->points += game->pointsPerRow;
}

void verifyLines(Game *game, int line)
{
    char *firstRowPiece = game->gameTable[line][0];

    for (int i = 0; i < NR_OF_COLUMNS; i++)
    {
        if (firstRowPiece != game->gameTable[line][i] || game->gameTable[line][i] == EMPTY_CELL_CHAR)
            return;
    }
    addPoints(game);
}

void showGameTable(Game *game)
{
    printf("\t ############################################ \n");
    printf("\t ######        Pontuação Atual: %d     ###### \n", game->points);
    printf("\t ############################################ \n");
    for (int i = 0; i < NR_OF_LINES; i++)
    {
        printf("\t ##");
        for (int ii = 0; ii < NR_OF_COLUMNS; ii++)
        {
            if (strcmp(PIECE_O, game->gameTable[i][ii]) == 0)
            {
                printf("\033[22;34m");
                printf("%s", game->gameTable[i][ii]);
                printf("\033[0m|");
            }
            else if (strcmp(PIECE_X, game->gameTable[i][ii]) == 0)
            {
                printf("\e[38;5;82m");
                printf("%s", game->gameTable[i][ii]);
                printf("\033[0m|");
            }
            else
                printf("%s|", game->gameTable[i][ii]);
        }

        printf("##\n");
    }
}
