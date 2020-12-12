/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#ifndef TENINROW_MODERATOR_H
#define TENINROW_MODERATOR_H

#include "models/Client/Client.h"
#include "models/Application/Game.h"

int maxPlayers;
char *gameDir;

typedef struct RunningGame {
    struct RunningGame *prev;
    Client Client;
    Game Game;
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
    Connections Connections;
} Moderator;

Moderator initModerator();

void readEnvVariables();
void printInitialInformation(int waiting_time, int duration);

void makeConnection(Connections *Connections, Client Client, Game Game);
void handleClientRequest(Moderator *Moderator, char *message);
/*
 * TODO
 * Check the num max of connected clients
 * Validate the username (if the request username is already exist, send the proper feedback message)
 * If the none of the above validations is triggered, make a connection (new game must be linked to the client)
 */
void onClientConnectionAttempt(Connections *Connections);

void disconnectClients(Connections *Connections);
void interruptGames(Connections *Connections);

void sendSignal(int targetPID);

// TODO pesquisar sobre os handlers de sinais
void signalHandler();
#endif