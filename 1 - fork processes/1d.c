#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>












int main()
{
//zmienna okreslajaca pokolenie procesu
int potomek = 0;


//wypisanie identyfikatorow  procesu macierzystego.
printf("      Macierzysty: %d  UID = %d, GID = %d, PID = %d, PPID = %d, PGID = %d\n",potomek, getuid(),getgid(),
getpid(),getppid(),getpgrp());


for(int i=1; i<4; i++)
	{
	switch(fork())
		{
		case -1:
		perror("fork error");
		exit(1);

		case 0:
		//akcja dla procesow potomkow

		//iteracja zmiennej potomek
		potomek++;

//wypisywanie identyfikatorow procesow potomnych.
printf("Pokolenie potomka: %d, UID = %d, GID = %d, PID = %d, PPID = %d, PGID = %d\n",potomek, getuid(),getgid(),
getpid(),getppid(),getpgrp());
// sleep sluzacy spowolnieniu wypisywania, aby pokolenia wyswietlaly sie rownoczesnie.
	sleep(1);
	break;




	default://akcja dla procesu macierzystego. Zakonczy sie przed zakonczeniem procesow potomnych
		//jednak nie potrafilem tego zrobic w pelni poprawnie.
		break;
}

}
//ten sleep jest tu po to aby nazwa uzytkownika(itd.) wyswietlala sie  po zakonczeniu wypisywania potomkow.
sleep(4);

return 0;
}
