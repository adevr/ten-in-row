/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#ifndef TEN_IN_ROW_GAME_H
#define TEN_IN_ROW_GAME_H

typedef struct Game {
    int pid;

    int readDescriptor;
    int writeDescriptor;
} Game;

Game initGame(int gamePid, int readDescriptor, int writeDescriptor);
void removeGame(Game *game);

#endif //TEN_IN_ROW_GAME_H
