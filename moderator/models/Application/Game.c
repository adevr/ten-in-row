/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#include "Game.h"

Game initGame(int gamePid, char* name, int readDescriptor, int writeDescriptor) {
    Game game;

    game.pid = gamePid;
    game.name = name;
    game.readDescriptor = readDescriptor;
    game.writeDescriptor = writeDescriptor;

    return game;
}

