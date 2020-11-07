//
// Created by ubuntu on 07/11/20.
//

#include <unistd.h>


int main(int argc, char *argv[]) {

    int cli_pid = fork();
    if (cli_pid > 0) {
        execl("/usr/bin/xterm", "/usr/bin/xterm", "-e", "bash", "-c", (void*)NULL);
        //execl("/usr/bin/xterm", "xterm", "./client/client", NULL);
        //execl("client/client", "client", "-e", NULL);
    }

}