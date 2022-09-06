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
#include <string.h>
#include <mqueue.h>
#include "lib.h"

int main(int argc, char *argv[])
{
    char dzialanie[] = "jebac";
    char a[10];
    strcpy(a, dzialanie);
    printf("%s", a);
}