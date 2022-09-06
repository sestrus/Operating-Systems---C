# Autor: Piotr Burdzy, 
### Krakow, 23.03.2021


##  Zawartosc: 

### I.
Program realizuje wzajemne wykluczanie procesów przy pomocy semaforów nazwanych.
powielacz.c - tworzy semafor oraz na końcu usuwa go, powiela procesy realizujace 
wzajemne wykluczanie. Dodatkowo tworzy plik numerek.txt i wpisuje w nim wartość "0"

#### wyklucz.c - realizuje wzajemne wykluczanie procesow, wypisuje odpowiednie komunikaty, oraz zwiększa w kazdej sekcji krytycznej liczbe w numerek.txt o 1.


### Program składa się z trzech modułów:  
1) powielacz.c
2) wyklucz.c
### Oraz biblioteki:
1) mylib.c
2) mylib.h

### Dodatkowo domyslnie do odczytu i zapisu:
numerek.txt - plik txt do odczytywania oraz wpisywania numeru


##	Komendy:
### Do uruchamiania programu:

### I program:
	make run1 ARG1=argv[1] ARG2=argv[2] ARG3=argv[3]
#### ARG1 - ilosc procesow                
#### ARG2 - ilosc sekcji krytycznych      
#### ARG3 - nazwa programu z wykluczeniami


### Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

### W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar

##
<h1 align="center">ENGLISH TRANSLATION</h1>

# Author: Piotr Burdzy, 
### Krakow, 23.03.2021


##  Content: 

### I.
The program implements the mutual exclusion of processes using named semaphores.
powielacz.c -creates a semaphore, a the end deletes it, duplicates the executing processes
mutual exclusion. 
Additionally, it creates a numerek.txt file and enters the value "0" in it

#### wyklucz.c - performs mutual process exclusion, prints appropriate messagesand increases the number by 1 in each critical section in num.txt file


### Program contains:  
1) powielacz.c
2) wyklucz.c
### And libraries:
1) mylib.c
2) mylib.h

### Additionaly, default files to read and to write
numerek.txt -  txt file to read and write increased number


##	Commands:
### Program running:

### I program:
	make run1 ARG1=argv[1] ARG2=argv[2] ARG3=argv[3]
#### ARG1 - number of processes                
#### ARG2 - number of critical sections      
#### ARG3 - name of program with exclusions


###  In order to clean the contents of the directory (remove unnecessary files):
       make clean

### In order to archive and compress the directory:
       make tar


