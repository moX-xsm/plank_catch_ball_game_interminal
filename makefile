all:
	gcc game.c function.c -o game -lcurses
	./game
