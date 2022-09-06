
# Autor: Piotr Burdzy,   
### Krakow, 21.04.2021


## Zawartosc: 

### Program I
Program do obslugi sygnalow z mozliwosciami: 
1) Wykonania operacji domyslnej
2) Ignorowania sygnalu
3) Przechwycenia i wlasnej obslugi sygnalu.
Program ma otrzymywac sygnaly przy pomocy polecenia kill z powloki lub
za pomoca sekwencji klawiszy.


### Sklada sie z jednego pliku:
1) 3a.c



### Program II
Program uruchamia program obslugujacy sygnaly, w procesie potomnym za pomoca funkcji exec,
sygnaly wyslane sa za pomoca funkcji kill z procesu macierzystego.


### Sklada sie z dwoch plikow:
1) 3ba.c
2) 3bb.c


### Program III
Program tworzy proces potomny i sprawia ze staje sie liderem nowej grupy procesow, nastepnie 
uruchamiane sa w nim procesy potomne wykonujace obsluge sygnalow. Z pierwszego procesu macierzystego
wysylany jest sygnal do calej grupy procesow potomnych (po sprawdzeniu ich istnienia). 
Lider grupy procesow ignoruje sygnalow i na koncu czeka na zakonczenie wszystkich procesow potomnych.


### Sklada sie z trzech plikow:
1) 3ca.c
2) 3cb.c
3) 3cc.c



## Komendy:

### ARG1 - ID SYGNALU,								  
### ARG2 - SPOSOB OBSLUGI SYGNALU,
### 'a' - obsluga domyslna,						  
### 'b' - ignorowanie sygnalu,						  
### 'c' - przechwycenie i obsluga wlasna sygnalu.	  

##
### Uruchamianie programu I:
	make run1 ARG1=argv[1] ARG2=argv[2]

### Uruchamianie programu II:
	make run2 ARG1=argv[1] ARG2=argv[2]

### Uruchamianie programu III:
	make run3 ARG1=argv[1] ARG2=argv[2]

### Czyszczenie katalogu:
       make clean

### Archiwizacja oraz kompresja katalogu:
       make tar
##
<h1 align="center">ENGLISH TRANSLATION</h1>


# Author: Piotr Burdzy,   
### Krakow, 21.04.2021


## Content: 

### Program I
Program for handling signals with capabilities: 
1) Perform the default operation
2) Ignore the signal
3) Signal interception and custom handling.
The program is to receive signals using a command kill from the shell or
with a key sequence

### Contains:
1) 3a.c



### Program II
The program starts the signal handler. in a child process, using the exec function,
signals are sent using the kill function from the parent process.


### Contains:
1) 3ba.c
2) 3bb.c


### Program III
The program creates a child process and makes it the leader of the new process group, then
it runs child processes that handle signals. From the first parent process
it sends a signal to the entire group of child processes (after checking their existence).
The process group leader ignores signals and finally waits for all child processes to finish.


### Contains:
1) 3ca.c
2) 3cb.c
3) 3cc.c



## Commands:

### ARG1 - SIGNAL ID,								  
### ARG2 - SIGNAL HANDLER MODE,

### HANDLE MODES:
### 'a' - Default handle,						  
### 'b' - Signal ignoring,						  
### 'c' - Signal interception and own signal handling.	  

##
### Running programu I:
	make run1 ARG1=argv[1] ARG2=argv[2]

### Running programu II:
	make run2 ARG1=argv[1] ARG2=argv[2]

### Running programu III:
	make run3 ARG1=argv[1] ARG2=argv[2]

### In order to clean the contents of the directory (remove unnecessary files):
       make clean

### In order to archive and compress the directory:
       make tar











