CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99

# =======================
# Executables
# =======================

EXEC_MORPH   = morphing
EXEC_SELECT  = select_points

# =======================
# Objets
# =======================

OBJ_COMMON = lire_ecrire.o

OBJ_SELECT = select_points.o interface.o afficher.o $(OBJ_COMMON)

OBJ_MORPH  = morphing.o \
             couples.o geom.o triangulation.o morphing_core.o \
             $(OBJ_COMMON)

# =======================
# Headers
# =======================

HEADERS = morphing_type.h \
          lire_ecrire.h \
          afficher.h \
          interface.h \
          couples.h \
          geom.h \
          triangulation.h \
          morphing_core.h

# =======================
# Librairies graphiques (seulement pour select_points)
# =======================

GRAPH_LIBS = -luvsqgraphics_2 -lSDL2 -lSDL2_ttf -lm

# =======================
# Règles principales
# =======================

all: $(EXEC_SELECT) $(EXEC_MORPH)

# -------- select_points --------
$(EXEC_SELECT): $(OBJ_SELECT)
	$(CC) $(CFLAGS) -o $@ $^ $(GRAPH_LIBS)

# -------- morphing --------
$(EXEC_MORPH): $(OBJ_MORPH)
	$(CC) $(CFLAGS) -o $@ $^

# =======================
# Compilation des .o
# =======================

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

# =======================
# Nettoyage
# =======================

clean:
	rm -f *.o $(EXEC_SELECT) $(EXEC_MORPH)

# =======================
# Archive à rendre
# =======================

zip:
	zip -r IN304_TONNOM.zip *.c *.h Makefile
