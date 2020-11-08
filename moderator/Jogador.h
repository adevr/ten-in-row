//
// Created by alex on 31/10/20.
//

#ifndef TENINROW_JOGADOR_H
#define TENINROW_JOGADOR_H

#define USERNAME_SIZE 50

typedef struct Jogador {
    char nome[USERNAME_SIZE];
    int pontuacao; // ? NEcessário? A pontuação basta ser controlada pelo jogo
} Jogador;

#endif //TENINROW_JOGADOR_H
