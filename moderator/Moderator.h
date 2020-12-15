/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#ifndef TENINROW_MODERATOR_H
#define TENINROW_MODERATOR_H

#include "models/Client/Client.h"
#include "models/Application/Game.h"
#include "../helpers/helpers.h"

int maxPlayers;
char *gameDir;

typedef struct RunningGame {
    struct RunningGame *prev;
    Client *Client;
    Game *Game;
    struct RunningGame *prox;
} RunningGame;

typedef struct Connections {
    // Pointer to the first connection node
    RunningGame *RunningGames;
    int length;
} Connections;

typedef struct Moderator {
    int pid;
    char *pipePath;
    int pipeDescriptor;

    ConnectedClients *connectedClients;
    int connectedClientsLength;
    CreatedGames *createdGames;
    int createdGamesLength;

    Connections Connections;

} Moderator;

Moderator initModerator();

void readEnvVariables();
void printInitialInformation(int waiting_time, int duration);

Client *addClient(Moderator *Moderator, int clientPid, char *user, char *pipeLocation);
void removeClient(Moderator *Moderator, int clientPid);
Game *addGame(Moderator *Moderator, char *name, int gamePid, int readDescriptor, int writeDescriptor);
void removeGame(Moderator *Moderator, int gamePid);

void makeConnection(Connections *Connections, Client *Client, Game *Game);

void handleClientRequest(Moderator *Moderator, char *message);
void handleMessageByCode(Moderator *moderator, Array messageSplited, char *clientNamedPipe);
void handleCommand(Moderator *moderator, Array messageSplited, int clientFileDescriptor);
void handleConnectionRequest(Moderator *moderator, Array messageSplited, char *clientNamedPipe, int clientFileDesciptor);

void onClientConnectionAttempt(Connections *Connections);

void disconnectClients(Connections *Connections);
void interruptGames(Connections *Connections);

void sendSignal(int targetPID);

#endif