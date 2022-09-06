#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>


//Program tworzy procesy potomne i wypisuje identyfikatory procesu
//macierzystego oraz za pomoca funkcji exec procesow potomnych
//funkcja exec zostaje wywolana 3 razy.



int main() {
//wypisuje identyfikatory procesu macierzystego.

  printf("\n\nProces Macierzysty:\n");
  printf("UID = %d, GID = %d, PID = %d, PPID = %d, PGID = %d\n", getuid(), getgid(), getpid(), getppid(), getpgrp());


  printf("Procesy Potomne:\n");


  for (int i = 1; i < 4; i++) {
    switch (fork()) {


//obsluga bledow funkcji fork.
    case -1:
      perror("fork error");
      exit(1);


    case 0:
//akcja dla potomka - tutaj: wypisanie identyfikatorow
//potomkow za pomoca funkcji exec.
      execl("./1b.x", "1b.x", NULL);
      perror("execl error");

      _exit(2);



    default:

//kontrola bledow funkcji wait.
      if (wait(NULL) == -1) {
        perror("wait error");
        _exit(0);
      }
      wait(NULL);
    }

  }

  return 0;
}
