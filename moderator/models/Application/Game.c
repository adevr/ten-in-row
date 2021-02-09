/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "Game.h"
#include "../../../helpers/helpers.h"

Game *initGame(char *name, char *path, int moderatorPipeFd[2]) {
    Game *game = malloc(sizeof(Game));

    int childProcessFd[2];

    game->name = strdup(name);
    game->path = strdup(path);

    pipe(childProcessFd);

    game->readDescriptor = moderatorPipeFd[0];
    game->writeDescriptor = childProcessFd[1];

    int currentForkPID = fork();
    
    if (currentForkPID) {
        game->pid = currentForkPID;
    }

    if (!currentForkPID) {
        execl(game->path, game->name, getNumberInString(childProcessFd[0]), getNumberInString(moderatorPipeFd[1]), NULL);
    }

    return game;
}

