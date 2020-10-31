cmake_minimum_required(VERSION 3.17)
project(teninrow C)

set(CMAKE_C_STANDARD 99)

add_executable(teninrow main.c Jogador.c Jogador.h Campeonato.c Campeonato.h Cliente.c Cliente.h Arbitro.c Arbitro.h Jogo.c Jogo.h JogosCliente.c JogosCliente.h Administrador.c Administrador.h)