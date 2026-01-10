CC = gcc
CFLAGS = -o -Wall
ARGS = test_image.jpeg

.PHONY: clean run

magick_commande: magick_commande.c
	gcc -Wall magick_commande.c -o magick_commande

run:
	./magick_commande $(ARGS)
	
clean:
	rm -f magick_commande
