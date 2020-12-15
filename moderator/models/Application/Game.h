/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#ifndef TEN_IN_ROW_GAME_H
#define TEN_IN_ROW_GAME_H

typedef struct Game {
    int pid;
    char *name;
    int readDescriptor;
    int writeDescriptor;
} Game;

typedef struct CreatedGames {
    struct CreatedGames *prev;
    Game game;
    struct CreatedGames *prox;
} CreatedGames;


Game initGame(int gamePid, char* name, int readDescriptor, int writeDescriptor);

#endif //TEN_IN_ROW_GAME_H
