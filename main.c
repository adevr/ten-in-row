#include <stdio.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    execl("moderator/moderator", "moderator", "-e", NULL);
}

/*
int main(int argc, char *argv[]) {

    Jogo *jogo = criaJogo();
    iniciaJogo(jogo);

    apresentaTabuleiro(jogo);
    executaJogada(jogo, 1, 1);
    printf("\n\n");
    apresentaTabuleiro(jogo);
    return 0;
}*/