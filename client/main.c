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
#include "../constants/constants.h"
#include "../models/Communication/Communication.h"

Client client;

void signalHandler(int signal) {
    if (signal == SIGUSR1) {
        printf("O campeonato foi encerrado.\n");
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

    signal(SIGTERM, signalHandler);
    signal(SIGUSR1, signalHandler);

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
            printf("### A aguardar começo do campeonato....\n");

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