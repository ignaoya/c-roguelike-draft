CC = gcc
CFLAGS = -lncurses -I$(IDIR) -lm -g

IDIR = ./include/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c

all: abyss run clean

abyss: 
	$(CC) $(SOURCES) $(CFLAGS) -o abyss

run:
	./abyss

clean:
	rm abyss
