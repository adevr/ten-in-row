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
#include "Moderator.h"

#define TEMP_ROOT_PATH "/tmp/ten-in-row"
#define TEMP_MODERATOR_PATH "/tmp/ten-in-row/moderator"
#define TEMP_CLIENTS_PATH "/tmp/ten-in-row/clients"

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
    Client client1, client2;
    Game game1, game2;

    client1 = initClient(123, "Diogo", "pipeClient1");
    client2 = initClient(1234, "Diogo2", "pipeClient2");

    game1 = initGame(321, 1, 2);
    game2 = initGame(4321, 3, 4);

    makeConnection(&Moderator->Connections, client1, game1);
    makeConnection(&Moderator->Connections, client2, game2);

    for (int i = 0; i < Moderator->Connections.length; ++i) {
        printf("Node\n");
        printf("PID: %i | User: %s\n", Moderator->Connections.RunningGames->Client.pid, Moderator->Connections.RunningGames->Client.userName);
        printf("------------\n");
        Moderator->Connections.RunningGames = Moderator->Connections.RunningGames->prox;
    }
}

/* TODO
 * Create a specific buffer to carry the messages info
 * Create the threads to:
 *      -> handle the CHAMPION duration and interrupt the games
 *      -> send info in a json format to the clients (data structure to be defined)
 *      -> to send the inputs received from a client to the related game
 *      -> ...
 *
 * The read isn't working well. Check the class videos to create a proper reader
 */
int main(int argc, char *argv[]) {
    //getArgsValues(argc, argv);
    setTempPaths();

    Moderator Moderator = initModerator();
    char *moderatorPipePath = createModeratorPipe(&Moderator, TEMP_MODERATOR_PATH);
    Moderator.pipeDescriptor = open(moderatorPipePath, O_RDWR);

    while (1) {
        char responseBuffer[STRING_BUFFER];

        // The loop waits until the pipe receives a new message
        read(Moderator.pipeDescriptor, responseBuffer, sizeof(responseBuffer));

        printf("Reponse: %s \n", responseBuffer);
    }

    return 0;
}


