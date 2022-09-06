#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

//Tworzy procesy potomne, dla ktorych jest liderem grupy
//proces potomny uruchamiany w funkcji execl
//czeka na zakończenie wszystkich procesow potomnych.

int main(int argc, char *argv[])
{

    int sig = atoi(argv[1]);
    char *obsluga = argv[2];

    int pid;
    //Ignorowanie sygnalu.
    if (signal(sig, SIG_IGN) == SIG_ERR)
    {
        perror("SIG_IGN ERROR\n");
        exit(EXIT_FAILURE);
    }

    printf("PROCES DZIECKO: PID = %d, PGID = %d\n", getpid(), getpgrp());

    //Potrojne wywolanie  funkcji fork
    for (int i = 0; i < 3; i++)
    {
        switch (pid = fork())
        {

        case -1:
            //obsluga bledow fork.
            perror("fork error");
            exit(EXIT_FAILURE);
            break;

        case 0:
            //Nadanie PGID = PPID procesowi wywolanemu przez execl
            setpgid(0, getppid());
            printf("PROCES WNUK:    PID = %d, PGID = %d\n", getpid(), getpgrp());

            if (execl("./3cc.x", "3cc.x", argv[1], argv[2], (char *)NULL) == -1)

            {
                perror("execl error");
                exit(EXIT_FAILURE);
            }

        default: //Dzialanie dla procesu macierzystego.
            break;
        }
    }

    //Potrojna funkcja wait aby procesy wszystkie procesy czekaly na sygnal
    if (wait(NULL) == -1)
    {
        perror("WAIT ERROR");
        exit(EXIT_FAILURE);
    }
    if (wait(NULL) == -1)
    {
        perror("WAIT ERROR");
        exit(EXIT_FAILURE);
    }
    if (wait(NULL) == -1)
    {
        perror("WAIT ERROR");
        exit(EXIT_FAILURE);
    }
}
