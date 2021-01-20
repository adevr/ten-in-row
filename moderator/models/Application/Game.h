/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#ifndef TEN_IN_ROW_GAME_H
#define TEN_IN_ROW_GAME_H

typedef struct Game {
    int pid;
    char *name;
    char *path;
    int readDescriptor;
    int writeDescriptor;
} Game;

Game *initGame(char *name, char *path, int moderatorPipeFd[2]);

#endif
