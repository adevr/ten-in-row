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
    int pipeDescriptor;
    int pipeModeratorDescriptor;

    /*
     * 0 - Unconnected
     * 1 - Connected with the moderator
     * */
    int status;
} Client;

Client initClient();

void createClientPipe(Client *client);

void handleUserInput(Client client, char *userInput);


#endif
