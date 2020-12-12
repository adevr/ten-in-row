/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "Client.h"
#include "../constants/constants.h"
#include "../models/Communication/Communication.h"

// TODO
//  if moderator accept the client, change status to 1 (fetched or connected)
//  ON SIGTERM OR KILL unlink pipes and close connections
int main(int argc, char *argv[]) {
    char moderatorResponseMessage[STRING_BUFFER], userInput[STRING_BUFFER];
    printf("%i\n", getpid());

    Client client = initClient();

    createClientPipe(&client);

    while (1) {
        client.pipeModeratorDescriptor = open(TEMP_MODERATOR_NAMED_PIPE, O_WRONLY);
        memset(userInput, 0, sizeof(userInput));
        memset(moderatorResponseMessage, 0, sizeof(moderatorResponseMessage));

        printf("\n$ ->: ");
        scanf("%25s", userInput);

        handleUserInput(client, userInput);
        close(client.pipeModeratorDescriptor);

        client.pipeDescriptor = open(client.pipePath, O_RDONLY);
        listeningResponse(client.pipeDescriptor, moderatorResponseMessage);

        close(client.pipeDescriptor);
    }
}