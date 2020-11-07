//
// Created by alex on 31/10/20.
//

#ifndef TENINROW_JOGOSCLIENTE_H
#define TENINROW_JOGOSCLIENTE_H

#include "Cliente.h"
#include "Jogo.h"

typedef struct JogosCliente {
    Cliente cliente;
    Jogo* jogos;
} JogosCliente;


#endif //TENINROW_JOGOSCLIENTE_H
