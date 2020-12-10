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

Client initClient(int clientPid, char *user, char *pipeLocation);
void removeClient(Client *client);

#endif //TEN_IN_ROW_CLIENT_H

