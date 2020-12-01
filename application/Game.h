/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#ifndef TENINROW_GAME_H
#define TENINROW_GAME_H

#define NR_OF_COLUMNS 10
#define NR_OF_LINES 5

#define PIECE_X 'x'
#define PIECE_O 'o'
#define EMPTY_CELL_CHAR '_'

typedef struct Game {
    int PID;
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

    char gameTable[NR_OF_LINES][NR_OF_COLUMNS];
} Game;

Game *createGame(int PID);
void initGame(Game *game);
void doPlay(Game *game, char pieceToVerify, int column);
void verifyLines(Game *game, int line);
void addPoints(Game *game);
void showGameTable(Game *game);

#endif //TENINROW_GAME_H