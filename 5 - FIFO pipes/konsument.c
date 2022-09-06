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
//Funkcja dla atexit
void unlinking(void)
{
    unlink(potok);
}

int main(int argc, char *argv[])
{ //Dzialanie dla procesu macierzystego
    potok = argv[1];

    //Zarezerwowanie pamieci na bufor
    char *buffor2;
    buffor2 = malloc(50);

    //Uspienie, oraz inicjacja liczb pseudolosowych do uzycia w pozniejszym uspieniu.
    sleep(1);
    srand(time(NULL));
    int sen;

    //Otworzenie pliku do pisania, oraz potoku i utworzenie deskryptorow
    int czytaj = open(argv[1], O_RDONLY, 0644);
    int pisz = open(argv[3], O_WRONLY, 0644);
    if (pisz == -1)
    {
        perror("czytaj error");
        exit(EXIT_FAILURE);
    }
    if (czytaj == -1)
    {
        perror("czytaj error");
        exit(EXIT_FAILURE);
    }

    //Odczytuje z deskryptora dane i umieszcza w bufforze.
    int y;
    y = read(czytaj, buffor2, 20);
    if (y == -1)
    {
        perror("Read error");
        exit(EXIT_FAILURE);
    }

    while (y > 0) //Gdy plik sie nie zakonczyl
    {
        //Wpisuje dane z buffora2 do potoku okreslonego deskryptorem "pisz"
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
        sleep(sen / 25);

        //Wczytuje kolejna porcje danych
        y = read(czytaj, buffor2, 20);
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
    //Zwolnienie deskryptora.
    close(czytaj);
    if (wait(NULL) == -1)
    {
        perror("Wait error");
        exit(EXIT_FAILURE);
    }

    if (atexit(unlinking) != 0)
    {
        perror("atexit error");
        exit(EXIT_FAILURE);
    }
}