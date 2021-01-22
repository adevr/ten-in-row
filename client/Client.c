/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#include <unistd.h>
#include <string.h>
#include <ftw.h>
#include <stdlib.h>
#include "stdio.h"

#include "Client.h"

#include "../helpers/helpers.h"
#include "../constants/constants.h"
#include "../models/Communication/Communication.h"

Client initClient() {
    Client client;

    client.pid = getpid();
    client.user = NULL;
    client.pipePath = NULL;

    client.pipeDescriptor = -1;
    client.pipeModeratorDescriptor = -1;
    client.status = UNCONNECTED;

    return client;
}

void userNameInput(Client *client) {
    char userName[INPUT_BUFFER];

    if (client->user != NULL){
        free(client->user);
    }

    printf("\nInsira o seu nome de jogador: ");
    scanf("%29s", userName);

    client->user = malloc(strlen(userName) * sizeof(char));
    strcpy(client->user, userName);
}

void createClientPipe(Client *client) {
    char *clientNamedPipePath = strdup(TEMP_CLIENTS_PATH);

    strcat(clientNamedPipePath, getNumberInString(client->pid));

    if(mkfifo(clientNamedPipePath,0777) == -1) {
        perror("On client named pipe creation: The moderator isn't running at the moment");
        exit(1);
    }

    client->pipePath = malloc(strlen(clientNamedPipePath) * sizeof(char));
    client->pipePath = clientNamedPipePath;
}

void onExit(Client *client) {
    close(client->pipeModeratorDescriptor);
    close(client->pipeDescriptor);

    unlink(client->pipePath);
    exit(1);
}

void handleUserInput(Client client, char *userInput) {
    int messageCode = GAME_MOVE;

    if(client.status == UNCONNECTED) {
        sendMessage(client.pipeModeratorDescriptor, initMessageModel(client.pid, CONNECTION_REQUEST, client.user));
        return;
    }

    if (userInput[0] == COMMANDS_PREFIX) {
        messageCode = COMMAND;

        if(!strcmp(userInput, "#quit")) {
            messageCode = REQUEST_QUIT;
            sendMessage(client.pipeModeratorDescriptor, initMessageModel(client.pid, REQUEST_QUIT, userInput));
            onExit(&client);
        }
    }

    sendMessage(client.pipeModeratorDescriptor, initMessageModel(client.pid, messageCode, userInput));
}

void handleModeratorResponse(Client *client, char *moderatorResponseMessage) {
    listeningResponse(client->pipeDescriptor, moderatorResponseMessage);

    Array responseArray = splitString(moderatorResponseMessage);
    long messageCode = stringToNumber(responseArray.array[MESSAGE_CODE]);

    if (messageCode == CONNECTION_REFUSED) {
        printf("%s\n", responseArray.array[MESSAGE]);
        onExit(client);
    }

    if (messageCode == CONNECTION_ACCEPTED) {
        client->status = CONNECTED_WAITING_TO_START;
    }

    printf("%s\n", responseArray.array[MESSAGE]);
}


