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

int main()
{
    struct mq_attr attrs;
    attrs.mq_flags = 0;
    attrs.mq_maxmsg = 10;
    attrs.mq_msgsize = 50;
    attrs.mq_curmsgs = 0;
    printf("%ld", attrs.mq_maxmsg);
}
