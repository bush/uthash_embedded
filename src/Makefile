IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=

_DEPS = uthash_embedded.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = uthash_embedded.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
		$(CC) -c -o $@ -Wall $< $(CFLAGS)

all: example1 example2

example1: example.o $(OBJ)
		gcc -o $@ $^ $(CFLAGS) $(LIBS)

example2: example1.o $(OBJ)
		gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
		rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
