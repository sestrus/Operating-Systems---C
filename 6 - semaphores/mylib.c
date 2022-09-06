
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

//Funkcja zamykajaca semafor
void zamknijSemafor(sem_t *sem)
{

    if (sem_close(sem) == -1)
    {
        perror("sem_close error");
        exit(5);
    }
}

//Funkcja pozyskujaca wartosc semafora
void pozyskajWartosc(sem_t *sem, int *sval)
{
    if (sem_getvalue(sem, sval) == -1)
    {
        perror("sem_getvalue error");
        _exit(5);
    }
}

//Funkcja podnoszaca semafor
int podniesSemafor(sem_t *sem)
{
    if (sem_post(sem) == -1)
    {
        perror("sem_post error");
        _exit(5);
    }
}

//Funkcja opuszczajaca semafor
int opuscSemafor(sem_t *sem)
{
    if (sem_wait(sem) == -1)
    {
        perror("sem_post error");
        exit(5);
    }
}

//Funkcja odlaczajaca semafor
int odlaczSemafor(const char *name)
{
    if (sem_unlink(name) == -1)
    {
        perror("sem_post error");
        exit(5);
    }
}

//Funkcja tworzaca semafor i otwierajaca go
sem_t *stworzSemafor(const char *name)
{
    if (sem_open(name, O_CREAT | O_EXCL, 0644, 1) == SEM_FAILED)
    {
        perror("sem_open stworz error");
        exit(5);
    }
}

//Funkcja otwierajaca semafor
sem_t *otworzSemafor(const char *name)
{
    if (sem_open(name, O_CREAT, 0644, 1) == SEM_FAILED)
    {
        perror("sem_open otworz error");
        _exit(5);
    }
}