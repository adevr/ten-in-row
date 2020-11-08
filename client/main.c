//
// Created by ubuntu on 07/11/20.
//

#include <unistd.h>
#include "Cliente.h"

int main(int argc, char *argv[]) {
    int pid = getpid();

    if (argc <= 0) {
        printf("\nÉ necessário passar o pid do arbitro como parametro.\n");
        return 0;
    }
    printf("\nPid do cliente: %i", pid);
    printf("\nPid do arbitro: %s", argv[0]);
}