#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

// status potomka
int status;



int main()
{


//wypisanie identyfikatorow procesu macierzystego
printf("UID = %d, GID = %d, PID = %d, PPID = %d, PGID = %d\n",getuid(),getgid(),getpid(),getppid(),getpgrp());


//trzykrotne wywolanie funkcji fork
for(int i=1; i<4; i++)
	{
	switch(fork())
		{
		//obsluga bledow
		case -1:
		perror("fork error");
		exit(1);


	case 0:
	//akcja dla procesow potomnych

		//pid_t setpgid(pid_t pid, pid_t pgrp)
		// gdzie pid = 0 oznacza ze zmieniony zostanie identyfikator PGID,
		// oraz pgrp = 0 oznacza ze ze proces zostaje liderem grupy co oznacza ze ma takis sam PID oraz PGID
		setpgid(0,0);

		//wypisanie identyfikatorow procesow potomnych.
		printf("UID = %d, GID = %d, PID = %d, PPID = %d, PGID = %d\n",getuid(),getgid(),getpid(),getppid(),getpgrp());


break;


	default:
//przedluzenie dzialania procesu macierzystego az do zakonczenia dzialania procesow potomnych
		wait(&status);
break;
}

}



return 0;
}
