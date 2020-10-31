//
// Created by alex on 31/10/20.
//

#ifndef TENINROW_CLIENTE_H
#define TENINROW_CLIENTE_H

#include "Jogador.h"

struct Cliente {
    struct Jogador *jogador;
    struct Arbitro *arbitro;
} Cliente;

void getInput(int *linha);

void sendInput(int input);

#endif //TENINROW_CLIENTE_H
