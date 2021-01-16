/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "Game.h"
#include "../helpers/helpers.h"

Game *game;

void getArgsValues(int argc, char *argv[]) {
    if (argc == 1) {
        return;
    }

    if (argc == 2) {
        printf("Incorrect set of arguments passed to the program.\n");
        printf("Must use: ./{games program} {file descriptor to read} {file descriptor to write}\n");
        exit(0);
    }

    game->readFd = stringToNumber(argv[1]);
    game->writeFd = stringToNumber(argv[2]);
}

void setFileDescriptors() {
    dup2(game->readFd, 0);
    dup2(game->writeFd, 1);

    close(game->readFd);
    close(game->writeFd);
}

void welcomeMenu() {
    printf(
        "\n\t ############################################ \n\t"
        "###### Bem vindo ao jogo 10-em-linha! ###### \n"
        "\t ##### O jogo favorito da tua infancia ###### \n"
        "\t ############################################ \n"
        "\t ################## Regras ################## \n"
        "\t #      -> 1 Linha completa = 1 ponto       # \n"
        "\t #      -> Maximo de 2 utilizadores         # \n"
        "\t #      -> 2 tipos de caracteres: `*` `º`   # \n"
        "\t #      -> Uma jogada de cada vez           # \n"
        "\t ############################################ \n"
        "\t # O jogo termina, assim que acabar o tempo # \n"
        "\t ############################################ \n"
        "\t ##### (A) Avançar ########## (S) Sair ###### \n"
        "\t ############################################ \n"
        "\t ##### Selecione opção: "
    );
    fflush(stdout);
}

void gameSig_handler(int signo){
    if (signo == SIGUSR1){
        // todo: get sig user 1
        // send the points to the client
        printf("\n PID: %i", game->PID);
        printf("\n POINTS: %i \n", game->points);
        exit(game->points);
    }

    if (signo == SIGTERM || signo == SIGINT){
        exit(0);
    }

}

/*
    TODO 
        if there are 0 arguments, run the game normaly
        if not, the game should work by instructions:
            -> getWelcomeMessage;
            -> startGame;

*/
int main(int argc, char *argv[]) {
    int column = 0;
    int playsCounter = 1;
    char selection;

    game = createGame();
    getArgsValues(argc, argv);

    if (argc > 2) {
        setFileDescriptors();
    }

    welcomeMenu();

    scanf("%c", &selection);
    if(selection != 'A' && selection != 'a'){
        exit(1);
    }
    
    initGame(game);

    
    if (signal(SIGUSR1, gameSig_handler) == (sig_t)SIG_ERR)
        printf("\ncan't catch SIGINT\n");

    //printf("%i", game->PID);

    if (signal(SIGINT, gameSig_handler) == (sig_t)SIG_ERR)
        printf("\ncan't catch SIGINT\n");


    while (1) {
        
        char* pieceToPlay = (playsCounter % 2 == 0) ? PIECE_O : PIECE_X;

        showGameTable(game);

        if(strcmp (pieceToPlay, PIECE_X) == 0){
            printf("\t # Peça: "); 
            printf("\e[38;5;82m");
            printf("%s", pieceToPlay);
            printf("\033[0m|");
            printf(". Coluna (1 - %i): ", NR_OF_COLUMNS);
        }else{
            printf("\t # Peça: "); 
            printf("\033[22;34m");
            printf("%s", pieceToPlay);
            printf("\033[0m|");
            printf(". Coluna (1 - %i): ", NR_OF_COLUMNS);
        }

        
        scanf("%i", &column);
        /*if(column == 0){
            exit(1);
        }*/
        doPlay(game, pieceToPlay,column - 1);

        playsCounter ++;
        system("clear");
    }
    return 0;
}