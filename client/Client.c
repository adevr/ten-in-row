/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#include <unistd.h>
#include <string.h>
#include <ftw.h>
#include <stdlib.h>
#include <fcntl.h>
#include "stdio.h"

#include "Client.h"

#include "../helpers/helpers.h"
#include "../constants/constants.h"
#include "../models/Communication/Communication.h"

Client initClient() {
    Client client;
    char userName[STRING_BUFFER];

    client.pid = getpid();
    client.user = NULL;
    client.pipePath = NULL;
    client.points = 0;
    client.pipeDescriptor = -1;
    client.pipeModeratorDescriptor = -1;

    puts("Insira o seu nome de jogador: ");
    scanf("%s", userName);

    client.user = malloc(strlen(userName) * sizeof(char));
    strcpy(client.user, userName);

    return client;
}

void createClientPipe(Client *client) {
    char *clientNamedPipePath = strdup(TEMP_CLIENTS_PATH);

    strcat(clientNamedPipePath, getNumberInString(client->pid));

    if(mkfifo(clientNamedPipePath,0777) == -1) {
        perror("On client named pipe creation: The moderator isn't running at the moment");
    }

    client->pipePath = malloc(strlen(clientNamedPipePath) * sizeof(char));
    client->pipePath = clientNamedPipePath;
}

void executeGameMove(Client client, char *movementString){
    char *messageToSend = initMessageModel(client.pid,1, movementString);

    sendMessage(client.pipeModeratorDescriptor, messageToSend);
}




