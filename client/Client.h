/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#ifndef TENINROW_CLIENT_H
#define TENINROW_CLIENT_H

typedef struct Client {
    int pid;
    char *user;
    char *pipePath;
    int points;
    int pipeDescriptor;
    int pipeModeratorDescriptor;
} Client;

Client initClient();

void createClientPipe(Client *client);

void executeGameMove(Client client, char *movementString);


#endif
