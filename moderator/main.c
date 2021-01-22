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
#include "../helpers/helpers.h"
#include "../constants/constants.h"
#include "../models/Communication/Communication.h"

Moderator moderator;
int championship_duration = 0, waiting_time = 0;

void setTempPaths() {
    mkdir(TEMP_ROOT_PATH, 0777);
    mkdir(TEMP_MODERATOR_PATH, 0777);
    mkdir(TEMP_CLIENTS_PATH, 0777);
}

void getArgsValues(int argc, char *argv[]) {
    if (argc < 5) {
        perror("Incorrect set of arguments passed to the program. Must use: \n");
        perror("./moderator -d {championship duration} -w {waiting time}\n");
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

// TODO close the games (SIGUSR1), wait the points, send to the client and close the connections
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
            displayGames(Moderator);
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

void *championshipTimerThread(void *pointerToData) {
    Moderator *Moderator = pointerToData;

    pthread_join(Moderator->threads.championshipWaitingTimeThreadID, NULL);

    printf("\n## Campeonato iniciado!");fflush(stdout);
    sleep(championship_duration);
    printf("\n## O campeonato terminou!\n");fflush(stdout);
    // TODO
    //  Finish the games
    //  Return the pontuation to the Clients
    //  Disconnect the clients
    //  Close the program
    kill(Moderator->pid, SIGTERM);
}

void *championshipWaitingTimeThread(void *pointerToData) {
    Moderator *Moderator = pointerToData;

    printf("\n## Pelo menos 2 players foram conectados.\n");
    printf("## O campeonato inicia em %i segundos.\n", waiting_time);

    sleep(waiting_time);

    startChampionship(Moderator);

    pthread_create(&moderator.threads.championshipTimerThreadID, NULL, championshipTimerThread, &moderator);
    pthread_exit(NULL);
}

void buildGamesApps(Moderator *moderator, int numberOfGamesToBuild) {

    char command[100] = "\0";
    char gameName[20] = "\0";
    char gamePath[100] = "\0";

    for (int i = 0; i < numberOfGamesToBuild && i < 1000; i++)
    {
        strcat(command, "make jogo GAME_NUMBER=");
        strcat(command, getNumberInString(i+1));

        strcat(gameName, "g_");
        strcat(gameName, getNumberInString(i+1));
        strcat(gamePath, "./");
        strcat(gamePath, gameDir);
        strcat(gamePath, gameName);

        addGameApp(moderator, gameName, gamePath);

        system(command);

        memset(command, 0, sizeof(command));
        memset(gameName, 0, sizeof(gameName));
        memset(gamePath, 0, sizeof(gamePath));
    }
}

/* TODO
 * During the champion, on client request, get the client info by PID and redirect the info to the related game process. (WITH BUGS)
 * Create a function to send and get info from anonymous pipes (Moderator <-> Game)
 * (Client <-> Moderator) comm should follow the existing standard
 * 
 * Create the threads to:
 *      -> control the waiting time
 *      -> handle the CHAMPION duration and interrupt the games and clients when the counter fisnishes,sending the pontuation
 */
int main(int argc, char *argv[]) {
    char responseBuffer[STRING_BUFFER] = "\0";
    int numberOfGames = 4;
    
    initRandom();
    getArgsValues(argc, argv);
    setTempPaths();

    moderator = initModerator();
    moderator.pipeDescriptor = open(moderator.pipePath, O_RDWR);

    buildGamesApps(&moderator, numberOfGames);
    
    signal(SIGTERM, signalHandler);
    signal(SIGINT, signalHandler);

    pthread_create(&moderator.threads.administratorCommandsReaderThreadID, NULL, commandReaderListener, &moderator);

    printf("-----------------------------------------------\n");
    printf("\t### A aguardar por clientes... ###\n");
    printf("-----------------------------------------------\n");

    while (1) {
        listeningResponse(moderator.pipeDescriptor, responseBuffer);
        handleClientRequest(&moderator, responseBuffer);

        if (!moderator.championStatus && moderator.connectedClientsLength == 2) {
            pthread_create(&moderator.threads.championshipWaitingTimeThreadID, NULL, championshipWaitingTimeThread, &moderator);
        }

        memset(responseBuffer, 0, sizeof(responseBuffer));
    }

    close(moderator.pipeDescriptor);
    return 0;
}


