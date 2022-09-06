

#Aby uzywac rozszerzen w nazwach plikow, nieznajdujacych sie na liscie parametrow wewnetrznych make.

.SUFFIXES: .c .o .x .h

#---------------------------------------------------------------------------------------------------
#Sluzy do wybierania wlasciwej nazwy katalogu lub pliku.

DIR = `basename $(CURDIR)`

#---------------------------------------------------------------------------------------------------
#Rdzenie nazw plikow ktorych bedzie uzywac Makefile.

NAME1 = powielacz
NAME2 = wyklucz
LIB1 = mylib


#---------------------------------------------------------------------------------------------------
#Program wykonawczyy wykonawcze gdzie dodaje rozszerzenie .x, oraz Pliki powstale po kompilacji
#pikow zrodlowych (.o)

EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x

OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o

LIBS1 = $(LIB1).c





#---------------------------------------------------------------------------------------------------
#Dolaczane biblioteki do poszczegolnych plikow oraz pliki naglowkowe.









#---------------------------------------------------------------------------------------------------
#Opcje kompilatora i linkera
CFLAGS = -pthread -Wall -std=c99 -pedantic -O
LFLAGS = -pthread -Wall -std=c99 -pedantic -O


#Biblioteki linkera zainstalowane w systemie
LDLIBS = -lm


#Kompilator oraz linker.
CO = gcc
LD = $(CO)


#Archiwizer do tworzenia bibliotek statycznych
AR =ar

#opcje archiwizera: tworzenie/uaktualnianie biblioteki wraz z indeksem plikow oraz wypisywanie komunikatow
ARFLAGS = rsv


#Argumenty wywolania procesow
#---------------------------------------------------------------------------------------------------
ARG1 =
ARG2 =
ARG3 = 
ARG4 = 
#---------------------------------------------------------------------------------------------------
#Reguła wzorcowa- sposob otrzymywania plikow .o z plikow .c
%.o: %.c
	$(CO)$(CLAGS) -c $<

#---------------------------------------------------------------------------------------------------
#Regula zaleznosci, uaktualnianie plikow po prawej stronie dwukropka.


#---------------------------------------------------------------------------------------------------
#Jawna regula zaleznosci:
#1. Uaktualnia pliki po prawej stronie dwukropka,
#2. Wykonaj linkowanie.
.PHONY: all
all: $(EXEC1)


$(EXEC1): $(OBJS1) $(LIBS1)
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC2): $(OBJS2) $(LIBS1)
	$(LD) -o $@ $(LFLAGS) $^


#---------------------------------------------------------------------------------------------------
#Uruchamianie programów EXEC1-EXEC6, najpierw sprawdza czy kod wykonawczy jest aktualny


.PHONY: run1
run1: $(EXEC1) $(EXEC2)
	clear
	./$(EXEC1) $(ARG1) $(ARG2) $(ARG3) 



#---------------------------------------------------------------------------------------------------
#Usuwa pliki z rozszerzeniami podanymi w poleceniu.

.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )





