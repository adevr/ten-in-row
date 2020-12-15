/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

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


#endif //TEN_IN_ROW_CLIENT_H

