//
// Created by ubuntu on 01/12/20.
//

#ifndef TEN_IN_ROW_GAME_H
#define TEN_IN_ROW_GAME_H

typedef struct Game {
    int pid;

    int readDescriptor;
    int writeDescriptor;
} Game;

Game initGame();
void removeGame(Game *game);

#endif //TEN_IN_ROW_GAME_H
