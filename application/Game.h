/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#ifndef TENINROW_GAME_H
#define TENINROW_GAME_H

#define NR_OF_COLUMNS 10
#define NR_OF_LINES 5

#define PIECE_X "***"
#define PIECE_O "ººº"
#define EMPTY_CELL_CHAR "___"

typedef struct Game {
    int PID;
    char *name;

    int readFd;
    int writeFd;

    int points;
    int pointsPerRow;
    /*
     * 1  -> Em execução
     * 0  -> Criado
     * -1 -> Terminado
     */
    int state;
    int lines;
    int columns;
    int playsCounter;

    char *gameTable[NR_OF_LINES][NR_OF_COLUMNS];
} Game;

Game *createGame();
void gameRoulesInfo(Game *game);
void gameRoulesInfoMenu(Game *game);
void doPlay(Game *game, char *pieceToVerify, int column);
void verifyLines(Game *game, int line);
void addPoints(Game *game);
void showGameTable(Game *game);
void cleanBoard(Game *game);
void initGame(Game *game);
void initGameChildProcess(Game *game);
void showGameInfo(Game *game);


#endif //TENINROW_GAME_H