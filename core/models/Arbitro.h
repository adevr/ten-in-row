//
// Created by alex on 31/10/20.
//

#ifndef TENINROW_ARBITRO_H
#define TENINROW_ARBITRO_H

#include "Cliente.h"
#include "Jogo.h"
#include "JogosCliente.h"
#include "Administrador.h"

struct Arbitro {
    struct Clientes *clientes;
    struct Jogo *jogos;
    struct Administrador *administrador;
    struct JogosCliente *jogosCliente
} Arbitro;


#endif //TENINROW_ARBITRO_H
