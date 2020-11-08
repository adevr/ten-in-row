#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    char opcao[2];
    printf("\t########## SISTEMA CHAMPION ##########\n");
    printf("Iniciar: \n");
    printf("\t 1 -> Arbitro\n");
    printf("\t 0 -> SAIR\n");

    execl("exportVars", "exportVars", NULL);
    while (1) {
        printf("\nOPCAO $: ");
        scanf("%1s", opcao);

        if (!strcmp(opcao, "1")) {
            // colocar aqui argumentos ou iniciar o moderator de outra forma
            execl("moderator/moderator", "moderator", NULL);
            continue;
        }

        if (!strcmp(opcao, "0")) {
            printf("sair\n");
            exit(0);
        }

        printf("escolha outra opcao\n");
    }
    // int pid = getpid();
    // printf("\nprocessPID: %i\n", pid);
    //execl("moderator/moderator", "moderator", "-e", NULL);
}

