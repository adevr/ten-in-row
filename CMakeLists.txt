cmake_minimum_required(VERSION 3.17)
project(teninrow C)

set(CMAKE_C_STANDARD 99)

add_executable(teninrow main.c core/models/Jogador.c core/models/Jogador.h core/models/Campeonato.c core/models/Campeonato.h core/models/Cliente.c core/models/Cliente.h core/models/Arbitro.c core/models/Arbitro.h core/models/Jogo.c core/models/Jogo.h core/models/JogosCliente.c core/models/JogosCliente.h core/models/Administrador.c core/models/Administrador.h)