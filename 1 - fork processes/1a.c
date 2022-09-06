#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>



int main()
{
	switch(fork())
	{

	case -1:
	//Obsluga bledow.
	perror ("fork error");
	exit(1);


	case 0:
	//Akcja dla procesu potomnego.
	break;


	default:
	//Akcja dla procesu macierzystego - tutaj wypisanie procesu macierzystego. 
	printf("UID = %d, GID = %d, PID = %d, PPID = %d, PGID = %d\n",getuid(),getgid(),getpid(),getppid(),getpgrp());
break;
	}
return 0;
}
