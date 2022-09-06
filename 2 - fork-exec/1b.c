#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>




//program ktory bedzie wywolywany przez funkcje exec.
int main() {
 
  //wypisanie identyfikatorow dla procesow potomnych.
  printf("UID = %d, GID = %d, PID = %d, PPID = %d, PGID = %d\n", getuid(), getgid(), getpid(),
    getppid(), getpgrp());

  return 0;
}