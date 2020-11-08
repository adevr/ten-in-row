//
// Created by ubuntu on 07/11/20.
//

#include <unistd.h>
#include <stdio.h>


int main(int argc, char *argv[]) {
    int pid = getpid();
    char *pidStr;
    sprintf(pidStr, "%i", pid);


    int cli_pid = fork();
    if (cli_pid == 0) {
        execl("client/client", pidStr, NULL);
    }

    printf("\nArbitro: Pid client: %i\n", cli_pid);
    printf("\nArbitro: Meu pid: %i\n", pid);




}