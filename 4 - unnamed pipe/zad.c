#define O_RDONLY 00
#define O_WRONLY 01
#include <limits.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/param.h>

//plik --> bufor, bufor --> pipe, pipe --> bufor2, bufor2 --> plik2
//Producent pobiera surowiec z pliku tekstowego i wstawia go jako towar do potoku.
//Konsument natomiast umieszcza pobrany z potoku towar w innym pliku tekstowym.

int main(int argc, char *argv[])
{
    //Zarezerwowanie miejsca na bufory i deskryptor,
    //Utworzenie potoku.
    char *buffor1;
    char *buffor2;
    buffor1 = malloc(50);
    buffor2 = malloc(50);
    int deskryptor[2];
    if (pipe(deskryptor) == -1)
    {
        perror("pipe error\n");
        exit(EXIT_FAILURE);
    }
    //Zakonczenie dzialania jesli niezgadza sie ilosc argumentow wywolania funkcji.
    if (argc != 3)
    {
        printf("Zle parametry! Prawidlowe wywolanie:\n./[Nazwa Pliku] [Nazwa pliku z danymi] [Nazwa pliku z wynikami]\nLub:\nMake run1 [Nazwa pliku z danymi] [Nazwa pliku z wynikami]\n");
        exit(EXIT_FAILURE);
    }

    //------------------------------------------------------------------
    //Utworzenie deskryptorow plikow z ktorych procesy beda czytac/do ktorych beda pisac.
    //

    int czytaj = open(argv[1], O_RDONLY, 0644);
    int pisz = open(argv[2], O_WRONLY, 0644);
    if (pisz == -1)
    {
        perror("open czytaj error");
        exit(EXIT_FAILURE);
    }
    if (czytaj == -1)
    {
        perror("open pisz error");
        exit(EXIT_FAILURE);
    }
    //------------------------------------------------------------------
    //Utworzenie procesu potomnego.
    int pid = fork();
    if (pid == -1)
    { //obsluga bledow fork
        perror("fork error");
        exit(EXIT_FAILURE);
    }
    //-----------------------------------------------------------------

    if (pid == 0)
    {
        //Dzialanie dla procesu potomnego:
        //zamkniecie nieuzywanego deskryptora
        if (close(deskryptor[0]) == -1)
        {
            perror("close error");
            exit(EXIT_FAILURE);
        }
        //Inicjowanie dla liczb pseudolosowych.
        srand(time(NULL));
        int sen;

        //czytanie z pliku i przenoszenie do buffora1
        int x;
        x = read(czytaj, buffor1, 20);
        if (x == -1)
        {
            perror("Read error");
            exit(EXIT_FAILURE);
        }

        //Działanie gdy funkcja read zakonczy sie sukcesem oraz gdy nie doszla do konca pliku
        while (x > 0)
        {
            //Zapisanie danych z buffora1 do miejsca okreslonego przez deskryptor
            if (write(deskryptor[1], buffor1, x) == -1)
            {
                perror("Write error");
                exit(EXIT_FAILURE);
            }
            //Wypisanie w konsoli komunikatu o dzialaniu producenta
            if (write(STDOUT_FILENO, "Producent: ", 12) == -1)
            {
                perror("Write error");
                exit(EXIT_FAILURE);
            }
            //Wypisanie dzialania ktore przebiega dla producenta
            if (write(STDOUT_FILENO, buffor1, x) == -1)
            {
                perror("Write error");
                exit(EXIT_FAILURE);
            }

            //Uspienie o pseudolosowej dlugosci

            sen = rand() % 40 + 30;
            sleep(sen / 30);
            printf("\n");

            //Wczytuje do buforu kolejna porcje danych.
            x = read(czytaj, buffor1, 20);
            if (x == -1)
            {
                perror("Read error");
                exit(EXIT_FAILURE);
            }
        }
        //Zamkniecie deskryptora[1]
        if (close(deskryptor[1]) == -1)
        {
            perror("close error");
            exit(EXIT_FAILURE);
        }
    }
    else
    { //Dzialanie dla procesu macierzystego
        if (close(deskryptor[1]) == -1)
        {
            perror("close error");
            exit(EXIT_FAILURE);
        }
        //Uspienie, oraz inicjacja liczb pseudolosowych do uzycia w pozniejszym uspieniu.
        sleep(1);
        srand(time(NULL));
        int sen;

        //Odczytuje z deskryptora dane i umieszcza w bufforze.
        int y;
        y = read(deskryptor[0], buffor2, 20);
        if (y == -1)
        {
            perror("Read error");
            exit(EXIT_FAILURE);
        }
        while (y > 0) //Gdy
        {
            //Wpisuje dane z buffora2 do pliku okreslonego deskryptorem "pisz"
            if (write(pisz, buffor2, y) == -1)
            {
                perror("Write error");
                exit(EXIT_FAILURE);
            }
            //Informuje ze konsument dziala
            if (write(STDOUT_FILENO, "Konsument: ", 12) == -1)
            {
                perror("Write error");
                exit(EXIT_FAILURE);
            }
            //Informuje jakie dane sa przenoszone
            if (write(STDOUT_FILENO, buffor2, y) == -1)
            {
                perror("Write error");
                exit(EXIT_FAILURE);
            }

            //Uspienie na pseudolosowa dlugosc czasu.
            sen = (rand() % 40 + 30);
            sleep(sen / 30);

            //Wczytuje kolejna porcje danych
            y = read(deskryptor[0], buffor2, 20);
            printf("\n");
            if (y == -1)
            {
                perror("Read error");
                exit(EXIT_FAILURE);
            }
        }
        //Komunikat, po zakonczeniu dzialania
        if (y == 0)
        {
            printf("\nKoniec pliku do czytania!\n\nSprawdzenie czy programy sa identyczne:\n\n");
        }
        //Zamkniecie deskryptora.
        close(deskryptor[0]);
        if (wait(NULL) == -1)
        {
            perror("Wait error");
            exit(EXIT_FAILURE);
        }
    }
}
