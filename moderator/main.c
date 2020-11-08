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
    int championship_duration, waiting_time;

    if (argc < 5) {
        printf("Incorrect set of arguments passed to the program. Must use: \n");
        printf("./moderator {championship duration} {waiting time}\n");
        return 0;
    }

    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "d")) {
            i++;
            championship_duration = atoi(argv[i]);
        }

        if (!strcmp(argv[i], "w")) {
            i++;
            waiting_time = atoi(argv[i]);
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