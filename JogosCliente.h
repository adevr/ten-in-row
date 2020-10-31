//
// Created by alex on 31/10/20.
//

#ifndef TENINROW_JOGOSCLIENTE_H
#define TENINROW_JOGOSCLIENTE_H

#include "Cliente.h"
#include "Jogo.h"

struct JogosCliente {
    struct Cliente cliente;
    struct Jogo* jogos;
} jogosCliente;


#endif //TENINROW_JOGOSCLIENTE_H
