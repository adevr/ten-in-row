cmake_minimum_required(VERSION 3.17)
project(teninrow C)

set(CMAKE_C_STANDARD 99)

add_executable(
        teninrow main.c
        moderator/Jogador.c
        moderator/Jogador.h
        moderator/Campeonato.c
        moderator/Campeonato.h
        moderator/Arbitro.c
        moderator/Arbitro.h
        moderator/main.c
        client/Cliente.c
        client/Cliente.h
        client/main.c
        application/Jogo.c
        application/Jogo.h
        application/main.c
        )