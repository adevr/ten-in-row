//
// Created by ubuntu on 01/12/20.
//

#ifndef TEN_IN_ROW_CLIENT_H
#define TEN_IN_ROW_CLIENT_H

typedef struct Client {
    int pid;
    char *userName;
    char *pipeLocation;
    int pipeDescriptor;
} Client;

typedef struct ConnectedClients {
    struct ConnectedClients *prev;
    Client client;
    struct ConnectedClients *prox;
} ConnectedClients;

Client initClient(int clientPid, char *user, char *pipeLocation);

int userNameExists(ConnectedClients *connectedClients, char *userName);

void removeClient(Client *client);



#endif //TEN_IN_ROW_CLIENT_H

