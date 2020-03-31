#include <stdio.h>
#include <stdlib.h>
#include "reversi.h"

int main(){
	// Create board:
	setBoardSize(askBoardSize());
	Board board = NULL;
	board = (Board) malloc (sizeof(Board));
	initBoard(board);
	// Run the Game:
	runGame(board);
	// Do some clean up:
	cleanBoard(board);
	free(board);
	return 0;
}
