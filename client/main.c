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
//  Initialize every string outside of loops (to get scans fs, ....)
//  ON SIGTERM OR KILL unlink pipes and close connections
int main(int argc, char *argv[]) {
    char moderatorResponseMessage[STRING_BUFFER], movementString[STRING_BUFFER];
    printf("%i\n", getpid());

    Client client = initClient();

    createClientPipe(&client);

    while (1) {
        client.pipeModeratorDescriptor = open(TEMP_MODERATOR_NAMED_PIPE, O_WRONLY);
        memset(movementString, 0, sizeof(movementString));
        memset(moderatorResponseMessage, 0, sizeof(moderatorResponseMessage));

        puts("Jogada: ");
        scanf("%s", movementString);

        executeGameMove(client, movementString);
        close(client.pipeModeratorDescriptor);

        client.pipeDescriptor = open(client.pipePath, O_RDONLY);
        listeningResponse(client.pipeDescriptor, moderatorResponseMessage);

        close(client.pipeDescriptor);
    }
}