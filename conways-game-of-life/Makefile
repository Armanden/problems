CFLAGS  = $(shell pkg-config --cflags raylib) -O2
LIBS    = $(shell pkg-config --libs   raylib)

all: game

game: main.c
	gcc $(CFLAGS) -o game main.c $(LIBS)

clean:
	rm -f game

run: game
	./game
