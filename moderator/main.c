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
#include "../helpers/helpers.h"
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
            championship_duration = stringToNumber(argv[i]);
        }

        if (!strcmp(argv[i], "-w")) {
            i++;
            waiting_time = stringToNumber(argv[i]);
        }
    }

    system("clear");
    readEnvVariables();
    printInitialInformation(waiting_time, championship_duration);
}

void displayClients(Moderator *Moderator) {
    ConnectedClients *auxConnectedClients;
    auxConnectedClients = Moderator->connectedClients;

    printf("\n##### Clientes Conectados #####\n");

    while (Moderator->connectedClients != NULL) {

        printf("PID: %i \t|\t Username: %s \t|\t Named Pipe: %s\n",
           Moderator->connectedClients->client.pid,
           Moderator->connectedClients->client.userName,
           Moderator->connectedClients->client.pipeLocation
        );

        Moderator->connectedClients = Moderator->connectedClients->prox;
    }

    Moderator->connectedClients = auxConnectedClients;
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
    Moderator *Moderator = pointerToData;
    char command[INPUT_BUFFER];

    while (1) {
        printf("\n$ ->: ");
        scanf("%29s", command);

        if (!strcmp(command, "players")) {
            displayClients(Moderator);
        }
        else if (!strcmp(command, "games")) {
            printf("Jogos\n");
        }
        else if (!strcmp(command, "quit")) {
            printf("Sair\n");
        }
        else if (command[0] == 'k') {
            printf("Kickar jogador\n");
        }
        else {
            printf("Comando indisponivel\n");
        }
    }
}

/* TODO
 * Create the threads to:
 *      -> handle the communications between the clients and games
 *      -> handle the CHAMPION duration and interrupt the games when the counter fisnishes.
 *      -> handle the administrator commands
 *
 * On exit status(SIGTERM or SIGKILL), close the opened pipes and unlink(remove) them
 */
int main(int argc, char *argv[]) {
    char responseBuffer[STRING_BUFFER] = "\0";
    pthread_t administratorCommandsReaderThread;

    getArgsValues(argc, argv);
    setTempPaths();

    Moderator Moderator = initModerator();
    Moderator.pipeDescriptor = open(Moderator.pipePath, O_RDWR);

    pthread_create(&administratorCommandsReaderThread, NULL, commandReaderListener, &Moderator);

    while (1) {
        listeningResponse(Moderator.pipeDescriptor, responseBuffer);
        handleClientRequest(&Moderator, responseBuffer);

        memset(responseBuffer, 0, sizeof(responseBuffer));
    }

    close(Moderator.pipeDescriptor);
    return 0;
}


