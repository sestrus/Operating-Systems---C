

#Aby uzywac rozszerzen w nazwach plikow, nieznajdujacych sie na liscie parametrow wewnetrznych make.

.SUFFIXES: .c .o .x .h

#---------------------------------------------------------------------------------------------------
#Sluzy do wybierania wlasciwej nazwy katalogu lub pliku.

DIR = `basename $(CURDIR)`

#---------------------------------------------------------------------------------------------------
#Rdzenie nazw plikow ktorych bedzie uzywac Makefile.

NAME1 = 1b
NAME2 = zadanie2


#---------------------------------------------------------------------------------------------------
#Program wykonawczyy wykonawcze gdzie dodaje rozszerzenie .x, oraz Pliki powstale po kompilacji
#pikow zrodlowych (.o)

EXEC1 = $(NAME1).x
OBJS1 = $(NAME1).o

EXEC2 = $(NAME2).x
OBJS2 = $(NAME2).o


#---------------------------------------------------------------------------------------------------
#Dolaczane biblioteki do poszczegolnych plikow oraz pliki naglowkowe.

LIBS1 = 
HEADS1 = 

LIBS2 = 
HEADS2 = 



#---------------------------------------------------------------------------------------------------
#Opcje kompilatora i linkera
CFLAGS = -Wall -std=c99 -pedantic -O fPIC
LFLAGS = -Wall -std=c99 -pedantic -O


#Biblioteki linkera zainstalowane w systemie
LDLIBS = -lm


#Kompilator oraz linker.
CO = gcc
LD = $(CO)


#Archiwizer do tworzenia bibliotek statycznych
AR =ar

#opcje archiwizera: tworzenie/uaktualnianie biblioteki wraz z indeksem plikow oraz wypisywanie komunikatow
ARFLAGS = rsv


#---------------------------------------------------------------------------------------------------
#Reguła wzorcowa- sposob otrzymywania plikow .o z plikow .c
%.o: %.c
	$(CO)$(CLAGS) -c $<

#---------------------------------------------------------------------------------------------------
#Regula zaleznosci, uaktualnianie plikow po prawej stronie dwukropka.
.PHONY: all
all: $(EXEC1) $(EXEC2)  


#---------------------------------------------------------------------------------------------------
#Jawna regula zaleznosci:
#1. Uaktualnia pliki po prawej stronie dwukropka,
#2. Wykonaj linkowanie.

$(EXEC1): $(OBJS1) $(LIBS1)
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC2): $(OBJS2) $(LIBS2)
	$(LD) -o $@ $(LFLAGS) $^

#---------------------------------------------------------------------------------------------------
#Uruchamianie programów EXEC1 i EXEC2.


.PHONY: run
run: $(EXEC1) $(EXEC2)
	./$(EXEC2)

#---------------------------------------------------------------------------------------------------
#Usuwa pliki z rozszerzeniami podanymi w poleceniu.

.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )





