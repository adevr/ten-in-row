//
// Created by ubuntu on 01/12/20.
//

#include "Client.h"
#include "../../../constants/constants.h"

Client initClient(int clientPid, char *user, char *pipeLocation) {
    Client client;

    client.pid = clientPid;
    client.userName = user;
    client.pipeLocation = pipeLocation;
    client.pipeDescriptor = -1;

    return client;
}

