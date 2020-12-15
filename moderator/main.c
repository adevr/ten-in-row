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
#include <signal.h>

#include "Moderator.h"
#include "../constants/constants.h"
#include "../models/Communication/Communication.h"

Moderator moderator;

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
    ConnectedClients *auxConnectedClients = Moderator->connectedClients;

    printf("\n##### Clientes Conectados #####\n");
    printf("Total: %i\n", Moderator->connectedClientsLength);

    while (Moderator->connectedClients != NULL) {

        printf("PID: %i | Username: %s | Named Pipe: %s\n",
           Moderator->connectedClients->client.pid,
           Moderator->connectedClients->client.userName,
           Moderator->connectedClients->client.pipeLocation
        );

        Moderator->connectedClients = Moderator->connectedClients->prox;
    }

    Moderator->connectedClients = auxConnectedClients;
}

// TODO clean the runningGames and createdGames nodes
void signalHandler(int signal) {
    close(moderator.pipeDescriptor);
    unlink(TEMP_MODERATOR_NAMED_PIPE);

    while (moderator.connectedClients != NULL) {
        ConnectedClients *auxConnectedClients = moderator.connectedClients->prox;

        kill(moderator.connectedClients->client.pid, SIGUSR1);
        free(moderator.connectedClients);

        moderator.connectedClients = auxConnectedClients;
    }

    system(RM_TEMP_ROOT_PATH);

    moderator.connectedClients = NULL;
    exit(0);
}

void *commandReaderListener(void *pointerToData) {
    Moderator *Moderator = pointerToData;
    char command[INPUT_BUFFER];

    while (1) {
        scanf("%29s", command);

        if (!strcmp(command, "players")) {
            displayClients(Moderator);
        }
        else if (!strcmp(command, "games")) {
            printf("Jogos\n");
        }
        else if (!strcmp(command, "quit")) {
            kill(moderator.pid, SIGTERM);
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
 *      -> handle the CHAMPION duration and interrupt the games when the counter fisnishes.
 */
int main(int argc, char *argv[]) {
    char responseBuffer[STRING_BUFFER] = "\0";
    pthread_t administratorCommandsReaderThread;

    getArgsValues(argc, argv);
    setTempPaths();

    moderator = initModerator();
    moderator.pipeDescriptor = open(moderator.pipePath, O_RDWR);

    signal(SIGTERM, signalHandler);
    signal(SIGINT, signalHandler);

    pthread_create(&administratorCommandsReaderThread, NULL, commandReaderListener, &moderator);

    printf("-----------------------------------------------\n");
    printf("\t ### A aguardar por clientes... ###\n");

    while (1) {
        listeningResponse(moderator.pipeDescriptor, responseBuffer);
        handleClientRequest(&moderator, responseBuffer);

        memset(responseBuffer, 0, sizeof(responseBuffer));
    }

    close(moderator.pipeDescriptor);
    return 0;
}


