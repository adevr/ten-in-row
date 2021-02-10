/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h> 
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>

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
        perror("Conjunto de argumentos incorreto. Deve de usar: \n");
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

void signalHandler(int signal) {
    close(moderator.pipeDescriptor);
    unlink(TEMP_MODERATOR_NAMED_PIPE);
    system(RM_TEMP_ROOT_PATH);
    
    while (moderator.connectedClients != NULL) {
        ConnectedClients *auxConnectedClients = moderator.connectedClients->prox;

        kill(moderator.connectedClients->client.gameChildProcess->pid, SIGUSR1);
        kill(moderator.connectedClients->client.pid, SIGUSR2);
        
        free(moderator.connectedClients->client.gameChildProcess);
        free(moderator.connectedClients);

        moderator.connectedClients = auxConnectedClients;
    }

    moderator.connectedClients = NULL;
    exit(0);
}

void *commandReaderListener(void *pointerToData) {
    Moderator *Moderator = pointerToData;
    char command[INPUT_BUFFER];

    while (1) {
        scanf("%29s", command);
        int commandLength = strlen(command);

        if (!strcmp(command, "players")) {
            displayClients(Moderator);
        }
        else if (!strcmp(command, "games")) {
            displayGames(Moderator);
        }
        else if (command[0] == 'k') {
            char playerName[29] = "\0";

            strncpy(playerName, command + 1, commandLength-1);
            kickPlayer(Moderator, playerName);
            printf("O jogador %s foi expulso com sucesso.\n", playerName);

            if (Moderator->connectedClientsLength <= 1 && Moderator->championStatus == 1) {
                endChampionship(Moderator);
            }
        }
        else if (command[0] == 's') {
            char playerName[29] = "\0";

            strncpy(playerName, command + 1, commandLength-1);
            changeClientCommunicationStatus(Moderator, playerName, 1);
            printf("Comunicações do jogador %s interrompidas.\n", playerName);
        }
        else if (command[0] == 'r') {
            char playerName[29] = "\0";

            strncpy(playerName, command + 1, commandLength-1);
            changeClientCommunicationStatus(Moderator, playerName, 0);
            printf("Comunicações do jogador %s reestabelecidas.\n", playerName);
        }
        else if (!strcmp(command, "end")) {
            printf("A concluir o campeonato imediatamente\n");
            endChampionship(Moderator);
        }
        else if (!strcmp(command, "exit")) {
            kill(moderator.pid, SIGTERM);
        }
        else {
            printf("Comando indisponivel\n");
        }
    }
}

void *championshipTimerThread(void *pointerToData) {
    Moderator *Moderator = pointerToData;

    pthread_join(Moderator->threads.championshipWaitingTimeThreadID, NULL);

    printf("\n## Campeonato iniciado!\n");
    sleep(championship_duration);
    printf("\n## O campeonato terminou!\n");

    endChampionship(Moderator);
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

/*
    Função disponibilizada pelo professor Durães.
*/
void getGameApps(char *path)
{
    char *dirname;
    char gamePath[STRING_BUFFER] = "\0";
    DIR *dir;
    struct dirent *entrada;

    if ((dir = opendir(path)) == NULL)
        perror("\nerro em opendir()");
    else
    {
        while ((entrada = readdir(dir)) != NULL) {

            if (entrada->d_name[0] == 'g' && entrada->d_name[1] == '_')
            {
                strcat(gamePath, "./");
                strcat(gamePath, gameDir);
                strcat(gamePath, entrada->d_name);

                addGameApp(&moderator, entrada->d_name, gamePath);

                memset(gamePath, 0, sizeof(gamePath));
            }
        }

        closedir(dir);
    }

    if (moderator.gameAppsLength <= 0) {
        printf("\nErro: Não é possivel executar o arbitro pois não existem jogos na pasta |%s|.\n"
        "Execute o comando createSixGames.sh para criar 6 jogos.\n", gameDir);
        kill(getpid(), SIGTERM);
    }
}

int main(int argc, char *argv[]) {
    char responseBuffer[STRING_BUFFER] = "\0";
    int numberOfGames = 4;
    
    initRandom();
    getArgsValues(argc, argv);
    setTempPaths();

    moderator = initModerator();
    moderator.pipeDescriptor = open(moderator.pipePath, O_RDWR);

    getGameApps(gameDir);
    
    signal(SIGTERM, signalHandler);
    signal(SIGINT, signalHandler);
    signal(SIGALRM, signalHandler);

    pthread_create(&moderator.threads.administratorCommandsReaderThreadID, NULL, commandReaderListener, &moderator);

    printf("-----------------------------------------------\n");
    printf("\t### A aguardar por clientes... ###\n");
    printf("-----------------------------------------------\n");

    while (moderator.championStatus != FINISHED) {
        listeningResponse(moderator.pipeDescriptor, responseBuffer);
        handleClientRequest(&moderator, responseBuffer);

        if (moderator.championStatus == WAITING_FOR_PLAYERS && moderator.connectedClientsLength == 2) {
            pthread_create(&moderator.threads.championshipWaitingTimeThreadID, NULL, championshipWaitingTimeThread, &moderator);
        }

        memset(responseBuffer, 0, sizeof(responseBuffer));
    }

    pthread_join(moderator.threads.championshipTimerThreadID, NULL);

    close(moderator.pipeDescriptor);
    return 0;
}


