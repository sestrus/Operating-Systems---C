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

int main(int argc, char *argv[])
{

    int wartosc;
    sem_t *my_semaphore;
    int liczSyg;
    int liczba_kryt = atoi(argv[2]);

    //Petla okreslajaca ilosc sekcji krytycznych
    for (int i = 0; i < liczba_kryt; i++)
    {
        //Otworzenie semafora
        my_semaphore = otworzSemafor("/semafor");
        //inicjacja pseudolosowego czasu.
        srand(time(NULL));
        int sen;

        //pozyskanie wartosci semafora
        pozyskajWartosc(my_semaphore, &wartosc);
        printf("PID:%d, Jestem przed sekcja krytyczna: %d, Wartosc semafora: %d\n", getpid(), i + 1, wartosc);
        sleep(2);
        //Opuszczenie semafora - sekcja krytyczna
        opuscSemafor(my_semaphore);

        //pozyskanie wartosci semafora
        pozyskajWartosc(my_semaphore, &wartosc);

        //Otworzenie i przeczytanie pliku oraz zwiekszenie wartosci o 1
        FILE *fp;
        fp = fopen("numerek.txt", "r");
        if (fp == NULL)
        {
            perror("fp open error");
            _exit(-1);
        }
        char buff[200];
        fscanf(fp, "%s", buff);
        int liczba = atoi(buff);
        liczba = liczba + 1;
        printf("PID:%d, Jestem w sekcji krytycznej: %d, Wartosc semafora: %d wartosc numeru: %d\n", getpid(), i + 1, wartosc, liczba);
        fclose(fp);

        //Otworzenie pliku oraz wpisanie kolejnej liczby.
        FILE *fo;
        fo = fopen("numerek.txt", "w");

        //uspienie o pseudolosowej dlugosci
        sen = (rand() % 40 + 30);
        sleep(sen / 25);
        fprintf(fo, "%d", liczba);
        fclose(fo);

        //Podniesienie semafora oraz pozyskanie jego wartosci oraz jej wypisanie
        podniesSemafor(my_semaphore);
        pozyskajWartosc(my_semaphore, &wartosc);
        printf("PID:%d, Jestem po sekcji krytycznej: %d, Wartosc semafora: %d\n\n\n", getpid(), i + 1, wartosc);

        //Zamkniecie semafora
        // zamknijSemafor(my_semaphore);
    }
    zamknijSemafor(my_semaphore);
}
