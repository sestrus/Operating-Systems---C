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
    sem_t *my_semaphore;

    my_semaphore = sem_open(argv[1], O_CREAT | O_EXCL, 0644, 1);

    printf("Adres semafora: %p\n\n", (void *)my_semaphore);
    // sem_close(my_semaphore);
    semafor_close(my_semaphore);
    sem_unlink(argv[1]);
}