/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h> 
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ftw.h>
#include <fcntl.h>

#include "Moderator.h"
#include "../helpers/helpers.h"
#include "../constants/constants.h"
#include "../models/Communication/Communication.h"

extern char **environ;

Moderator initModerator(){
    Moderator Moderator;

    Moderator.pid = getpid();
    Moderator.pipePath = strdup(TEMP_MODERATOR_NAMED_PIPE);
    Moderator.pipeDescriptor = -1;
    Moderator.anonymousPipeFd[0] = -1;
    Moderator.anonymousPipeFd[1] = -1;

    Moderator.connectedClients = NULL;
    Moderator.connectedClientsLength = 0;

    Moderator.championStatus = WAITING_FOR_PLAYERS;

    Moderator.gameApps = NULL;
    Moderator.gameAppsLength = 0;

    /*if(mkfifo(Moderator.pipePath,0777) == -1) {
        perror("Já se encontra um arbitro a correr no momento. Tente mais tarde\n");
        exit(1);
    }*/
    mkfifo(Moderator.pipePath,0777);

    pipe(Moderator.anonymousPipeFd);

    return Moderator;
}

void *addGameApp(Moderator *Moderator, char *name, char *path) {
    GameApps *auxCreatedGamesPointer, *newCreatedGame;

    auxCreatedGamesPointer = Moderator->gameApps;
    newCreatedGame = malloc(sizeof(GameApps));

    if (newCreatedGame == NULL) {
        perror("A criar o jogo: Exceção ao alocar memoria");
        exit(1);
    }

    newCreatedGame->path = strdup(path);
    newCreatedGame->name = strdup(name);

    newCreatedGame->prox = NULL;

    while (1) {
        if (Moderator->gameAppsLength == 0) {
            Moderator->gameApps = newCreatedGame;
            break;
        }

        if (Moderator->gameApps->prox == NULL) {
            newCreatedGame->prev = Moderator->gameAppsLength != 0 ? Moderator->gameApps : NULL;

            Moderator->gameApps->prox = newCreatedGame;

            // Back to the first node
            Moderator->gameApps = auxCreatedGamesPointer;
            break;
        }

        // Iterate over the nodes
        Moderator->gameApps = Moderator->gameApps->prox;
    }

    Moderator->gameAppsLength ++;
}

GameApps *getRandomGameApp(Moderator *Moderator) {
    if (Moderator->gameAppsLength <= 0) {
        perror("Erro: getRandomGameApp: Não existem jogos criados");
    }

    int randomGameIndex = intUniformRnd(1, Moderator->gameAppsLength);

    GameApps *auxGameApp = Moderator->gameApps;
    GameApps *randomGameApp;

    for (int i = 1; i <= Moderator->gameAppsLength && Moderator->gameApps != NULL; i++)
    {
        if (i == randomGameIndex) {
            randomGameApp = Moderator->gameApps;
            break;
        }
        Moderator->gameApps = Moderator->gameApps->prox;
    }

    Moderator->gameApps = auxGameApp;
    return randomGameApp;
}

Client *addClient(Moderator *Moderator, int clientPid, char *user, char *pipeLocation) {
    ConnectedClients *auxConnectedClientsPointer, *newConnectedClients;

    auxConnectedClientsPointer = Moderator->connectedClients;
    newConnectedClients = malloc(sizeof(ConnectedClients));

    if (newConnectedClients == NULL) {
        perror("Ao adicionar cliente: Exceção ao alocar memoria.");
        exit(1);
    }
    
    GameApps *randomGameApp = getRandomGameApp(Moderator);
    Game *game = initGame(randomGameApp->name, randomGameApp->path, Moderator->anonymousPipeFd);

    newConnectedClients->client = initClient(clientPid, game, user, pipeLocation);
    newConnectedClients->prox = NULL;

    while (1) {
        if (Moderator->connectedClientsLength == 0) {
            Moderator->connectedClients = newConnectedClients;
            break;
        }

        if (Moderator->connectedClients->prox == NULL) {
            newConnectedClients->prev = Moderator->connectedClientsLength != 0 ? Moderator->connectedClients : NULL;

            Moderator->connectedClients->prox = newConnectedClients;

            // Back to the first node
            Moderator->connectedClients = auxConnectedClientsPointer;
            break;
        }

        // Iterate over the nodes
        Moderator->connectedClients = Moderator->connectedClients ->prox;
    }

    Moderator->connectedClientsLength ++;
    return &newConnectedClients->client;
}

Client *getClientByPid(Moderator *Moderator, int clientPid) {
    ConnectedClients *auxConnectedClient = Moderator->connectedClients;
    Client *auxClient = NULL;

    while (Moderator->connectedClients != NULL)
    {
        if (clientPid == Moderator->connectedClients->client.pid) {
            auxClient = &Moderator->connectedClients->client;
            break;
        }

        Moderator->connectedClients = Moderator->connectedClients->prox;
    }
    
    Moderator->connectedClients = auxConnectedClient;
    return auxClient;
}

Client *getClientByName(Moderator *Moderator, char *userName) {
    ConnectedClients *auxConnectedClient = Moderator->connectedClients;
    Client *auxClient = NULL;

    while (Moderator->connectedClients != NULL)
    {
        if (!strcmp(Moderator->connectedClients->client.userName, userName)){ 
            auxClient = &Moderator->connectedClients->client;
            break;
        }

        Moderator->connectedClients = Moderator->connectedClients->prox;
    }
    
    Moderator->connectedClients = auxConnectedClient;
    return auxClient;
}

void removeClient(Moderator *Moderator, int clientPid) {
    ConnectedClients *auxConnectedClients = Moderator->connectedClients;

    for (int i = 0; Moderator->connectedClients != NULL; i++) {
        if (Moderator->connectedClients->client.pid != clientPid) {
            Moderator->connectedClients = Moderator->connectedClients->prox;
            continue;
        }

        if (i == 0) {
            auxConnectedClients = Moderator->connectedClients->prox;
        }

        if (Moderator->connectedClients->prox != NULL) {
            Moderator->connectedClients->prox->prev = Moderator->connectedClients->prev;
        }

        if (Moderator->connectedClients->prev != NULL) {
            Moderator->connectedClients->prev->prox = Moderator->connectedClients->prox;
        }

        kill(Moderator->connectedClients->client.gameChildProcess->pid, SIGUSR1);
        free(Moderator->connectedClients->client.gameChildProcess);
        free(Moderator->connectedClients);

        break;
    }

    Moderator->connectedClients = auxConnectedClients;
    Moderator->connectedClientsLength--;
}

void kickPlayer(Moderator *Moderator, char *playerName) {
    Client *client = getClientByName(Moderator, playerName);

    if (client == NULL) {
        printf("O player com o nome %s não existe.\n", playerName);
        return;
    }

    kill(client->pid, SIGUSR2);
    removeClient(Moderator, client->pid);
}

void changeClientCommunicationStatus(Moderator *Moderator, char *playerName, int communicationStatus) {
    Client *client = getClientByName(Moderator, playerName);

    if (client == NULL) {
        printf("O player com o nome %s não existe.\n", playerName);
        return;
    }

    client->communicationsInterrupted = communicationStatus;
}

void handleCommand(Moderator *moderator, Array messageSplited, int clientFileDescriptor) {
    int clientPID = stringToNumber(messageSplited.array[PROCESS_ID]);
    Client *client = getClientByPid(moderator, clientPID);

    char *command = messageSplited.array[MESSAGE];
    char response[STRING_BUFFER] = "\0";

    if (!strcmp(command, "#mygame")){
        communicateWithChildProcess(client->gameChildProcess->writeDescriptor, client->gameChildProcess->readDescriptor, REQUEST_CODE_GET_GAME_INFO, response);
    } else {
        strcat(response, "ARBITRO: Comando indisponivel");
    }

    sendMessage(clientFileDescriptor, initMessageModel(moderator->pid, INFO, response));
    memset(response, 0, sizeof(response));
}

void handleConnectionRequest(Moderator *moderator, Array messageSplited, char *clientNamedPipe, int clientFileDesciptor) {
    if (moderator->championStatus == CHAMPION_STARTED) {
        sendMessage(
                clientFileDesciptor,
                initMessageModel(moderator->pid, CONNECTION_REFUSED, "O campeonato já foi iniciado.\n")
        );
        return;
    }

    if (moderator->connectedClientsLength >= maxPlayers) {
        sendMessage(
            clientFileDesciptor,
            initMessageModel(moderator->pid, CONNECTION_REFUSED, "Capacidade maxima de jogadores atingida.")
        );
        return;
    }

    if (userNameExists(moderator->connectedClients, messageSplited.array[MESSAGE])) {
        sendMessage(
                clientFileDesciptor,
                initMessageModel(moderator->pid, INVALID_USERNAME, "Utilizador já existe, tente um novo.")
        );
        return;
    }

    Client *client = addClient(
        moderator,
        stringToNumber(messageSplited.array[PROCESS_ID]),
        messageSplited.array[MESSAGE],
        strdup(clientNamedPipe)
    );

    printf("O cliente [%s:%s] conectou-se com sucesso.\n", messageSplited.array[MESSAGE], messageSplited.array[PROCESS_ID]);

    char gameRoulesBuffer[STRING_BUFFER] = "\0";

    sendMessage(client->gameChildProcess->writeDescriptor, REQUEST_CODE_GET_GAME_ROULES);
    listeningResponse(client->gameChildProcess->readDescriptor, gameRoulesBuffer);
    sendMessage(
        clientFileDesciptor,
        initMessageModel(moderator->pid, CONNECTION_ACCEPTED, gameRoulesBuffer)
    );
}

void handleMessageByCode(Moderator *moderator, Array messageSplited, char *clientNamedPipe) {
    Client *client;
    
    char buffer[STRING_BUFFER] = "\0";
    int fd = open(clientNamedPipe, O_WRONLY);

    long messageCode = stringToNumber(messageSplited.array[MESSAGE_CODE]);
    int clientPid = stringToNumber(messageSplited.array[PROCESS_ID]);

    switch (messageCode) {
        case COMMAND:
            handleCommand(moderator, messageSplited, fd);
            break;
        case CONNECTION_REQUEST:
            handleConnectionRequest(moderator, messageSplited, clientNamedPipe, fd);
            break;
        case GAME_MOVE:
            client = getClientByPid(moderator, clientPid);

            if (client->communicationsInterrupted) {
                sendMessage(fd, initMessageModel(moderator->pid, INFO, "Está com as comunicações interrompidas!\n"));
                break;
            }

            communicateWithChildProcess(
                client->gameChildProcess->writeDescriptor,
                client->gameChildProcess->readDescriptor,
                messageSplited.array[MESSAGE],
                buffer
            );

            sendMessage(fd, initMessageModel(moderator->pid, INFO, buffer));
            break;
        case REQUEST_QUIT:
            removeClient(moderator, clientPid);
            printf("\nO cliente [%s] abandonou.\n", messageSplited.array[PROCESS_ID]);
            
            if (moderator->connectedClientsLength <= 1 && moderator->championStatus == 1) {
                endChampionship(moderator);
            }

            break;
        default:
            sendMessage(fd, initMessageModel(moderator->pid, INFO, "ARBITRO: Código não reconhecido"));
            break;
    }

    close(fd);
}

void handleClientRequest(Moderator *Moderator, char *message) {
    Array messageSplited = splitString(strdup(message));

    char clientPid[strlen(messageSplited.array[PROCESS_ID])];
    strcpy(clientPid, messageSplited.array[PROCESS_ID]);

    char clientsTempPath[strlen(TEMP_CLIENTS_PATH)];
    strcpy(clientsTempPath, TEMP_CLIENTS_PATH);

    char clientNamedPipe[strlen(clientPid) + strlen(clientsTempPath)];
    strcpy(clientNamedPipe, clientsTempPath);
    strcat(clientNamedPipe, clientPid);

    handleMessageByCode(Moderator, messageSplited, clientNamedPipe);

    freeTheArrayAllocatedMemory(&messageSplited);
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
    printf("#########################\n");
}

void displayGames(Moderator *Moderator) {
    GameApps *auxCreatedGames = Moderator->gameApps;

    printf("\n##### Jogos Criados #####\n");
    printf("Total: %i\n", Moderator->gameAppsLength);

    while (Moderator->gameApps != NULL) {

        printf("Nome: %s | Path: %s\n",
               Moderator->gameApps->name,
               Moderator->gameApps->path
        );

        Moderator->gameApps = Moderator->gameApps->prox;
    }

    Moderator->gameApps = auxCreatedGames;
    printf("#########################\n");
}

void readEnvVariables() {
    char *tempMaxPlayer = getenv("MAXPLAYERS"), *tempGameDir = getenv("GAMEDIR");

    if (tempGameDir == NULL || tempMaxPlayer == NULL) {
        printf("Erro: As variáveis de ambiente MAXPLAYERS e GAMEDIR não estão definidas.\nExecute primeiro o ficheiro setEnvVars.sh através do comando [source ./setEnvVars.sh] antes de executar o Arbitro\n");
        exit(0);
    }

    maxPlayers = stringToNumber(tempMaxPlayer);

    if (maxPlayers <= 0 || maxPlayers > MAX_PLAYERS) {
        system("clear");
        printf("\nErro: A variavel de ambiente MAXPLAYERS apresenta valores inválidos. O seu valor deve ser estar contido entre 1 e 30.\n");
        exit(1);
    }

    gameDir = tempGameDir;
}

void printInitialInformation(int waiting_time, int duration) {
    printf("*  MAXPLAYER             = %d\n",maxPlayers);
    printf("*  GAMEDIR               = %s\n",gameDir);
    printf("*  Moderator PID         = %d\n\n",getpid());
    printf("*  Championship duration = %d\n",duration);
    printf("*  Waiting time          = %d\n",waiting_time);
}

void sendSignal(int sig, int targetId){
    if(targetId != 0){
        if(sig == SIGTERM){
            kill(targetId, SIGTERM);
        }else if (sig == SIGUSR1){
            kill(targetId, SIGUSR1);
        }
    }
}

void startChampionship(Moderator *Moderator) {
    ConnectedClients *auxConnectedClient = Moderator->connectedClients;
    char buffer[STRING_BUFFER] = "\0";
    int clientFd = 0;

    Moderator->championStatus = CHAMPION_STARTED;

    while (Moderator->connectedClients != NULL)
    {
        sendMessageToChildProcess(Moderator->connectedClients->client.gameChildProcess->writeDescriptor, REQUEST_CODE_INIT_GAME);
        listeningResponse(Moderator->connectedClients->client.gameChildProcess->readDescriptor, buffer);
        
        clientFd = open(Moderator->connectedClients->client.pipeLocation, O_WRONLY);
        sendMessage(clientFd, initMessageModel(Moderator->pid, INFO, buffer));
        close(clientFd);

        memset(buffer, 0, sizeof(buffer));

        Moderator->connectedClients = Moderator->connectedClients->prox;
    }
    Moderator->connectedClients = auxConnectedClient;
}

void endChampionship(Moderator * Moderator) {
    ConnectedClients *auxConnectedClient = Moderator->connectedClients;
    int gamePoints = 0, winnerPoints = 0;
    char *pointsString, *winnerName;
    char messageBuffer[STRING_BUFFER] = "\0";

    int points[Moderator->connectedClientsLength];

    Moderator->championStatus = FINISHED;
    winnerPoints = gamePoints;
    winnerName = strdup(Moderator->connectedClients->client.userName);

    for (int i = 0; i < Moderator->connectedClientsLength || Moderator->connectedClients != NULL; i++){
        kill(Moderator->connectedClients->client.gameChildProcess->pid, SIGUSR1);
        
        wait(&gamePoints);

        gamePoints = gamePoints/256;

        points[i] = gamePoints;

        if (gamePoints > winnerPoints) {
            winnerPoints = gamePoints;
            winnerName = strdup(Moderator->connectedClients->client.userName);
        }

        free(Moderator->connectedClients->client.gameChildProcess);

        Moderator->connectedClients = Moderator->connectedClients->prox;
    }
    
    Moderator->connectedClients = auxConnectedClient;
    auxConnectedClient = NULL;

    for (int i = 0; i < Moderator->connectedClientsLength || Moderator->connectedClients != NULL; i++) {
        memset(messageBuffer, 0, sizeof(messageBuffer));
        
        strcat(messageBuffer, "\nO vencedor do campeonato é o jogador ");
        strcat(messageBuffer, winnerName);
        strcat(messageBuffer, " com ");
        strcat(messageBuffer, getNumberInString(winnerPoints));
        strcat(messageBuffer, " pontos.\n");
        strcat(messageBuffer, "A sua pontuação final foi de ");
        strcat(messageBuffer, getNumberInString(points[i]));
        strcat(messageBuffer, " pontos.\n");

        kill(Moderator->connectedClients->client.pid, SIGUSR1);

        int clientFd = open(Moderator->connectedClients->client.pipeLocation, O_WRONLY);
        sendMessage(clientFd, initMessageModel(Moderator->pid, INFO, messageBuffer));
        close(clientFd);

        auxConnectedClient = Moderator->connectedClients->prox;

        free(Moderator->connectedClients);

        Moderator->connectedClients = auxConnectedClient;
        Moderator->connectedClientsLength --;
    }

    memset(messageBuffer, 0, sizeof(messageBuffer));
    kill(Moderator->pid, SIGTERM);
}