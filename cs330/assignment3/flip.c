#include <stdio.h>
#include "reversi.h"
#include "placement.h"
#include "flip.h"

// Global Variable
static int boardSize = 0;

int flipBoardSize(int size){
	boardSize = size; // Set global variable for size of board
}

void toLeftFlip(Board board, int player, int oppenent, int x, int y){
		// Opponent to the left
                int j = y-1;
                while(j >= 0){
                        if((*board)[x][j] == player){
                                break;
                        }
			if((*board)[x][j] == None){
                                break;
                        }
			(*board)[x][j] = player;
                        j--;
                }
}

void toRightFlip(Board board, int player, int oppenent, int x, int y){
		// Opponent to the right
                int j = y+1;
                while(j < boardSize){
                        if((*board)[x][j] == player){
                                break;
                        }
                        if((*board)[x][j] == None){
                                break;
                        }
			(*board)[x][j] = player;
                        j++;
                }
}

void upLeftFlip(Board board, int player, int oppenent, int x, int y){
		// Opponent up and to the left
		int i = x-1;
                int j = y-1;
                while(i >= 0 && j >= 0){
                        if((*board)[i][j] == player){
                                break;
                        }
                        if((*board)[i][j] == None){
                                break;
                        }
			(*board)[i][j] = player;
                        i--;
                        j--;
                }
}

void upwardsFlip(Board board, int player, int oppenent, int x, int y){
		// Opponent upwards
		int i = x-1;
		while(i >= 0){
			if((*board)[i][y] == player){
				break;
			}
			if((*board)[i][y] == None){
				break;
			}
			(*board)[i][y] = player;
			i--;
		}
}

void upRightFlip(Board board, int player, int oppenent, int x, int y){
		// Opponent up and to the right
		int i = x-1;
		int j = y+1;
		while(i >= 0 && j < boardSize){
			if((*board)[i][j] == player){
				break;
			}
			if((*board)[i][j] == None){
				break;
			}
			(*board)[i][j] = player;
			i--;
			j++;
		}
}

void downLeftFlip(Board board, int player, int oppenent, int x, int y){
		// Opponent down and the the left
		int i = x+1;
                int j = y-1;
                while(i < boardSize && j >= 0){
                        if((*board)[i][j] == player){
                                break;
                        }
                        if((*board)[i][j] == None){
                                break;
                        }
			(*board)[i][j] = player;
                        i++;
                        j--;
                }
}

void downwardsFlip(Board board, int player, int oppenent, int x, int y){
		// Opponent downwards
		int i = x+1;
		while(i < boardSize){
			if((*board)[i][y] == player){
				break;
			}
			if((*board)[i][y] == None){
				break;
			}
			(*board)[i][y] = player;
			i++;
		}
}

void downRightFlip(Board board, int player, int oppenent, int x, int y){
		// Opponent down and to the right
		int i = x+1;
                int j = y+1;
                while(i < boardSize && j < boardSize){
                        if((*board)[i][j] == player){
                                break;
                        }
                        if((*board)[i][j] == None){
                                break;
                        }
			(*board)[i][j] = player;
                        i++;
                        j++;
                }
}

void upperLeftChoiceFlip(Board board, int player, int oppenent, int x, int y){
	if(toRight(board, player, oppenent, x, y)){
		toRightFlip(board, player, oppenent, x, y);
	}
	if(downwards(board, player, oppenent, x, y)){
		downwardsFlip(board, player, oppenent, x, y);
	}
	if(downRight(board, player, oppenent, x, y)){
		downRightFlip(board, player, oppenent, x, y);
	}
}

void upperRightChoiceFlip(Board board, int player, int oppenent, int x, int y){
	if(toLeft(board, player, oppenent, x, y)){
		toLeftFlip(board, player, oppenent, x, y);
	}
	if(downLeft(board, player, oppenent, x, y)){
		downLeftFlip(board, player, oppenent, x, y);
	}
	if(downwards(board, player, oppenent, x, y)){
		downwardsFlip(board, player, oppenent, x, y);
	}
}

void lowerLeftChoiceFlip(Board board, int player, int oppenent, int x, int y){
	if(toRight(board, player, oppenent, x, y)){
		toRightFlip(board, player, oppenent, x, y);
	}
	if(upwards(board, player, oppenent, x, y)){
		upwardsFlip(board, player, oppenent, x, y);
	}
	if(upRight(board, player, oppenent, x, y)){
		upRightFlip(board, player, oppenent, x, y);
	}
}

void lowerRightChoiceFlip(Board board, int player, int oppenent, int x, int y){
	if(toLeft(board, player, oppenent, x, y)){
		toLeftFlip(board, player, oppenent, x, y);
	}
	if(upLeft(board, player, oppenent, x, y)){
		upLeftFlip(board, player, oppenent, x, y);
	}
	if(upwards(board, player, oppenent, x, y)){
		upwardsFlip(board, player, oppenent, x, y);
	}
}

void upperEdgeChoiceFlip(Board board, int player, int oppenent, int x, int y){
	if(toLeft(board, player, oppenent, x, y)){
		toLeftFlip(board, player, oppenent, x, y);
	}
	if(toRight(board, player, oppenent, x, y)){
		toRightFlip(board, player, oppenent, x, y);
	}
	if(downLeft(board, player, oppenent, x, y)){
		downLeftFlip(board, player, oppenent, x, y);
	}
	if(downwards(board, player, oppenent, x, y)){
		downwardsFlip(board, player, oppenent, x, y);
	}
	if(downRight(board, player, oppenent, x, y)){
		downRightFlip(board, player, oppenent, x, y);
	}
}

void leftEdgeChoiceFlip(Board board, int player, int oppenent, int x, int y){
	if(toRight(board, player, oppenent, x, y)){
		toRightFlip(board, player, oppenent, x, y);
	}
	if(upwards(board, player, oppenent, x, y)){
		upwardsFlip(board, player, oppenent, x, y);
	}
	if(upRight(board, player, oppenent, x, y)){
		upRightFlip(board, player, oppenent, x, y);
	}
	if(downwards(board, player, oppenent, x, y)){
		downwardsFlip(board, player, oppenent, x, y);
	}
	if(downRight(board, player, oppenent, x, y)){
		downRightFlip(board, player, oppenent, x, y);
	}
}

void rightEdgeChoiceFlip(Board board, int player, int oppenent, int x, int y){
	if(toLeft(board, player, oppenent, x, y)){
		toLeftFlip(board, player, oppenent, x, y);
	}
	if(upLeft(board, player, oppenent, x, y)){
		upLeftFlip(board, player, oppenent, x, y);
	}
	if(upwards(board, player, oppenent, x, y)){
		upwardsFlip(board, player, oppenent, x, y);
	}
	if(downLeft(board, player, oppenent, x, y)){
		downLeftFlip(board, player, oppenent, x, y);
	}
	if(downwards(board, player, oppenent, x, y)){
		downwardsFlip(board, player, oppenent, x, y);
	}
}

void lowerEdgeChoiceFlip(Board board, int player, int oppenent, int x, int y){
	int found = 0;
	if(toLeft(board, player, oppenent, x, y)){
		toLeftFlip(board, player, oppenent, x, y);
	}
	if(toRight(board, player, oppenent, x, y)){
		toRightFlip(board, player, oppenent, x, y);
	}
	if(upLeft(board, player, oppenent, x, y)){
		upLeftFlip(board, player, oppenent, x, y);
	}
	if(upwards(board, player, oppenent, x, y)){
		upwardsFlip(board, player, oppenent, x, y);
	}
	if(upRight(board, player, oppenent, x, y)){
		upRightFlip(board, player, oppenent, x, y);
	}
}

void noEdgeChoiceFlip(Board board, int player, int oppenent, int x, int y){
	if(toLeft(board, player, oppenent, x, y)){
		toLeftFlip(board, player, oppenent, x, y);
	}
	if(toRight(board, player, oppenent, x, y)){
		toRightFlip(board, player, oppenent, x, y);
	}
	if(upLeft(board, player, oppenent, x, y)){
		upLeftFlip(board, player, oppenent, x, y);
	}
	if(upwards(board, player, oppenent, x, y)){
		upwardsFlip(board, player, oppenent, x, y);
	}
	if(upRight(board, player, oppenent, x, y)){
		upRightFlip(board, player, oppenent, x, y);
	}
	if(downLeft(board, player, oppenent, x, y)){
		downLeftFlip(board, player, oppenent, x, y);
	}
	if(downwards(board, player, oppenent, x, y)){
		downwardsFlip(board, player, oppenent, x, y);
	}
	if(downRight(board, player, oppenent, x, y)){
		downRightFlip(board, player, oppenent, x, y);
	}
}

void doFlip(Board board, int player, int x, int y){
	// Set oppenent number
	int oppenent = 0;
	if(player == White){
		oppenent = Black;
	}
	else{
		oppenent = White;
	}
	// Upper Left Corner
	if(x == 0 && y == 0){
		upperLeftChoiceFlip(board, player, oppenent, x, y);
	}
	// Upper Right Corner
	if(x == 0 && y == boardSize-1){
		upperRightChoiceFlip(board, player, oppenent, x, y);
	}
	// Lower Left Corner
	if(x == boardSize-1 && y == 0){
		lowerLeftChoiceFlip(board, player, oppenent, x, y);
	}
	// Lower Right Corner
	if(x == boardSize-1 && y == boardSize-1){
		lowerRightChoiceFlip(board, player, oppenent, x, y);
	}
	// The following is for an upper edge choice
	if(x == 0 && y != 0 && y != boardSize-1){
		upperEdgeChoiceFlip(board, player, oppenent, x, y);
	}
	// The following is for a left edge choice
	if(y == 0 && x != 0 && x != boardSize-1){
		leftEdgeChoiceFlip(board, player, oppenent, x, y);
	}
	// The following is for a right edge choice
	if(y == boardSize-1 && x != 0 && x != boardSize-1){
		rightEdgeChoiceFlip(board, player, oppenent, x, y);
	}
	// The following is for a lower edge choice
	if(x == boardSize-1 && y != 0 && y != boardSize-1){
		lowerEdgeChoiceFlip(board, player, oppenent, x, y);
	}
	// The following is for a none edge choice
	if(x != 0 && x != boardSize-1 && y != 0 && y != boardSize-1){
		noEdgeChoiceFlip(board, player, oppenent, x, y);
	}
}
