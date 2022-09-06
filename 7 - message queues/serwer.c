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
#include <mqueue.h>
#define MAX_SIZE 1024
#include "lib.h"

mqd_t kolejka_serwer;
mqd_t kolejka_klient;
char bufor[50];
int serv_des;
//Wlasna obsluga dla SIGINT
void wlasna_obsluga()
{
    zamknijKomunikat(kolejka_serwer);
    odlaczKomunikat(QUEUE_NAME);
}

int main(int argc, char *argv[])
{
    char *plus;
    char *minus;
    char *mnoz;
    char *dziel;
    long int drugi;
    char nowybufor[50];
    char *podloga;
    long int wynik = 1;
    long int k;
    char name[50];
    char ukosnik[10] = "/";
    char second[10];

    //Struct do ktorego bedzie odnosi sie mq_open
    struct mq_attr attrs;
    attrs.mq_flags = 0;
    attrs.mq_maxmsg = 10;//maksymalna ilosc komunikatow w kolejce
    attrs.mq_msgsize = 50;//Maksymalnia wielkosc komunikatu
    attrs.mq_curmsgs = 0;//Aktualna ilosc komunikatow w kolejce

	//Tworze kolejke serwera o nazwie zdef. w lib.h, do odczytu.
    kolejka_serwer = otworzKomunikat(QUEUE_NAME, O_RDONLY | O_CREAT | O_EXCL, &attrs);
    printf("\nNazwa utworzonej kolejki: %s\nDeskryptor: %d\nmq_flags: %ld\nmq_maxmsg: %ld\nmq_msgsize: %ld\nmq_curmsgs: %ld\n", QUEUE_NAME, kolejka_serwer, attrs.mq_flags, attrs.mq_maxmsg, attrs.mq_msgsize, attrs.mq_curmsgs);

    while (1)
    {//Otwieram ponownie kolejke serwera
kolejka_serwer = otworzKomunikat(QUEUE_NAME,O_RDONLY | O_CREAT, &attrs);
        if (signal(2, &wlasna_obsluga) == SIG_ERR) //
        {
            perror("signal function error");
            exit(EXIT_FAILURE);
        }
        //Czekam na komunikat z kolejki o deskryptorze kolejka_serwer, zapisuje do 'bufor'. 60 - rozmiar bufora
        if (serv_des = otrzymajKomunikat(kolejka_serwer, bufor, 60, NULL) == -1)
        {
            perror("receive error");
            exit(-1);
        }
        if (serv_des == 0)
        {//Dzialanie kiedy serwer odbierze komunikat
            sleep(1);
            printf("\n\nOTRZYMAŁEM KOMUNIKAT: %s\n", bufor);

            strcpy(nowybufor, bufor);                   //Kopiuje wartosc z bufor do nowybufor
            podloga = strchr(bufor, '_');               //Rozdzielam tablice bufor wzgledem znaku '_'
            char *wyraz2 = &bufor[podloga - bufor + 1]; //Działanie
            char *pobrany_pid = strtok(bufor, "_");     //PID
            printf("DZIAŁANIE: %s\nPID PROCESU POTOMNEGO: %s\n", wyraz2, pobrany_pid);
            int pierwszy = atoi(wyraz2); //Pierwszy argument działania

            plus = strchr(nowybufor, '+'); //Działanie jeżeli realizujemy dodawanie
            while (plus != NULL)
            {
                k = plus - nowybufor + 1; //okresla miejsce gdzie znajduje sie znak działania

                strcpy(second, &nowybufor[k]);//Kopiuje do char second wartosci tablicy znakowej od parametru k
                drugi = atol(second); //drugi argument działania

                plus = strchr(plus + 1, '+'); //Dalsze przeszukiwanie char w szukaniu znaku
                wynik = drugi + pierwszy;     //wynik
                sleep(1);
                printf("WYNIK: %ld\n", wynik);
            }

            minus = strchr(nowybufor, '-'); //Działanie jeżeli realizujemy odejmowanie
            while (minus != NULL)
            {
                k = minus - nowybufor + 1;
                strcpy(second, &nowybufor[k]);
                drugi = atol(second);
                wynik = pierwszy - drugi;
                sleep(1);
                printf("WYNIK: %ld\n", wynik);
                minus = strchr(minus + 1, '-');
            }

            mnoz = strchr(nowybufor, '*'); //Działanie jeżeli realizujemy mnoz
            while (mnoz != NULL)
            {

                k = mnoz - nowybufor + 1;
                strcpy(second, &nowybufor[k]);
                drugi = atol(second);
                wynik = pierwszy * drugi;
                sleep(1);
                printf("WYNIK: %ld\n", wynik);
                mnoz = strchr(mnoz + 1, '*');
            }

            dziel = strchr(nowybufor, '/'); //Działanie jeżeli realizujemy dziel
            while (dziel != NULL)
            {
                k = dziel - nowybufor + 1;
                strcpy(second, &nowybufor[k]);
                drugi = atol(second);
                wynik = pierwszy / drugi;
                sleep(1);
                printf("WYNIK: %ld\n", wynik);
                dziel = strchr(dziel + 1, '/');
            }

            sleep(1);

            sprintf(name, "%s%s", ukosnik, pobrany_pid); //Łącze ukośnik oraz pid aby pozyskac nazwe kolejki
            char wysylamy[50];
            sprintf(wysylamy, "WYNIK: %ld", wynik); // Char zawierajacy wynik
            //Otwieram kolejke klienta
            kolejka_klient = otworzKomunikat(name, O_WRONLY, &attrs);
            if (kolejka_klient == (mqd_t)-1)
            {
                perror("kolejka 2 open error");
                exit(-3);
            }//
            wyslijKomunikat(kolejka_klient, wysylamy, 20, 30);//Wysylam komunikat do kolejki serwera
            if (atexit(wlasna_obsluga) != 0)
            {
                perror("atexit error");
                exit(-1);
            }
        }
    }
}
