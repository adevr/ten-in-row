//
// Created by alex on 31/10/20.
//

#ifndef TENINROW_ARBITRO_H
#define TENINROW_ARBITRO_H

#define USER_SIZE 25
#define MAX_PLAYERS 30

int maxPlayer;
char *gameDir;
typedef struct Arbitro {
    int pid;
    int jogo_pid;
    int client_pid;
    char user[USER_SIZE];
} Arbitro;


#endif //TENINROW_ARBITRO_H
