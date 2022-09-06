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
#include <errno.h>
#include <mqueue.h>
#define MAX_SIZE 1024
#include "lib.h"
mqd_t kolejka_serwera;
mqd_t kolejka2;
char nazwa[50];
void wyjscie()
{
    zamknijKomunikat(kolejka2);
    odlaczKomunikat(nazwa);
//    zamknijKomunikat(kolejka_serwera);
}
int main(int argc, char *argv[])
{
    char fgetsbuffor[100];
    char ukosnik[10] = "/";
    char dzialanie[30];
    char send_pid[30];
    int pid = getpid();
    char wyslij[50];
    char buff[50];
    //tworzenie nazwy kolejki komunikatow
    sprintf(nazwa, "%s%d", ukosnik, pid);

    //Struktura z parametrami otwarcia kolejki
    struct mq_attr attrs;
    attrs.mq_flags = 0;
    attrs.mq_maxmsg = 10;//Max ilosc komunikatow w kolejce
    attrs.mq_msgsize = 50;//Max wielkosc komunikatu
    attrs.mq_curmsgs = 0;//Aktualna ilosc komunikatow w kolejce
sleep(1);
    kolejka2 = otworzKomunikat(nazwa, O_RDONLY | O_CREAT | O_EXCL, &attrs);//Tworze kolejke klienta do czytania
    kolejka_serwera = otworzKomunikat(QUEUE_NAME, O_WRONLY,&attrs);//Otwieram kolejke serwera do pisania
    printf("\nNazwa Utworzonej kolejki: %s\nDeskryptor: %d\nmq_flags: %ld\nmq_maxmsg: %ld\nmq_msgsize: %ld\nmq_curmsgs: %ld", nazwa, kolejka2, attrs.mq_flags, attrs.mq_maxmsg, attrs.mq_msgsize, attrs.mq_curmsgs);
    printf("\nPID PROCESU: %d\nPODAJ DZIAŁANIE KTÓRE CHCESZ WYKONAĆ: ", getpid());



    //Wczytanie komunikatu do wysłania
    for (int i = 0; i < 10; i++)
    {

        fgets(dzialanie, 10, stdin);//Wczytuje dzialanie do obliczenia

        if (feof(stdin))//Jezeli wartosc wczytana==EOF to wyjdz z petli
        {
            break;
        }
    }
    //Tworzenie komunikatu do wyslania PID_DZIAŁANIE
    sprintf(wyslij, "%d_%s", pid, dzialanie);
    printf("WYSYŁAM KOMUNIKAT: %s\n", wyslij);
    wyslijKomunikat(kolejka_serwera, wyslij, 20, pid);//Wysylam komunikat PID_DZIALANIE do kolejki serwera
    sleep(2);
    otrzymajKomunikat(kolejka2, buff, 60, NULL);//Odbieram komunikat z kolejki klienta
    printf("%s\n", buff);
    if (atexit(wyjscie) != 0)
    {
        perror("atexit error");
        exit(-1);
    }

}
