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

//Tworzy potok fifo z poziomu programu i uruchamia procesy producenta i konsumenta.

int main(int argc, char *argv[])
{

    //Tworzy potok nazwany
    if (mkfifo(argv[1], 0644) == -1)
    {
        perror("mkfifo error");
        _exit(1);
    }
    //Tworzy proces potomny
    int pid = fork();

    if (pid == -1)
    { //obsluga bledow fork
        perror("fork error");
        _exit(EXIT_FAILURE);
    }

    if (pid == 0)
    { //Dzialanie dla procesu potomnego
        //Uruchamia proces producenta
        if (execl("./producent.x", "producent.x", argv[1], argv[2], argv[3], (char *)NULL) == -1)
        {
            perror("execl producent error");
            _exit(EXIT_FAILURE);
        }
    }

    if (pid != -1 && pid != 0)
    { //Dzialanie dla procesu macierzystego
        //Uruchamia proces konsumenta
        if (execl("./konsument.x", "konsument.x", argv[1], argv[2], argv[3], (char *)NULL) == -1)
        {
            perror("execl konsument error");
            _exit(EXIT_FAILURE);
        }
    }

    return 0;
}
