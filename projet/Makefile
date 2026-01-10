CC = gcc
CFLAGS = -O2 -Wall `sdl2-config --cflags`
LDLIBS=`sdl2-config --libs` -lm -lSDL2_ttf

SOURCE = main.c
OBJ = $(SOURCE:.c=.o) lecture_fichier_ppm.o uvsqgraphics_2.o gui.o liste_chainee.o calculs.o
BINARY = main

#Variable FICHIER pas utilisée (pour l'instant)
FICHIER =./input_pic/chat_chien_2.ppm
#---------------------------------------------------------------------------------------------------------------------------
.PHONY: clean run

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
liste_chainee: liste_chainee.o
	$(CC) $(CFLAGS) $< -o $@
	
gui: gui.o uvsqgraphics_2.o lecture_fichier_ppm.o liste_chainee.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)
	
lecture_fichier_ppm: lecture_fichier_ppm.o uvsqgraphics_2.o
	$(CC) $(CFLAGS) -o $^ $(LDLIBS)

$(BINARY): $(OBJ)
	$(CC) $(CFLAGS) -o $(BINARY) $(OBJ) $(LDLIBS)

run: $(BINARY)
	./$(BINARY)
	
clean:
	rm -f $(BINARY)
	rm -f *.o
