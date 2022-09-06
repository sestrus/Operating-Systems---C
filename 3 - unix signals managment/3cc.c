#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

//Program obsluguje wysylane mu sygnały na 3 sposoby:
//1. Wykonuje operacje domyślną sygnału
//2. Ignoruje sygnał
//3. Przechwytuje i obsluguje sygnał na swój sposób.

//Funkcja wykonywana po przechwyceniu sygnału.
void wlasna_obsluga(int sig)
{

    printf("NUMER SYGNAŁU TO: %d\n", sig);
}

int main(int argc, char *argv[])
{

    //zamiana argumentu wywołania programu z typu 'char' na 'int'
    int sig = atol(argv[1]);
    char *obsluga = argv[2];
    //Wypisanie PID procesu obsługującego sygnał.
    //printf("PROCES WNUK: PID = %d, PGID = %d\n", getpid(), getpgrp());

    //
    //Obsluga sygnalow taka sama jak w 3a.c i 3ca.c
    //
    if (*argv[2] == 'a')
    {
        //Obsluga sygnalow taka sama jak w 3a.c i 3ca.c
        if (signal(sig, SIG_DFL) == SIG_ERR)
        {
            perror("SIG_DFL ERROR");
            exit(EXIT_FAILURE);
        }
        if (pause() != -1)
        {
            perror("\npause error\n");
            exit(EXIT_FAILURE);
        }
    }

    if (*argv[2] == 'b')
    {

        if (signal(sig, SIG_IGN) == SIG_ERR)
        {
            perror("SIG_IGN ERROR");
            exit(EXIT_FAILURE);
        }
        if (pause() != -1)
        {
            perror("\npause error\n");
            exit(EXIT_FAILURE);
        }
    }

    else if (*argv[2] == 'c')
    {

        if (signal(sig, &wlasna_obsluga) == SIG_ERR)
        {
            perror("OBSLUGA WLASNA ERROR");
            exit(EXIT_FAILURE);
        }
        if (pause() != -1)
        {
            perror("\npause error\n");
            exit(EXIT_FAILURE);
        }
    }
}