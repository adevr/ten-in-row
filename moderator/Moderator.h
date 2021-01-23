/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#ifndef TENINROW_MODERATOR_H
#define TENINROW_MODERATOR_H

#include <signal.h>
#include "models/Client/Client.h"
#include "models/Application/Game.h"
#include "../helpers/helpers.h"

int maxPlayers;
char *gameDir;

enum CHAMPION_STATUS_TYPES {
    WAITING_FOR_PLAYERS,
    CHAMPION_STARTED,
    FINISHED    
};

typedef struct GameApps {
    struct GameApps *prev;
    char *name;
    char *path;
    struct GameApps *prox;
} GameApps;

typedef struct Threads {
    pthread_t administratorCommandsReaderThreadID;
    pthread_t championshipWaitingTimeThreadID;
    pthread_t championshipTimerThreadID;
} Threads;

typedef struct Moderator {
    int pid;
    char *pipePath;
    int pipeDescriptor;
    int anonymousPipeFd[2];

    /*
        * 0 -> not started and waiting for players
        * 1 -> started
    */
    int championStatus;

    ConnectedClients *connectedClients;
    int connectedClientsLength;
    GameApps *gameApps;
    int gameAppsLength;

    Threads threads;
} Moderator;

Moderator initModerator();

void *addGameApp(Moderator *Moderator, char *name, char *path);
GameApps *getRandomGameApp(Moderator *Moderator);

Client *addClient(Moderator *Moderator, int clientPid, char *user, char *pipeLocation);
Client *getClientByPid(Moderator *Moderator, int clientPid);
void removeClient(Moderator *Moderator, int clientPid);

void handleClientRequest(Moderator *Moderator, char *message);
void handleMessageByCode(Moderator *moderator, Array messageSplited, char *clientNamedPipe);
void handleCommand(Moderator *moderator, Array messageSplited, int clientFileDescriptor);
void handleConnectionRequest(Moderator *moderator, Array messageSplited, char *clientNamedPipe, int clientFileDesciptor);

void displayClients(Moderator *Moderator);
void displayGames(Moderator *Moderator);

void readEnvVariables();
void printInitialInformation(int waiting_time, int duration);
void sendSignal(int sig, int targetId);

void startChampionship(Moderator *Moderator);
#endif