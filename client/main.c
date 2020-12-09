/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "Client.h"
#include "../constants/constants.h"

// TODO
//  Initialize every string outside of loops (to get scans fs, ....)
//  ON SIGTERM OR KILL unlink pipes and close connections
int main(int argc, char *argv[]) {
    printf("%i\n", getpid());

    char moderatorMessage[STRING_BUFFER];
    Client client = initClient();

    createClientPipe(&client);

    while (1) {
        //client.pipeModeratorDescriptor = open(TEMP_MODERATOR_NAMED_PIPE, O_WRONLY);
        //client.pipeDescriptor = open(client.pipePath, O_RDONLY | O_NONBLOCK);

        executeGameMove(&client);
        //read(client.pipeDescriptor, moderatorMessage, sizeof(moderatorMessage));
        //printf("%s\n", moderatorMessage);

        //close(client.pipeModeratorDescriptor);
    }
}