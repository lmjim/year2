# very basic Makefile to compile and remove reversi

reversiAndOthello: reversi.h reversi.c othello.h othello.c placement.h placement.c flip.h flip.c main.c othelloMain.c
	gcc -g -std=c11 -o reversi reversi.c placement.c flip.c main.c
	gcc -g -std=c11 -o othello othello.c placement.c flip.c othelloMain.c

reversi: reversi.h reversi.c placement.h placement.c flip.h flip.c main.c
	gcc -g -std=c11 -o reversi reversi.c placement.c flip.c main.c

othello: othello.h othello.c placement.h placement.c flip.h flip.c othelloMain.c
	gcc -g -std=c11 -o othello othello.c placement.c flip.c othelloMain.c

clean:
	rm reversi
	rm othello
