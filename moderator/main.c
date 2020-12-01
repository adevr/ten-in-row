/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Moderator.h"

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

int main(int argc, char *argv[]) {
    getArgsValues(argc, argv);
    return 0;
}