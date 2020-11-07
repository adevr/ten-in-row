//
// Created by alex on 31/10/20.
//

#ifndef TENINROW_CLIENTE_H
#define TENINROW_CLIENTE_H

#include "stdio.h"

#define USER_SIZE 25

typedef struct Cliente {
    int pid;
    char user[USER_SIZE];
    int pontos;
} Cliente;

void getInput(int *linha);

void sendInput(int input);

void startClient();

#endif //TENINROW_CLIENTE_H
