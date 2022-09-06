
# Autor: Piotr Burdzy,                                                                     Krakow, 23.03.2021



## Zawartość: 

## I. 
Program wypisujący identyfikatory UID, GID, PID, PPID, PGID dla danego procesu.

### Program składa się z jednego modułu: 
1) 1a.c



## II. 
Program wypisuje identyfikatory UID, GID, PID, PPID, PGID dla procesów: macierzystego oraz wszystkich
procesów potomnych dla wywołanej trzykrotnie funkcji fork. Dodatkowo proces macierzysty czeka na zakończenie 
procesów potomnych za pomocą funkcji wait.

### Program składa się z jednego modułu: 
1) 1b.c

## III.
Program wypisuje identyfikatory UID, GID, PID, PPID, PGID dla procesów: macierzystego oraz wszystkich
procesów potomnych dla wywołanej trzykrotnie funkcji fork, gdzie proces macierzysty czeka na zakończenie
procesów potomnych przy użyciu funkcji sleep. Dodatkowo procesy potomne są adaptowane przez proces init.

### Program składa się z jednego modułu: 
1) 1c.c

## IV. 
Program wypisuje identyfikatory UID, GID, PID, PPID, PGID dla procesów: macierzystego oraz wszystkich
procesów potomnych dla wywołanej trzykrotnie funkcji fork. Dodatkowo procesy pojawiają się pokoleniami od
najstarszego do najmłodszego, a proces macierzysty powinien kończyć się po procesach potomnych.


### Program składa się z jednego modułu: 
1) 1d.c


## V.
Program wypisuje identyfikatory UID, GID, PID, PPID, PGID dla procesów: macierzystego oraz wszystkich
procesów potomnych dla wywołanej trzykrotnie funkcji fork. Dodatkowo za pomocą funkcji setpgid każdy proces 
potomny staje się liderem swojej własnej grupy procesów.



### Program składa się z jednego modułu: 
1) 1e.c



## Komendy:

### Do uruchamiania programów:

### Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

### W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar
### I program:
	make run1
### II program:
	make run2
### III program:
	make run3
### IV program:
	make run4
### V program:
	make run5


<h1 align="center">
ENGLISH TRANSLATION
</h1>

# Author: Piotr Burdzy,                                                                     Krakow, 23.03.2021


## Content:

## I.
Program that prints out identifiers UID, GID, PID, PPID, PGID for a given process

### The program consists of one module:
1) 1a.c



## II. 
Program that prints out identifiers UID, GID, PID, PPID, PGID for processes: mother and all child
processes for the fork function called three times. Additionally, the parent process waits for child processes
to terminate using the wait function.

### The program consists of one module:
1) 1b.c



## III.
Program that prints out identifiers UID, GID, PID, PPID, PGID for processes: mother and all child
processes for the fork function called three times, but mother process is waiting for completion
child processesusing the sleep function. Additionally child processes are adapted by init process.

### The program consists of one module:
1) 1c.c



## IV. 
Program that prints out identifiers UID, GID, PID, PPID, PGID for processes: mother and all child
processes for the fork function called three times. Additionally processes appear 'generations' from
the oldest to the youngest, and mother process waits for every child process termination.


### The program consists of one module:
1) 1d.c



## V.
Program that prints out identifiers UID, GID, PID, PPID, PGID for processes: mother and all child
processes for the fork function called three times. Additionally, using setpgid function every child process
becomes a leader of its own process group. 

### The program consists of one module:
1) 1e.c



## Commands:

### Running programs:

### In order to clean the contents of the directory (remove unnecessary files):
       make clean

### In order to archive and compress the directory:
       make tar
### I program:
	make run1
### II program:
	make run2
### III program:
	make run3
### IV program:
	make run4
### V program:
	make run5



























