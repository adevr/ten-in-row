cmake_minimum_required(VERSION 3.17)
project(teninrow C)

set(CMAKE_C_STANDARD 99)

add_executable(
        teninrow main.c
        moderator/Moderator.c
        moderator/Moderator.h
        moderator/main.c
        client/Client.c
        client/Client.h
        client/main.c
        application/Jogo.c
        application/Jogo.h
        application/main.c
        )