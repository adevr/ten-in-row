/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "constants/constants.h"

int main(int argc, char *argv[])
{
    char option;

    setenv("GAMEDIR", "application/", 0);
    setenv("MAXPLAYERS", "30", 0);

    printf("\t########## SISTEMA CHAMPION ##########\n");
    printf("Iniciar: \n");
    printf("\t 1 -> Arbitro\n");
    printf("\t 0 -> SAIR\n");

    while (1) {
        printf("\nOPCAO $: ");
        scanf(" %c", &option);

        if (option == '1') {
            char duration[INPUT_BUFFER];
            char waitTime[INPUT_BUFFER];

            printf("\nIntroduzir duracao do campeonato: ");
            scanf("%29s", duration);

            printf("\nIntroduzir tempo de espera do campeonato: ");
            scanf("%29s", waitTime);

            execl("./moderator/moderator", "moderator", "-d", duration, "-w", waitTime, NULL);
            exit(0);
        }

        if (option == '0') {
            printf("sair\n");
            exit(1);
        }
        printf("Escolha outra opcao\n");
    }
}

