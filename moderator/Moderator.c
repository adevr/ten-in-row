/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ftw.h>
#include "Moderator.h"

#define SERVER_PIPE_PATH "/moderatorPipe"

extern char **environ;

Moderator initModerator(){
    Moderator Moderator;
    Connections Connections;

    Moderator.pid = getpid();
    Moderator.pipeName = strdup(SERVER_PIPE_PATH);
    Moderator.pipeDescriptor = -1;
    Moderator.Connections = Connections;

    Moderator.Connections.length = 0;

    return Moderator;
}

char *createModeratorPipe(Moderator *Moderator, char *TEMP_MODERATOR_PATH) {
    char *moderatorPipeNamePath = strdup(TEMP_MODERATOR_PATH);
    strcat(moderatorPipeNamePath, Moderator->pipeName);

    mkfifo(moderatorPipeNamePath,0777);

    return moderatorPipeNamePath;
}

void makeConnection(Connections *Connections, Client Client, Game Game){
    RunningGame *auxRunningGamePointer, *newRunningGame;

    auxRunningGamePointer = Connections->RunningGames;
    newRunningGame = malloc(sizeof(RunningGame));

    if (newRunningGame == NULL) {
        perror("On Make Connection: Exception during memory allocation");
        return;
    }

    newRunningGame->Client = Client;
    newRunningGame->Game = Game;
    newRunningGame->prox = NULL;

    while (1) {
        if (Connections->length == 0) {
            Connections->RunningGames = newRunningGame;
            break;
        }

        if (Connections->RunningGames->prox == NULL) {
            newRunningGame->prev = Connections->length != 0 ? Connections->RunningGames : NULL;

            Connections->RunningGames->prox = newRunningGame;

            // Back to the first node
            Connections->RunningGames = auxRunningGamePointer;
            break;
        }

        // Iterate over the nodes
        Connections->RunningGames = Connections->RunningGames->prox;
    }

    Connections->length++;
}

void readEnvVariables() {
    char *tempMaxPlayer = getenv("MAXPLAYERS"), *tempGameDir = getenv("GAMEDIR");

    if (tempGameDir == NULL || tempMaxPlayer == NULL) {
        printf("Error: MAXPLAYERS or GAMEDIR env variable are not defined **\n");
        exit(0);
    }

    maxPlayers = atoi(tempMaxPlayer);
    gameDir = tempGameDir;
}

void printInitialInformation(int waiting_time, int duration) {
    printf("*  MAXPLAYER             = %d\n",maxPlayers);
    printf("*  GAMEDIR               = %s\n",gameDir);
    printf("*  Moderator PID         = %d\n\n",getpid());
    printf("*  Championship duration = %d\n",duration);
    printf("*  Waiting time          = %d\n",waiting_time);
}

