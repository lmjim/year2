#include <iostream>
#include "reversi.hpp"

int main(){
	reversi::Reversi r;
	// Create board:
	r.setBoardSize(r.askBoardSize());
	reversi::Reversi::Board board = nullptr;
	board = new int **;
	r.initBoard(board);
	// Run the Game:
	r.runGame(board);
	// Do some clean up:
	r.cleanBoard(board);
	delete board;
	return 0;
}
