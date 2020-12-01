/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#ifndef TENINROW_MODERATOR_H
#define TENINROW_MODERATOR_H

#include "Models/Client/Client.h"
#include "Models/Application/Game.h"

#define STRING_BUFFER 40

int maxPlayers;
char *gameDir;

typedef struct RunningGame {
    Client client;
    Game game;
} RunningGame;

typedef struct Connections {
    RunningGame *prev, *RunningGame, *prox;
    int length;
} Connections;

typedef struct Moderator {
    int pid;
    char pipeLocation[STRING_BUFFER];
    int pipeDescriptor;
    Connections *Connections;
} Moderator;

Moderator initModerator();

void readEnvVariables();
void printInitialInformation(int waiting_time, int duration);

void onClientConnectionAttempt(Connections *Connections);

void makeConnection(Connections *Connections, Client *client, Game *game);
void disconnectClients(Connections *Connections);
void interruptGames(Connections *Connections);

void sendSignal(int PID);

// TODO pesquisar sobre os handlers de sinais
void signalHandler();
#endif