
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <sys/param.h>
#include "mylib.h"
sem_t *my_semaphore;
//funkcja dla atexit, opuszcza semafor
void unlinking(void)
{

    odlaczSemafor("/semafor");
}
//Funkcja do wlasnej obslugi sygnalu SIGINT
void wlasna_obsluga(sig)
{
    odlaczSemafor("/semafor");
}
//Program realizuje wywolanie wzajemnego wykluczania. Tworzy i otwiera semafor,
//inicjuje ilosc procesow realizujacych wzajemne wykluczanie, Tworzy plik txt i wpisuje,
// do niego wartosc zero,sprawdza czy numer w pliku tekstowym zwiekszyl sie o odpowiednia ilosc razy.
//na koniec zamyka semafor

int main(int argc, char *argv[])
{

    //awaryjna obsluga sygnalu SIGINT
    if (signal(SIGINT, &wlasna_obsluga) == SIG_ERR)
    {
        perror("Funkcja signal ma problem z SIGQUIT");
        exit(EXIT_FAILURE);
    }

    sem_t *my_semaphore;

    //Tworzy i otwiera semafor oraz pobiera jego adres
    my_semaphore = stworzSemafor("/semafor");
    printf("Semafor utworzony i podniesiony\n");
    printf("Adres semafora: %p\n\n", (void *)my_semaphore);

    //Tworzy plik, otwiera go oraz wpisuje do niego wartosc 0
    FILE *create;
    create = fopen("numerek.txt", "w");
    if (create == NULL)
    {
        perror("fopen error");
        exit(-3);
    }
    fprintf(create, "0");
    fclose(create);

    //Ilosc procesow potomnych, pobrana przez argumenty wywolania funkcji
    int liczSyg;
    liczSyg = atoi(argv[1]);
    int licz = 0;
    for (int i = 0; i < liczSyg; i++)
    {
        licz = licz + 1;
        switch (fork())
        {
        case -1: //obsluga bledow
            perror("fork error");
            exit(-1);

        case 0: //Dzialanie dla procesu potomnego
            //Proces potomny wykona program pod adresem argv[3]=wyklucz.c
            //Przesylam rowniez argumenty wywolania takie jak:
            //argv[1] - ilosc utworzonych procesow wykonujacych wyklucznie
            //argv[2] - ilosc sekcji krytycznych
            //argv[4] - nazwa semafora

            if (execl(argv[3], argv[3], argv[1], argv[2], (char *)NULL) == -1)
            {
                perror("execl error");
                _exit(-5);
            }

        default:

            break;
        }
    }
    int sprawdz = atoi(argv[1]) * atoi(argv[2]);
    for (int i = 0; i < sprawdz; i++)
    {
        wait(NULL);
    }
    //Sprawdzenie jaka liczba znajduje sie w pliku numerek.txt
    FILE *check;
    char buff[200];
    check = fopen("numerek.txt", "r");
    if (check == NULL)
    {
        perror("check fopen error");
        exit(-4);
    }

    //Sprawdzenie czy w pliku znajduje sie odpowiednia liczba

    fscanf(check, "%s", buff);

    int liczba = atoi(buff);
    printf("Końcowa wartość numeru z pliku numerek.txt: %d\n", liczba);

    if (liczba == sprawdz)
    {
        printf("Liczba w pliku prawidlowa\n");
    }
    else
    {
        printf("Liczba w pliku niepoprawna\n");
    }
    //odlaczenie semafora
    if (atexit(unlinking) != 0)
    {
        perror("atexit error");
        exit(EXIT_FAILURE);
    }

    fclose(check);
}