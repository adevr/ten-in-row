/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "Game.h"
#include "../helpers/helpers.h"
#include "../models/Communication/Communication.h"

Game *game;

void getArgsValues(int argc, char *argv[]) {
    if (argc == 1) {
        return;
    }

    if (argc == 2) {
        perror("Argumentos incorretos.\n"
        "Deve de seguir a estrutura: ./{games program} {file descriptor to read} {file descriptor to write}\n");

        exit(0);
    }

    game->name = strdup(argv[0]);
    game->readFd = stringToNumber(argv[1]);
    game->writeFd = stringToNumber(argv[2]);
}

void setFileDescriptors() {
    dup2(game->readFd, 0);
    dup2(game->writeFd, 1);

    close(game->readFd);
    close(game->writeFd);
}

void gameSig_handler(int signo){
    if (signo == SIGUSR1){
        exit(game->points);
    }
}

int main(int argc, char *argv[]) {
    int runningAsChildProcess = 0;

    game = createGame();
    getArgsValues(argc, argv);

    if (signal(SIGUSR1, gameSig_handler) == (sig_t)SIG_ERR)
        perror("\ncan't catch SIGUSR1\n");

    if (argc > 2) {
        runningAsChildProcess = 1;
        setFileDescriptors();
    }

    if(!runningAsChildProcess) {
        initGame(game);
        return 0;
    }

    initGameChildProcess(game);

    return 0;
}