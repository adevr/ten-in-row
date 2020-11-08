/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Moderator.h"

int main(int argc, char *argv[]) {
    int op;
    int championship_duration, waiting_time;

    if (argc < 3) {
        printf("Incorrect set of arguments passed to the program. Must use: \n");
        printf("./moderator {championship duration} {waiting time}\n");
        return 0;
    }

    while ((op = getopt(argc, argv, "ce:")) != -1) {
        switch (op) {
            case 'c':
                if (strcmp(argv[1], "-c") == 0) {
                    championship_duration = atoi(argv[2]);
                } else {
                    championship_duration = atoi(argv[4]);
                }
                break;
            case 'e':
                if (strcmp(argv[1], "-e") == 0) {
                    waiting_time = atoi(argv[2]);
                } else {
                    waiting_time = atoi(argv[4]);
                }
                break;
        }
    }

    system("clear");
    readEnvVariables();
    printInitialInformation(waiting_time, championship_duration);
    return 0;
}


void testMethod() {
    int pid = getpid();
    char *pidStr;
    sprintf(pidStr, "%i", pid);

    int cli_pid = fork();
    if (cli_pid == 0) {
        execl("client/client", pidStr, NULL);
    }

    printf("\nArbitro: Pid client: %i\n", cli_pid);
    printf("\nArbitro: Meu pid: %i\n", pid);
}