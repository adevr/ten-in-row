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
    int status;
} Client;

enum CLIENT_STATUS_TYPES {
    UNCONNECTED,
    CONNECTED_WAITING_TO_START,
    RUNNING
};

Client initClient();

void userNameInput(Client *client);

void createClientPipe(Client *client);

void handleUserInput(Client client, char *userInput);

void handleModeratorResponse(Client *client, char *moderatorResponseMessage);

void onExit(Client *client);


#endif
