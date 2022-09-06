#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

  



int main()
{


//wypisanie identyfikatorow procesow macierzystych  oraz uspienie go na 2 sekundy, aby umozliwic sprawdzenie
//przez komende "pstree -p" gdzie sie znajduje w drzewie procesow
printf("M: UID = %d, GID = %d, PID = %d, PPID = %d, PGID = %d\n",getuid(),getgid(),getpid(),getppid(),getpgrp());
sleep(2);


for(int i=1; i<4; i++)
	{
	switch(fork())
		{
		//obsluga bledow
		case -1:
		perror("fork error");
		exit(1);

		case 0:
//akcja dla procesow potomnych - tutaj uspienie na 3 sekundy, aby:
//1. proces potomny zaczal sie po skonczeniu dzialania procesu pierwotnego
//2. umozliwic sprawdzenie czy procesy zostaly adoptowane przez proces init.
//oraz wypisanie identyfikatorow procesow potomnych.
sleep(3);
printf("P: UID = %d, GID = %d, PID = %d, PPID = %d, PGID = %d\n",getuid(),getgid(),getpid(),getppid(),getpgrp());
		
break;


	default:
//akcja  dla procesu macierzystego - tutaj: brak akcji poniewaz, chce aby proces macierzysty sie zakonczyl celem
//adoptowania procesow potomnych przez proces init.
		break;
}

}


return 0;
}
