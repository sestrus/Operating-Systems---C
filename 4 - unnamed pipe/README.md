# Autor: Piotr Burdzy,                                     
### Krakow, 23.03.2021


## Zawartosc: 

### I.
Problem ,,Producenta i konsumenta" zaimplementowany przy pomocy potoków nienazwanych. Producent pobiera 
surowiec z pliku tekstowego i wstawia go jako towar do potoku, natomiast Konsument umieszcza pobrany 
z potoku towar w innym pliku tekstowym.


### Program składa się z jednego modułu: 
1) zad.c

### Dodatkowo domyslnie do odczytu i zapisu
#### surowiec.txt - od odczytu
#### wyn.txt - do zapisu





## Komendy:
Do uruchamiania programu:

### I program:
	make run1 ARG1=argv[1] ARG2=argv[2]
  
  
#### ARG1 - plik do odczytu 
#### ARG2 - plik do zapisu  


### -> Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

### -> W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar

<h3 align="center">ENGLISH TRANSLATION</h3>

# Author: Piotr Burdzy,                                     
### Krakow, 23.03.2021


## Content: 

### I.
"Producer and consumer" implemented with unnamed pipes. Producer gets source data from 
text file and inserts it as a commodity into the pipe, whereas Consumer inserts data from
pipe to another text file


### Contains: 
1) zad.c

### Additionaly, default files to read and to write
#### surowiec.txt - to read
#### wyn.txt - to write





## Commands:
Program running:

### I program:
	make run1 ARG1=argv[1] ARG2=argv[2]
  
  
#### ARG1 - file to read 
#### ARG2 - file to write  


### -> In order to clean the contents of the directory (remove unnecessary files):
       make clean

### -> In order to archive and compress the directory:
       make tar





