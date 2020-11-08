//
// Created by alex on 31/10/20.
//

#ifndef TENINROW_CAMPEONATO_H
#define TENINROW_CAMPEONATO_H

#include "../application/Jogo.h"

typedef struct Campeonato {
    int duracao;
    int horaInicio;
    int horaFim;
    Jogo* jogos;
} Campeonato;

#endif //TENINROW_CAMPEONATO_H
