#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    char opcao[2];
    printf("\t########## SISTEMA CHAMPION ##########\n");
    printf("Iniciar: \n");
    printf("\t 1 -> Arbitro\n");
    printf("\t 0 -> SAIR\n");

    setenv("GAMEDIR", "application/", 0);
    setenv("MAXPLAYERS", "15", 0);

    while (1) {
        printf("\nOPCAO $: ");
        scanf("%1s", opcao);

        if (!strcmp(opcao, "1")) {
            char duration[12];
            char waitTime[12];

            printf("\nIntroduzir duracao do campeonato: ");
            scanf("%s", duration);

            printf("\nIntroduzir tempo de espera do campeonato: ");
            scanf("%s", waitTime);

            execl("./moderator/moderator", "moderator", duration, waitTime, NULL);
            exit(0);
        }

        if (!strcmp(opcao, "0")) {
            printf("sair\n");
            exit(0);
        }

        printf("escolha outra opcao\n");
    }
}

