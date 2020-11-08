/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#ifndef TENINROW_MODERATOR_H
#define TENINROW_MODERATOR_H
#define USER_SIZE 25

int maxPlayers;
char *gameDir;

typedef struct Moderator {
    int pid;
    int game_pid;
    int client_pid;
    int points;
    char user[USER_SIZE];
} Moderator;

void readEnvVariables();
void printInitialInformation(int waiting_time, int duration);

#endif //TENINROW_MODERATOR_H