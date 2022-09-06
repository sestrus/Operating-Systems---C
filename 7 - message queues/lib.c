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
#include "lib.h"

int zamknijKomunikat(mqd_t des)
{
    if (mq_close(des) == -1)
    {
        perror("close error");
        exit(-1);
    }
}

int odlaczKomunikat(const char *name)
{
    if (mq_unlink(name) == -1)
    {
        perror("unlink error");
        exit(-1);
    }
}
mqd_t otworzKomunikat(const char *name, int oflag, struct mq_attr *attrs)
{
    if (mq_open(name, oflag, 0644, attrs) == -1)
    {
        perror("open error");
        exit(-1);
    }
}

int otrzymajKomunikat(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio)
{
    if (mq_receive(mqdes, msg_ptr, msg_len, msg_prio) == -1)
    {
        perror("receive error");
        exit(-1);
    }
}

int wyslijKomunikat(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio)
{
    if (mq_send(mqdes, msg_ptr, msg_len, msg_prio) == -1)
    {
        perror("send error");
        exit(-1);
    }
}
