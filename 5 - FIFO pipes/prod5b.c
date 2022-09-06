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
char *potok;
int main(int argc, char *argv[])
{
    //rezerwuje pamiec na buffor
    char *buffor1;
    buffor1 = malloc(50);

    //Tworze deskryptory oraz otwieram plik do pisania oraz
    int czytaj = open(argv[2], O_RDONLY, 0644);
    int pisz = open(argv[1], O_WRONLY, 0644);
    if (czytaj == -1)
    {
        perror("czytaj error");
        exit(EXIT_FAILURE);
    }

    if (pisz == -1)
    {
        perror("pisz error");
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
        if (write(pisz, buffor1, x) == -1)
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
        sleep(sen / 20);
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
    if (close(pisz) == -1)
    {
        perror("close error");
        exit(EXIT_FAILURE);
    }

    if (close(czytaj) == -1)
    {
        perror("close error");
        exit(EXIT_FAILURE);
    }
}
