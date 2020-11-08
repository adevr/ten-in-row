/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#ifndef TENINROW_CLIENT_H
#define TENINROW_CLIENT_H

#include "stdio.h"

#define USER_SIZE 25

typedef struct Client {
    int pid;
    char user[USER_SIZE];
    int points;
} Cliente;

void startClient();

#endif //TENINROW_CLIENT_H
