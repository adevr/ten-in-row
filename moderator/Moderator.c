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

    Moderator.connectedClients = NULL;
    Moderator.connectedClientsLength = 0;

    Moderator.createdGames = NULL;
    Moderator.createdGamesLength = 0;

    Moderator.Connections = Connections;
    Moderator.Connections.length = 0;

    mkfifo(Moderator.pipePath,0777);

    return Moderator;
}

Client *addClient(Moderator *Moderator, int clientPid, char *user, char *pipeLocation) {
    ConnectedClients *auxConnectedClientsPointer, *newConnectedClients;

    auxConnectedClientsPointer = Moderator->connectedClients;
    newConnectedClients = malloc(sizeof(ConnectedClients));

    if (newConnectedClients == NULL) {
        perror("On add client: Exception during memory allocation");
        exit(1);
    }

    newConnectedClients->client = initClient(clientPid, user, pipeLocation);
    newConnectedClients->prox = NULL;

    while (1) {
        if (Moderator->connectedClientsLength == 0) {
            Moderator->connectedClients = newConnectedClients;
            break;
        }

        if (Moderator->connectedClients->prox == NULL) {
            newConnectedClients->prev = Moderator->connectedClientsLength != 0 ? Moderator->connectedClients : NULL;

            Moderator->connectedClients->prox = newConnectedClients;

            // Back to the first node
            Moderator->connectedClients = auxConnectedClientsPointer;
            break;
        }

        // Iterate over the nodes
        Moderator->connectedClients = Moderator->connectedClients ->prox;
    }

    Moderator->connectedClientsLength ++;
    return &newConnectedClients->client;
}

Game *addGame(Moderator *Moderator, char *name, int gamePid, int readDescriptor, int writeDescriptor) {
    CreatedGames *auxCreatedGamesPointer, *newCreatedGame;

    auxCreatedGamesPointer = Moderator->createdGames;
    newCreatedGame = malloc(sizeof(CreatedGames));

    if (newCreatedGame == NULL) {
        perror("On new game creation: Exception during memory allocation");
        exit(1);
    }

    newCreatedGame->game = initGame(gamePid, name, readDescriptor, writeDescriptor);
    newCreatedGame->prox = NULL;

    while (1) {
        if (Moderator->createdGamesLength == 0) {
            Moderator->createdGames = newCreatedGame;
            break;
        }

        if (Moderator->createdGames->prox == NULL) {
            newCreatedGame->prev = Moderator->createdGamesLength != 0 ? Moderator->createdGames : NULL;

            Moderator->createdGames->prox = newCreatedGame;

            // Back to the first node
            Moderator->createdGames = auxCreatedGamesPointer;
            break;
        }

        // Iterate over the nodes
        Moderator->createdGames = Moderator->createdGames ->prox;
    }

    Moderator->createdGamesLength ++;
    return &newCreatedGame->game;
}

void makeConnection(Connections *Connections, Client *Client, Game *Game){
    RunningGame *auxRunningGamePointer, *newRunningGame;

    auxRunningGamePointer = Connections->RunningGames;
    newRunningGame = malloc(sizeof(RunningGame));

    if (newRunningGame == NULL) {
        perror("On Make Connection: Exception during memory allocation");
        exit(1);
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

void handleCommand(Moderator *moderator, Array messageSplited, int clientFileDescriptor) {
    char *command = messageSplited.array[MESSAGE];
    char *response;

    if (!strcmp(command, "#mygame")){
        response = "ARBITRO: Comando ainda em desenvolvimento";
    } else {
        response = "ARBITRO: Comando indisponivel";
    }

    sendMessage(clientFileDescriptor, initMessageModel(moderator->pid, INFO, response));
}

// TODO get a random game and connect to a client with "makeConnection"
void handleConnectionRequest(Moderator *moderator, Array messageSplited, char *clientNamedPipe, int clientFileDesciptor) {
    if (moderator->Connections.length >= maxPlayers) {
        sendMessage(
            clientFileDesciptor,
            initMessageModel(moderator->pid, CONNECTION_REFUSED, "Capacidade maxima de jogadores atingida")
        );
        return;
    }

    if (userNameExists(moderator->connectedClients, messageSplited.array[MESSAGE])) {
        sendMessage(
                clientFileDesciptor,
                initMessageModel(moderator->pid, INVALID_USERNAME, "Utilizador já existe, tente um novo")
        );
        return;
    }

    Client *client = addClient(
        moderator,
        stringToNumber(messageSplited.array[PROCESS_ID]),
        messageSplited.array[MESSAGE],
        clientNamedPipe
    );

    // TODO HERE
    makeConnection(&moderator->Connections, client, NULL);

    sendMessage(
        clientFileDesciptor,
        initMessageModel(moderator->pid, CONNECTION_ACCEPTED, "ARBITRO: Conectado com sucesso!")
    );
}

void handleMessageByCode(Moderator *moderator, Array messageSplited, char *clientNamedPipe) {
    // TODO adapt. Follow the TODO above ^
    int fd = open(clientNamedPipe, O_WRONLY);

    long messageCode = stringToNumber(messageSplited.array[MESSAGE_CODE]);

    switch (messageCode) {
        case COMMAND:
            handleCommand(moderator, messageSplited, fd);
            break;
        case CONNECTION_REQUEST:
            handleConnectionRequest(moderator, messageSplited, clientNamedPipe, fd);
            break;
        case GAME_MOVE:
            sendMessage(fd, initMessageModel(moderator->pid, INFO, "ARBITRO: É um movimento"));
            break;
        case REQUEST_QUIT:
            //TODO remove unlink the player from the running games
            sendMessage(fd, initMessageModel(moderator->pid, INFO, "ARBITRO: É um pedido de saida"));
            break;
        default:
            sendMessage(fd, initMessageModel(moderator->pid, INFO, "ARBITRO: Código não reconhecido"));
            break;
    }

    close(fd);
}

// TODO
//  Delete the node when the client request to exit
void handleClientRequest(Moderator *Moderator, char *message) {
    Array messageSplited = splitString(strdup(message));

    char clientPid[strlen(messageSplited.array[PROCESS_ID])];
    strcpy(clientPid, messageSplited.array[PROCESS_ID]);

    char clientsTempPath[strlen(TEMP_CLIENTS_PATH)];
    strcpy(clientsTempPath, TEMP_CLIENTS_PATH);

    char clientNamedPipe[strlen(clientPid) + strlen(clientsTempPath)];
    strcpy(clientNamedPipe, clientsTempPath);
    strcat(clientNamedPipe, clientPid);

    handleMessageByCode(Moderator, messageSplited, clientNamedPipe);

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

