cmake_minimum_required(VERSION 3.17)
project(teninrow C)

set(CMAKE_C_STANDARD 99)

add_executable(teninrow main.c moderator/Jogador.c moderator/Jogador.h moderator/Campeonato.c moderator/Campeonato.h client/Cliente.c client/Cliente.h moderator/Arbitro.c moderator/Arbitro.h application/Jogo.c application/Jogo.h core/models/JogosCliente.c core/models/JogosCliente.h moderator/Administrador.c moderator/Administrador.h)