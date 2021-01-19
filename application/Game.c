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

#include "../helpers/helpers.h"
#include "../models/Communication/Communication.h"

Game *createGame()
{
    Game *game = malloc(sizeof(Game));

    game->PID = getpid();
    game->readFd = -1;
    game->writeFd = -1;
    game->points = 0;
    game->state = 0;
    game->pointsPerRow = 1;
    game->lines = NR_OF_LINES;
    game->columns = NR_OF_COLUMNS;
    game->playsCounter = 0;

    for (int i = 0; i < NR_OF_LINES; i++)
        for (int ii = 0; ii < NR_OF_COLUMNS; ii++)
            game->gameTable[i][ii] = EMPTY_CELL_CHAR;

    return game;
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

void gameRoulesInfo(Game *game) {
    printContent(
        "\n"
        "\t ############################################ \n"
        "\t ###### Bem vindo ao jogo 10-em-linha! ###### \n"
        "\t ##### O jogo favorito da tua infancia ###### \n"
        "\t ############################################ \n"
        "\t ################## Regras ################## \n"
        "\t #      -> 1 Linha completa = 1 ponto       # \n"
        "\t #      -> 2 tipos de caracteres: `*` `º`   # \n"
        "\t #      -> Uma jogada de cada vez           # \n"
        "\t ############################################ \n"
        "\t # O jogo termina, assim que acabar o tempo # \n"
        "\t ############################################ \n"
    , game->writeFd);
}

void gameRoulesInfoMenu(Game *game) {
    printContent(
        "\n\t ############################################ \n"
        "\t ###### Bem vindo ao jogo 10-em-linha! ###### \n"
        "\t ##### O jogo favorito da tua infancia ###### \n"
        "\t ############################################ \n"
        "\t ################## Regras ################## \n"
        "\t #      -> 1 Linha completa = 1 ponto       # \n"
        "\t #      -> 2 tipos de caracteres: `*` `º`   # \n"
        "\t #      -> Uma jogada de cada vez           # \n"
        "\t ############################################ \n"
        "\t # O jogo termina, assim que acabar o tempo # \n"
        "\t ############################################ \n"
        "\t ##### (A) Avançar ########## (S) Sair ###### \n"
        "\t ############################################ \n"
        "\t ##### Selecione opção: "
    , game->writeFd);
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
    char buffer[1500] = "\0";
    char* pieceToPlay = (game->playsCounter % 2 == 0) ? PIECE_O : PIECE_X;

    strcat(buffer, "\t ############################################# \n");
    strcat(buffer, "\t #####        Pontuação Atual: ");
    strcat(buffer, getNumberInString(game->points));
    strcat(buffer, "\t ##### \n");
    strcat(buffer, "\t ############################################# \n");

    for (int i = 0; i < NR_OF_LINES; i++)
    {   
        strcat(buffer, "\t ##");
        for (int ii = 0; ii < NR_OF_COLUMNS; ii++)
        {
            if (strcmp(PIECE_O, game->gameTable[i][ii]) == 0)
            {   
                strcat(buffer, "\033[22;34m");
                strcat(buffer, game->gameTable[i][ii]);
                strcat(buffer, "\033[0m|");
            }
            else if (strcmp(PIECE_X, game->gameTable[i][ii]) == 0)
            {
                strcat(buffer, "\e[38;5;82m");
                strcat(buffer, game->gameTable[i][ii]);
                strcat(buffer, "\033[0m|");
            }
            else {
                strcat(buffer, game->gameTable[i][ii]);
                strcat(buffer, "|");
            }   
        }

        strcat(buffer, "##\n");
    }

    strcat(buffer, "\t # Peça: ");

    strcat(buffer, (strcmp (pieceToPlay, PIECE_X) != 0 ? "\033[22;34m" : "\e[38;5;82m"));
    strcat(buffer, pieceToPlay);
    strcat(buffer, "\033[0m|");
    strcat(buffer, ". Coluna (1 - ");
    strcat(buffer, getNumberInString(NR_OF_COLUMNS));
    strcat(buffer, "): ");

    printContent(buffer, game->writeFd);
}

void initGame(Game *game)
{
    if (game == NULL)
        return;
    
    char selection;
    int column = 0;

    gameRoulesInfoMenu(game);

    scanf("%c", &selection);
    if(selection != 'A' && selection != 'a'){
        exit(1);
    }

    game->state = 1;

    while (1) {
        char* pieceToPlay = (game->playsCounter % 2 == 0) ? PIECE_O : PIECE_X;

        showGameTable(game);
        
        scanf("%i", &column);
        /*if(column == 0){
            exit(1);
        }*/
        doPlay(game, pieceToPlay, column - 1);

        game->playsCounter ++;
        system("clear");
    }
}

// TODO REQUEST_CODE_GET_GAME_INFO Command!!
void initGameChildProcess(Game *game) {
    if (game == NULL) {
        return;
    }

    char requestMessage[2] = "\0";
    int column = 0;

    while (1)
    {
        char* pieceToPlay = (game->playsCounter % 2 == 0) ? PIECE_O : PIECE_X;

        if (game->state) {
            showGameTable(game);
        }
        
        scanf("%2s", requestMessage); 

        if (!game->state && !strcmp(requestMessage, REQUEST_CODE_GET_GAME_ROULES))
        {
            gameRoulesInfo(game);
            continue;
        }

        if (!game->state && !strcmp(requestMessage, REQUEST_CODE_INIT_GAME))
        {
            game->state = 1;
            continue;
        }

        if (!strcmp(requestMessage, REQUEST_CODE_GET_GAME_INFO))
        {
            printContent("REQUEST_CODE_GET_GAME_INFO", game->writeFd);
            continue;
        }

        column = stringToNumber(requestMessage);

        doPlay(game, pieceToPlay, column - 1);
        game->playsCounter ++;
    }
    
}