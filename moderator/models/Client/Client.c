/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#include <string.h>
#include "Client.h"

Client initClient(int clientPid, Game *game, char *user, char *pipeLocation) {
    Client client;

    client.pid = clientPid;
    client.userName = user;
    client.pipeLocation = pipeLocation;
    client.pipeDescriptor = -1;

    client.gameChildProcess = game;

    return client;
}

int userNameExists(ConnectedClients *connectedClients, char *userName) {
    ConnectedClients *auxConnectedClients = connectedClients;

    if (connectedClients == NULL) {
        return 0;
    }

    while (connectedClients != NULL) {

        if (!strcmp(connectedClients->client.userName, userName)) {
            connectedClients = auxConnectedClients;
            return 1;
        }

        connectedClients = connectedClients->prox;
    }

    connectedClients = auxConnectedClients;
    return 0;
}
