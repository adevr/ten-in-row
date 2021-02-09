/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include "Client.h"

#include "../helpers/helpers.h"
#include "../constants/constants.h"
#include "../models/Communication/Communication.h"

Client client;

void signalHandler(int signal) {
    if (signal == SIGUSR1) {
        char messageBuffer[STRING_BUFFER] = "\0";

        int myFd;
        
        myFd = open(client.pipePath, O_RDONLY);
        listeningResponse(myFd, messageBuffer);
        close(myFd);

        Array responseArray = splitString(messageBuffer);
        printf("%s\n", responseArray.array[MESSAGE]);
        memset(messageBuffer, 0, sizeof(messageBuffer));

        long messageCode = stringToNumber(responseArray.array[MESSAGE_CODE]);

        if ( messageCode == RESTART) {
            close(client.pipeModeratorDescriptor);
            close(client.pipeDescriptor);

            client.status == UNCONNECTED;
            return;
        }

        onExit(&client);
        return;
        
    }

    if (signal == SIGUSR2) {
        printf("\nFoste expulso do campeonato.\n");

        onExit(&client);
        return;
    }

    if (client.status != UNCONNECTED) {
        sendMessage(client.pipeModeratorDescriptor, initMessageModel(client.pid, REQUEST_QUIT, "\0"));
    }

    onExit(&client);
}

int main(int argc, char *argv[]) {
    char moderatorResponseMessage[STRING_BUFFER], userInput[INPUT_BUFFER];

    system("clear");

    client = initClient();

    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGUSR1, signalHandler);
    signal(SIGUSR2, signalHandler);

    createClientPipe(&client);

    while (1) {
        client.pipeModeratorDescriptor = open(TEMP_MODERATOR_NAMED_PIPE, O_WRONLY);
        memset(userInput, 0, sizeof(userInput));
        memset(moderatorResponseMessage, 0, sizeof(moderatorResponseMessage));

        if (client.status == RUNNING) {
            printf("\n$ ->: ");
            scanf("%29s", userInput);
        }
        else if (client.status == CONNECTED_WAITING_TO_START)
        {
            client.pipeDescriptor = open(client.pipePath, O_RDONLY);
            printf("### A aguardar o começo do campeonato....\nPrima ctrl + C para sair.\n");
            fflush(stdin);

            handleModeratorResponse(&client, moderatorResponseMessage);
            close(client.pipeDescriptor);

            client.status = RUNNING;
            continue;
        }
        else {
            userNameInput(&client);
        }

        handleUserInput(client, userInput);
        close(client.pipeModeratorDescriptor);

        client.pipeDescriptor = open(client.pipePath, O_RDONLY);
        handleModeratorResponse(&client, moderatorResponseMessage);
        close(client.pipeDescriptor);
    }
}