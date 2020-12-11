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
#include <fcntl.h>
#include "Moderator.h"

#include "../constants/constants.h"
#include "../helpers/helpers.h"
#include "../models/Communication/Communication.h"

extern char **environ;

Moderator initModerator(){
    Moderator Moderator;
    Connections Connections;

    Moderator.pid = getpid();
    Moderator.pipePath = strdup(TEMP_MODERATOR_NAMED_PIPE);
    Moderator.pipeDescriptor = -1;
    Moderator.Connections = Connections;

    Moderator.Connections.length = 0;

    mkfifo(Moderator.pipePath,0777);

    return Moderator;
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

void handleMessageByCode(Array messageSplited, char *clientNamedPipe) {
    // TODO adapt. Follow the TODO above ^
    char *pChar;
    int fd = open(clientNamedPipe, O_WRONLY);
    long messageCode = strtol(messageSplited.array[MESSAGE_CODE], &pChar,10);

    switch (messageCode) {
        case COMMAND:
            sendMessage(fd, "ARBITRO: É um comando");
            break;
        case CONNECTION_REQUEST:
            sendMessage(fd, "ARBITRO: É um pedido de conexao");
            break;
        case GAME_MOVE:
            sendMessage(fd, "ARBITRO: É um movimento");
            break;
        default:
            sendMessage(fd, "ARBITRO: Comando não reconhecido");
            break;
    }

    close(fd);
}

// TODO
//  Validate the clients already connected (max 25)
//  If there is a free space, create a client connection (new node), add the descriptor and send the feedback message(success or not and why)
void handleClientRequest(Moderator *Moderator, char *message) {
    Array messageSplited = splitString(strdup(message));

    char clientPid[strlen(messageSplited.array[PROCESS_ID])];
    strcpy(clientPid, messageSplited.array[PROCESS_ID]);

    char clientsTempPath[strlen(TEMP_CLIENTS_PATH)];
    strcpy(clientsTempPath, TEMP_CLIENTS_PATH);

    char clientNamedPipe[strlen(clientPid) + strlen(clientsTempPath)];
    strcpy(clientNamedPipe, clientsTempPath);
    strcat(clientNamedPipe, clientPid);

    handleMessageByCode(messageSplited, clientNamedPipe);

    freeTheArrayAllocatedMemory(&messageSplited);
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

