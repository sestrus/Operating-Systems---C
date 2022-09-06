
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

//Program  oczekuje i obsluguje wysylane mu sygnały na 3 sposoby:
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
    //Sprawdzenie ilości wpisanych argumentów
    if (argc != 3)
    {
        printf("----------\nPodana liczba argumentow: %d,\nPrawidlowy schemat uruchomienia:\n./[Nazwa Pliku] [Sygnał] [Obsługa(a/b/c)]\nLub:\nmake run1 [Sygnał] [ARG1=(a/b/c) ARG2=(a/b/c)]\n----------\n", argc);
        exit(EXIT_FAILURE);
    }

    //Zamiana typu danych celem uzycia ich w dalszej części programu
    int sig = atol(argv[1]);

    //Wypisanie PID procesu obsługującego sygnał.
    printf("PID = %d\n", getpid());

    //Obsługa sygnału w zależności od wprowadzonego drugiego argumentu wywolania programu.

    //Sygnał wykona stanardową operację
    if (*argv[2] == 'a')
    {
        if (signal(sig, SIG_DFL) == SIG_ERR)
        {
            perror("Funkcja signal ma problem z SIGQUIT");
            exit(EXIT_FAILURE);
        }
        //Pause aby proces czekał na sygnał który obsłuży w wybrany sposób(Tutaj wykona standardowe działanie)
        if (pause() != -1)
        {
            perror("\npause error\n");
            exit(1);
        }
    }

    //Sygnał zignoruje sygnał(Jeżeli jest to możliwe)
    if (*argv[2] == 'b')
    {
        if (signal(sig, SIG_IGN) == SIG_ERR)
        {
            perror("Funkcja signal ma problem z SIGQUIT");
            exit(EXIT_FAILURE);
        }
        if (pause() != -1)
        {
            perror("\npause error\n");
            exit(1);
        }
    }

    //Obsluga sygnalu zdefiniowana przez uzytkownika
    if (*argv[2] == 'c')
    {

        if (signal(sig, &wlasna_obsluga) == SIG_ERR)
        {
            perror("Funkcja signal ma problem z SIGQUIT");
            exit(EXIT_FAILURE);
        }
        if (pause() != -1)
        {
            perror("\npause error\n");
            exit(1);
        }
    }

    return 0;
}