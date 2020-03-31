#include <iostream>
#include "reversi.hpp"
#include "placement.hpp"
#include "flip.hpp"

namespace flip{

void Flip::toLeftFlip(Board board, int player, int oppenent, int x, int y){
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

void Flip::toRightFlip(Board board, int boardSize, int player, int oppenent, int x, int y){
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

void Flip::upLeftFlip(Board board, int player, int oppenent, int x, int y){
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

void Flip::upwardsFlip(Board board, int player, int oppenent, int x, int y){
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

void Flip::upRightFlip(Board board, int boardSize, int player, int oppenent, int x, int y){
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

void Flip::downLeftFlip(Board board, int boardSize, int player, int oppenent, int x, int y){
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

void Flip::downwardsFlip(Board board, int boardSize, int player, int oppenent, int x, int y){
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

void Flip::downRightFlip(Board board, int boardSize, int player, int oppenent, int x, int y){
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

void Flip::upperLeftChoiceFlip(Board board, int boardSize, int player, int oppenent, int x, int y, placement::Placement p){
	if(p.toRight(board, boardSize, player, oppenent, x, y)){
		toRightFlip(board, boardSize, player, oppenent, x, y);
	}
	if(p.downwards(board, boardSize, player, oppenent, x, y)){
		downwardsFlip(board, boardSize, player, oppenent, x, y);
	}
	if(p.downRight(board, boardSize, player, oppenent, x, y)){
		downRightFlip(board, boardSize, player, oppenent, x, y);
	}
}

void Flip::upperRightChoiceFlip(Board board, int boardSize, int player, int oppenent, int x, int y, placement::Placement p){
	if(p.toLeft(board, player, oppenent, x, y)){
		toLeftFlip(board, player, oppenent, x, y);
	}
	if(p.downLeft(board, boardSize, player, oppenent, x, y)){
		downLeftFlip(board, boardSize, player, oppenent, x, y);
	}
	if(p.downwards(board, boardSize, player, oppenent, x, y)){
		downwardsFlip(board, boardSize, player, oppenent, x, y);
	}
}

void Flip::lowerLeftChoiceFlip(Board board, int boardSize, int player, int oppenent, int x, int y, placement::Placement p){
	if(p.toRight(board, boardSize, player, oppenent, x, y)){
		toRightFlip(board, boardSize, player, oppenent, x, y);
	}
	if(p.upwards(board, player, oppenent, x, y)){
		upwardsFlip(board, player, oppenent, x, y);
	}
	if(p.upRight(board, boardSize, player, oppenent, x, y)){
		upRightFlip(board, boardSize, player, oppenent, x, y);
	}
}

void Flip::lowerRightChoiceFlip(Board board, int player, int oppenent, int x, int y, placement::Placement p){
	if(p.toLeft(board, player, oppenent, x, y)){
		toLeftFlip(board, player, oppenent, x, y);
	}
	if(p.upLeft(board, player, oppenent, x, y)){
		upLeftFlip(board, player, oppenent, x, y);
	}
	if(p.upwards(board, player, oppenent, x, y)){
		upwardsFlip(board, player, oppenent, x, y);
	}
}

void Flip::upperEdgeChoiceFlip(Board board, int boardSize, int player, int oppenent, int x, int y, placement::Placement p){
	if(p.toLeft(board, player, oppenent, x, y)){
		toLeftFlip(board, player, oppenent, x, y);
	}
	if(p.toRight(board, boardSize, player, oppenent, x, y)){
		toRightFlip(board, boardSize, player, oppenent, x, y);
	}
	if(p.downLeft(board, boardSize, player, oppenent, x, y)){
		downLeftFlip(board, boardSize, player, oppenent, x, y);
	}
	if(p.downwards(board, boardSize, player, oppenent, x, y)){
		downwardsFlip(board, boardSize, player, oppenent, x, y);
	}
	if(p.downRight(board, boardSize, player, oppenent, x, y)){
		downRightFlip(board, boardSize, player, oppenent, x, y);
	}
}

void Flip::leftEdgeChoiceFlip(Board board, int boardSize, int player, int oppenent, int x, int y, placement::Placement p){
	if(p.toRight(board, boardSize, player, oppenent, x, y)){
		toRightFlip(board, boardSize, player, oppenent, x, y);
	}
	if(p.upwards(board, player, oppenent, x, y)){
		upwardsFlip(board, player, oppenent, x, y);
	}
	if(p.upRight(board, boardSize, player, oppenent, x, y)){
		upRightFlip(board, boardSize, player, oppenent, x, y);
	}
	if(p.downwards(board, boardSize, player, oppenent, x, y)){
		downwardsFlip(board, boardSize, player, oppenent, x, y);
	}
	if(p.downRight(board, boardSize, player, oppenent, x, y)){
		downRightFlip(board, boardSize, player, oppenent, x, y);
	}
}

void Flip::rightEdgeChoiceFlip(Board board, int boardSize, int player, int oppenent, int x, int y, placement::Placement p){
	if(p.toLeft(board, player, oppenent, x, y)){
		toLeftFlip(board, player, oppenent, x, y);
	}
	if(p.upLeft(board, player, oppenent, x, y)){
		upLeftFlip(board, player, oppenent, x, y);
	}
	if(p.upwards(board, player, oppenent, x, y)){
		upwardsFlip(board, player, oppenent, x, y);
	}
	if(p.downLeft(board, boardSize, player, oppenent, x, y)){
		downLeftFlip(board, boardSize, player, oppenent, x, y);
	}
	if(p.downwards(board, boardSize, player, oppenent, x, y)){
		downwardsFlip(board, boardSize, player, oppenent, x, y);
	}
}

void Flip::lowerEdgeChoiceFlip(Board board, int boardSize, int player, int oppenent, int x, int y, placement::Placement p){
	int found = 0;
	if(p.toLeft(board, player, oppenent, x, y)){
		toLeftFlip(board, player, oppenent, x, y);
	}
	if(p.toRight(board, boardSize, player, oppenent, x, y)){
		toRightFlip(board, boardSize, player, oppenent, x, y);
	}
	if(p.upLeft(board, player, oppenent, x, y)){
		upLeftFlip(board, player, oppenent, x, y);
	}
	if(p.upwards(board, player, oppenent, x, y)){
		upwardsFlip(board, player, oppenent, x, y);
	}
	if(p.upRight(board, boardSize, player, oppenent, x, y)){
		upRightFlip(board, boardSize, player, oppenent, x, y);
	}
}

void Flip::noEdgeChoiceFlip(Board board, int boardSize, int player, int oppenent, int x, int y, placement::Placement p){
	if(p.toLeft(board, player, oppenent, x, y)){
		toLeftFlip(board, player, oppenent, x, y);
	}
	if(p.toRight(board, boardSize, player, oppenent, x, y)){
		toRightFlip(board, boardSize, player, oppenent, x, y);
	}
	if(p.upLeft(board, player, oppenent, x, y)){
		upLeftFlip(board, player, oppenent, x, y);
	}
	if(p.upwards(board, player, oppenent, x, y)){
		upwardsFlip(board, player, oppenent, x, y);
	}
	if(p.upRight(board, boardSize, player, oppenent, x, y)){
		upRightFlip(board, boardSize, player, oppenent, x, y);
	}
	if(p.downLeft(board, boardSize, player, oppenent, x, y)){
		downLeftFlip(board, boardSize, player, oppenent, x, y);
	}
	if(p.downwards(board, boardSize, player, oppenent, x, y)){
		downwardsFlip(board, boardSize, player, oppenent, x, y);
	}
	if(p.downRight(board, boardSize, player, oppenent, x, y)){
		downRightFlip(board, boardSize, player, oppenent, x, y);
	}
}

void Flip::doFlip(Board board, int boardSize, int player, int x, int y){
	// Access to placement
	placement::Placement p;
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
		upperLeftChoiceFlip(board, boardSize, player, oppenent, x, y, p);
	}
	// Upper Right Corner
	if(x == 0 && y == boardSize-1){
		upperRightChoiceFlip(board, boardSize, player, oppenent, x, y, p);
	}
	// Lower Left Corner
	if(x == boardSize-1 && y == 0){
		lowerLeftChoiceFlip(board, boardSize, player, oppenent, x, y, p);
	}
	// Lower Right Corner
	if(x == boardSize-1 && y == boardSize-1){
		lowerRightChoiceFlip(board, player, oppenent, x, y, p);
	}
	// The following is for an upper edge choice
	if(x == 0 && y != 0 && y != boardSize-1){
		upperEdgeChoiceFlip(board, boardSize, player, oppenent, x, y, p);
	}
	// The following is for a left edge choice
	if(y == 0 && x != 0 && x != boardSize-1){
		leftEdgeChoiceFlip(board, boardSize, player, oppenent, x, y, p);
	}
	// The following is for a right edge choice
	if(y == boardSize-1 && x != 0 && x != boardSize-1){
		rightEdgeChoiceFlip(board, boardSize, player, oppenent, x, y, p);
	}
	// The following is for a lower edge choice
	if(x == boardSize-1 && y != 0 && y != boardSize-1){
		lowerEdgeChoiceFlip(board, boardSize, player, oppenent, x, y, p);
	}
	// The following is for a none edge choice
	if(x != 0 && x != boardSize-1 && y != 0 && y != boardSize-1){
		noEdgeChoiceFlip(board, boardSize, player, oppenent, x, y, p);
	}
}
}
