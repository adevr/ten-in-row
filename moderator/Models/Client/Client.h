//
// Created by ubuntu on 01/12/20.
//

#ifndef TEN_IN_ROW_CLIENT_H
#define TEN_IN_ROW_CLIENT_H

#define STRING_BUFFER 40

typedef struct Client {
    int pid;
    char user[STRING_BUFFER];
    char pipeLocation[STRING_BUFFER];
    int pipeDescriptor;
} Client;

Client initClient();
void removeClient(Client *client);

#endif //TEN_IN_ROW_CLIENT_H

