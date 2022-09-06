#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

//Program służy do wysyłania sygnału do programu 3bb.c
//Wysyła oraz sposób obsługi dla podanego sygnalu do pliku 3bb.c za pomocą funkcji exec.
// wysyla sygnal do procesu potomnego.

int main(int argc, char *argv[])
{

    //Sprawdzenie ilości przekazanych argumentów.
    if (argc != 3)
    {
        printf("----------\nPodana liczba argumentow: %d,\nPrawidlowy schemat uruchomienia:\n./[Nazwa Pliku] [Sygnał] [Obsługa(a/b/c)]\nLub:\nmake run2 [Sygnał] [ARG1=(a/b/c) ARG2=(a/b/c)]\n----------\n", argc);
        exit(EXIT_FAILURE);
    }

    int sig = atol(argv[1]);

    //tworzenie procesu potomnego i zastosowanie go w funkcji switch
    int pid = fork();
    switch (pid)
    {

    case -1:
        //obsluga bledow fork.
        perror("fork error");
        exit(EXIT_FAILURE);
        break;

    case 0:
        //Dzialanie dla procesu potomnego:
        //Funkcja execl, wraz z kontrola bledow, sluzaca do wykonania programu do ktorego sie odnosi. Wysylam jej rowniez argumenty uruchomienia.

        if (execl("./3bb.x", "3bb.x", argv[1], argv[2], (char *)NULL) == -1)

        {
            perror("execl error");
            exit(EXIT_FAILURE);
        }

        break;

    default:
        //Dzialanie dla procesu macierzystego:
        //Sprawdzenie czy proces istnieje.
        if (kill(pid, 0) == -1)
        {
            perror("PROCESS NON EXIST");
            exit(EXIT_FAILURE);
        }
        //Uspienie procesu i wyslanie sygnalu.

        sleep(2);
        kill(pid, sig);

        //Funkcja wait oczekujaca na zakonczenie dzialania procesu potomnego wraz z kontrola bledow
        if (wait(NULL) == -1) // wait zwraca -1 przy nieprawidlowy wykonaniu
        {
            perror("WAIT ERROR");
            exit(EXIT_FAILURE);
        }

        break;
    }
    return EXIT_SUCCESS;
}
