//
// Created by ubuntu on 01/12/20.
//

#include <string.h>
#include <stdio.h>
#include "Client.h"

Client initClient(int clientPid, char *user, char *pipeLocation) {
    Client client;

    client.pid = clientPid;
    client.userName = user;
    client.pipeLocation = pipeLocation;
    client.pipeDescriptor = -1;

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
