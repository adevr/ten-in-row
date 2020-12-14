/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#include "Moderator.h"
#include "../constants/constants.h"
#include "../models/Communication/Communication.h"

void setTempPaths() {
    mkdir(TEMP_ROOT_PATH, 0777);
    mkdir(TEMP_MODERATOR_PATH, 0777);
    mkdir(TEMP_CLIENTS_PATH, 0777);
}

void getArgsValues(int argc, char *argv[]) {
    int championship_duration, waiting_time;

    if (argc < 5) {
        printf("Incorrect set of arguments passed to the program. Must use: \n");
        printf("./moderator -d {championship duration} -w {waiting time}\n");
        exit(0);
    }

    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-d")) {
            i++;
            championship_duration = atoi(argv[i]);
        }

        if (!strcmp(argv[i], "-w")) {
            i++;
            waiting_time = atoi(argv[i]);
        }
    }

    system("clear");
    readEnvVariables();
    printInitialInformation(waiting_time, championship_duration);
}

// TODO DELETE
// ONLY FOR TEST PROPOSE
void connectionsTester(Moderator *Moderator) {
    makeConnection(
        &Moderator->Connections,
        addClient(Moderator, 123, "Diogo", "/Diogo"),
        addGame(Moderator, "g_1", 321, 1, 2)
    );
    makeConnection(
        &Moderator->Connections,
        addClient(Moderator, 345, "Diogo1", "/Diogo1"),
        addGame(Moderator, "g_2", 333, 1, 2)
    );
    makeConnection(
        &Moderator->Connections,
        addClient(Moderator, 678, "Diogo2", "/Diogo2"),
        addGame(Moderator, "g_3", 444, 1, 2)
    );

    for (int i = 0; i < Moderator->createdGamesLength; ++i) {
        printf("Node\n");
        printf("PID: %i | ID: %s\n", Moderator->createdGames->game.pid, Moderator->createdGames->game.name);
        printf("------------\n");
        Moderator->createdGames = Moderator->createdGames->prox;
    }

    printf("\n-----------\n");
    for (int i = 0; i < Moderator->connectedClientsLength; ++i) {
        printf("Node\n");
        printf("PID: %i | USerName: %s\n", Moderator->connectedClients->client.pid, Moderator->connectedClients->client.userName);
        printf("------------\n");
        Moderator->connectedClients = Moderator->connectedClients->prox;
    }

    printf("\n-----------\n");
    for (int i = 0; i < Moderator->Connections.length; ++i) {
        printf("Node\n");
        printf("GAME ID: %s | USERNAME: %s\n", Moderator->Connections.RunningGames->Game->name, Moderator->Connections.RunningGames->Client->userName);
        printf("------------\n");
        Moderator->Connections.RunningGames = Moderator->Connections.RunningGames->prox;
    }
}

void *commandReaderListener(void *pointerToData) {
    char command[INPUT_BUFFER];

    while (1) {
        printf("\n$ ->: ");
        scanf("%29s", command);
        printf("\n$$$: %s", command);
    }
}

/* TODO
 * Create the threads to:
 *      -> handle the communications between the clients and games
 *      -> handle the CHAMPION duration and interrupt the games when the counter finishes.
 *      -> handle the administrator commands
 *
 * On exit status(SIGTERM or SIGKILL), close the opened pipes and unlink(remove) them
 */
int main(int argc, char *argv[]) {
    char responseBuffer[STRING_BUFFER] = "\0";

    pthread_t administratorCommandsReaderThread;

    //getArgsValues(argc, argv);
    setTempPaths();

    Moderator Moderator = initModerator();
    Moderator.pipeDescriptor = open(Moderator.pipePath, O_RDWR);

    pthread_create(&administratorCommandsReaderThread, NULL, commandReaderListener, NULL);

    while (1) {
        listeningResponse(Moderator.pipeDescriptor, responseBuffer);
        handleClientRequest(&Moderator, responseBuffer);

        memset(responseBuffer, 0, sizeof(responseBuffer));
    }

    close(Moderator.pipeDescriptor);
    return 0;
}


