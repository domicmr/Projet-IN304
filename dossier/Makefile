CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99

# Sélection couples (projet étape 3)
EXEC1   = morphing
OBJ1    = morphing.o lire_ecrire.o afficher.o interface.o

# Debug interpolation (TD6.1)
EXEC2   = interp
OBJ2    = interp_main.o interpolation.o

HEADERS = morphing_type.h lire_ecrire.h afficher.h interface.h interpolation.h
SRC     = morphing.c lire_ecrire.c afficher.c interface.c interpolation.c interp_main.c

ZIPNAME = IN304_TONNOM.zip

LDFLAGS = -luvsqgraphics_2 -lSDL2 -lSDL2_ttf -lm

all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJ1)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(EXEC2): $(OBJ2)
	$(CC) $(CFLAGS) -o $@ $^

morphing.o: morphing.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

lire_ecrire.o: lire_ecrire.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

afficher.o: afficher.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

interface.o: interface.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

interp_main.o: interp_main.c interpolation.h
	$(CC) $(CFLAGS) -c $<

interpolation.o: interpolation.c interpolation.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ1) $(OBJ2) $(EXEC1) $(EXEC2)

zip:
	zip -r $(ZIPNAME) $(SRC) $(HEADERS) Makefile
