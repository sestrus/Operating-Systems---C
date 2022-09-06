
#include <sys/types.h>
#include <unistd.h> 
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>




int main()
{


//wypisanie identyfikatorow procesu macierzystego
printf("UID = %d, GID = %d, PID = %d, PPID = %d, PGID = %d\n",getuid(),getgid(),getpid(),getppid(),getpgrp());


//potrojne wywolanie funkcji fork
for(int i=1; i<4; i++)
	{
	switch(fork())
		{
		//obsluga bledow.
		case -1:
		perror("fork error");
		exit(1);

		case 0:
		//akcja dla potomka - tutaj: wypisanie identyfikatorow potomka.
		printf("UID = %d, GID = %d, PID = %d, PPID = %d, PGID = %d\n",getuid(),getgid(),getpid(),getppid(),getpgrp());
		


	default:
wait(NULL);

	//akcja dla procesu macierzystego - tutaj: oczekuje na zakonczenie procesow potomnych.
//	wait(&status);

}

}



return 0;
}
