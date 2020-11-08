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
    char *tempM = NULL, *tempG = NULL;

    if ((tempM = getenv("MAXPLAYERS")) == NULL || (tempG = getenv("GAMEDIR")) == NULL) {
        printf("********************************** \n");
        tempM == NULL ? printf("** [NOTICE] MAXPLAYERS env variable not defined **\n") : (maxPlayers = atoi(tempM));

        if (tempG == NULL) {
            printf("** [NOTICE] GAMEDIR env variable not defined **\n");
        } else {
            gameDir = tempG;
        }
        printf("********************************** \n");
    } else {
        maxPlayers = atoi(tempM);
        gameDir = tempG;
    }
}

void printInitialInformation(int waiting_time, int duration)
{
    printf("**************************************\n");
    printf("*  MAXPLAYER    = %d\n",maxPlayers);
    printf("*  GAMEDIR      = %s\n",gameDir);
    printf("*  Moderator PID = %d\n\n",getpid());
    printf("*  Championship duration = %d\n",duration);
    printf("*  Waiting time = %d\n",waiting_time);
    printf("**************************************\n");
}