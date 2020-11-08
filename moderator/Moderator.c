/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "Moderator.h"

void readEnvVariables() {
    char *tempMaxPlayer = getenv("MAXPLAYERS"), *tempGameDir = getenv("GAMEDIR");

    if (tempGameDir == NULL || tempMaxPlayer == NULL) {
        tempM == NULL ? printf("Notice: MAXPLAYERS env variable not defined **\n") : (maxPlayers = atoi(tempM));

        if (tempG == NULL) {
            printf("Notice: GAMEDIR env variable not defined **\n");
        } else {
            gameDir = tempG;
        }

        printf("********************************** \n");
        exit(0);
    } else {
        maxPlayers = atoi(tempMaxPlayer);
        gameDir = tempGameDir;
    }
}

void printInitialInformation(int waiting_time, int duration)
{
    printf("*  MAXPLAYER    = %d\n",maxPlayers);
    printf("*  GAMEDIR      = %s\n",gameDir);
    printf("*  Moderator PID = %d\n\n",getpid());
    printf("*  Championship duration = %d\n",duration);
    printf("*  Waiting time = %d\n",waiting_time);
}