//
// Created by ubuntu on 01/12/20.
//

#include "Game.h"

Game initGame(int gamePid, int readDescriptor, int writeDescriptor) {
    Game game;

    game.pid = gamePid;
    game.readDescriptor = readDescriptor;
    game.writeDescriptor = writeDescriptor;

    return game;
}

