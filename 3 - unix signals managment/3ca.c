#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

//Program Wysyla sygnal kill do grupy procesow wywolanych przez proces potomny w jego procesie potomnym za pomoca funkcji exec.
//Tworzy proces potomny ktory staje sie liderem grupy procesow
//Do grupy procesow potomnych ktorych liderem jest proces utworzony w tym pliku wysylane sa sygnaly z procesu macierzystego.

int main(int argc, char *argv[])
{
    //Sprawdzenie liczby podanych argumentow.
    if (argc != 3)
    {
        printf("----------\nPodana liczba argumentow: %d,\nPrawidlowy schemat uruchomienia:\n./[Nazwa Pliku] [Sygnał] [Obsługa(a/b/c)]\nLub:\nmake run3 [Sygnał] [ARG1=(a/b/c) ARG2=(a/b/c)]\n----------\n", argc);
        exit(EXIT_FAILURE);
    }
    int status;
    int sig = atoi(argv[1]);
    char *obsluga = argv[2];
    int pid = fork();

    //funkcja switch okreslajaca akcje dla procesu macierzystego oraz potomnego
    switch (pid)
    {

    case -1:
        //obsluga bledow fork.
        perror("fork error");
        exit(EXIT_FAILURE);
        break;

    case 0:
        //Dzialanie dla procesu potomnego
        //ustawienie procesu potomnego liderem grupy procesow.
        setpgid(0, 0);
        //Funkcja execl ktora otwiera plik 3cb.x i go wykonuje, biorac pod uwage argumenty wywolania.
        if (execl("./3cb.x", "3cb.x", argv[1], argv[2], (char *)NULL) == -1)
        {
            perror("execl error");
            exit(EXIT_FAILURE);
        }

    default:
        //Dzialanie dla procesu macierzystego
        //uspienie procesu oraz sprawdzenie czy istnieje szukany proces.
        sleep(2);
        printf("PROCES MACIERZ: PID = %d, PGID = %d\n", getpid(), getpgrp());
        if (kill(pid, 0) == -1)
        {
            perror("PROCESS NON EXIST");
            exit(EXIT_FAILURE);
        }

        //Uzyskanie ID grupy procesow
        int wnuki = getpgid(pid);
        // Funkcja kill
        //parametr -1 * wnuki --- odnosi się do Procesow nalezacych do grupy o PGID = -pid
        //parametr sig - sygnal jaki funkcja kill wysyla.
        kill(-1 * wnuki, sig);
        //Funkcja wait oczekujaca na zakonczenie procesow potomnych
        if (wait(&status) == -1)
        {
            perror("WAIT ERROR");
            exit(EXIT_FAILURE);
        }
    }
}
