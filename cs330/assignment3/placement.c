#include <stdio.h>
#include "reversi.h"
#include "placement.h"

// Global Variable
static int boardSize = 0;

int placementBoardSize(int size){
	boardSize = size; // Set global variable for size of board
}

int toLeft(Board board, int player, int oppenent, int x, int y){
        if((*board)[x][y-1] == oppenent){
		// Opponent to the left
                int j = y-2;
                while(j >= 0){
                        if((*board)[x][j] == player){
                                return 1;
                        }
                        if((*board)[x][j] == None){
                                break;
                        }
                        j--;
                }
        }
	return 0;
}

int toRight(Board board, int player, int oppenent, int x, int y){
        if((*board)[x][y+1] == oppenent){
		// Opponent to the right
                int j = y+2;
                while(j < boardSize){
                        if((*board)[x][j] == player){
                                return 1;
                        }
                        if((*board)[x][j] == None){
                                break;
                        }
                        j++;
                }
        }
	return 0;
}

int upLeft(Board board, int player, int oppenent, int x, int y){
        if((*board)[x-1][y-1] == oppenent){
		// Opponent up and to the left
		int i = x-2;
                int j = y-2;
                while(i >= 0 && j >= 0){
                        if((*board)[i][j] == player){
                                return 1;
                        }
                        if((*board)[i][j] == None){
                                break;
                        }
                        i--;
                        j--;
                }
        }
	return 0;
}

int upwards(Board board, int player, int oppenent, int x, int y){
	if((*board)[x-1][y] == oppenent){
		// Opponent upwards
		int i = x-2;
		while(i >= 0){
			if((*board)[i][y] == player){
				return 1;
			}
			if((*board)[i][y] == None){
				break;
			}
			i--;
		}
        }
	return 0;
}

int upRight(Board board, int player, int oppenent, int x, int y){
        if((*board)[x-1][y+1] == oppenent){
		// Opponent up and to the right
		int i = x-2;
		int j = y+2;
		while(i >= 0 && j < boardSize){
			if((*board)[i][j] == player){
				return 1;
			}
			if((*board)[i][j] == None){
				break;
			}
			i--;
			j++;
		}
        }
	return 0;
}

int downLeft(Board board, int player, int oppenent, int x, int y){
        if((*board)[x+1][y-1] == oppenent){
		// Opponent down and the the left
		int i = x+2;
                int j = y-2;
                while(i < boardSize && j >= 0){
                        if((*board)[i][j] == player){
                                return 1;
                        }
                        if((*board)[i][j] == None){
                                break;
                        }
                        i++;
                        j--;
                }
        }
	return 0;
}

int downwards(Board board, int player, int oppenent, int x, int y){
        if((*board)[x+1][y] == oppenent){
		// Opponent downwards
		int i = x+2;
		while(i < boardSize){
			if((*board)[i][y] == player){
				return 1;
			}
			if((*board)[i][y] == None){
				break;
			}
			i++;
		}
        }
	return 0;
}

int downRight(Board board, int player, int oppenent, int x, int y){
        if((*board)[x+1][y+1] == oppenent){
		// Opponent down and to the right
		int i = x+2;
                int j = y+2;
                while(i < boardSize && j < boardSize){
                        if((*board)[i][j] == player){
                                return 1;
                        }
                        if((*board)[i][j] == None){
                                break;
                        }
                        i++;
                        j++;
                }
        }
	return 0;
}

int upperLeftChoice(Board board, int player, int oppenent, int x, int y){
	int found = 0;
	found += toRight(board, player, oppenent, x, y);
	found += downwards(board, player, oppenent, x, y);
	found += downRight(board, player, oppenent, x, y);
	return found;
}

int upperRightChoice(Board board, int player, int oppenent, int x, int y){
	int found = 0;
	found += toLeft(board, player, oppenent, x, y);
	found += downLeft(board, player, oppenent, x, y);
	found += downwards(board, player, oppenent, x, y);
	return found;
}

int lowerLeftChoice(Board board, int player, int oppenent, int x, int y){
	int found = 0;
	found += toRight(board, player, oppenent, x, y);
	found += upwards(board, player, oppenent, x, y);
	found += upRight(board, player, oppenent, x, y);
	return found;
}

int lowerRightChoice(Board board, int player, int oppenent, int x, int y){
	int found = 0;
	found += toLeft(board, player, oppenent, x, y);
	found += upLeft(board, player, oppenent, x, y);
	found += upwards(board, player, oppenent, x, y);
	return found;
}

int upperEdgeChoice(Board board, int player, int oppenent, int x, int y){
	int found = 0;
	found += toLeft(board, player, oppenent, x, y);
	found += toRight(board, player, oppenent, x, y);
	found += downLeft(board, player, oppenent, x, y);
	found += downwards(board, player, oppenent, x, y);
	found += downRight(board, player, oppenent, x, y);
	return found;
}

int leftEdgeChoice(Board board, int player, int oppenent, int x, int y){
	int found = 0;
	found += toRight(board, player, oppenent, x, y);
	found += upwards(board, player, oppenent, x, y);
	found += upRight(board, player, oppenent, x, y);
	found += downwards(board, player, oppenent, x, y);
	found += downRight(board, player, oppenent, x, y);
	return found;
}

int rightEdgeChoice(Board board, int player, int oppenent, int x, int y){
	int found = 0;
	found += toLeft(board, player, oppenent, x, y);
	found += upLeft(board, player, oppenent, x, y);
	found += upwards(board, player, oppenent, x, y);
	found += downLeft(board, player, oppenent, x, y);
	found += downwards(board, player, oppenent, x, y);
	return found;
}

int lowerEdgeChoice(Board board, int player, int oppenent, int x, int y){
	int found = 0;
	found += toLeft(board, player, oppenent, x, y);
	found += toRight(board, player, oppenent, x, y);
	found += upLeft(board, player, oppenent, x, y);
	found += upwards(board, player, oppenent, x, y);
	found += upRight(board, player, oppenent, x, y);
	return found;
}

int noEdgeChoice(Board board, int player, int oppenent, int x, int y){
	int found = 0;
	found += toLeft(board, player, oppenent, x, y);
	found += toRight(board, player, oppenent, x, y);
	found += upLeft(board, player, oppenent, x, y);
	found += upwards(board, player, oppenent, x, y);
	found += upRight(board, player, oppenent, x, y);
	found += downLeft(board, player, oppenent, x, y);
	found += downwards(board, player, oppenent, x, y);
	found += downRight(board, player, oppenent, x, y);
	return found;
}

int isValidPlacement(Board board, int player, int x, int y){
	// Check if xy is a valid point on the board
	if(x < 0 || y < 0 || x >= boardSize || y >= boardSize){
		printf("Not a place on the board.\n");
		return 0;
	}

	// Check if a disc is already there
	if((*board)[x][y] != None){
		printf("Disc already there.\n");
		return 0;
	}

	// Check if a surrounding disc is an oppenent's and in that direction there is eventually the player's own disc
	int found = 0;
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
		found = upperLeftChoice(board, player, oppenent, x, y);
	}
	// Upper Right Corner
	if(x == 0 && y == boardSize-1){
		found = upperRightChoice(board, player, oppenent, x, y);
	}
	// Lower Left Corner
	if(x == boardSize-1 && y == 0){
		found = lowerLeftChoice(board, player, oppenent, x, y);
	}
	// Lower Right Corner
	if(x == boardSize-1 && y == boardSize-1){
		found = lowerRightChoice(board, player, oppenent, x, y);
	}
	// The following is for an upper edge choice
	if(x == 0 && y != 0 && y != boardSize-1){
		found = upperEdgeChoice(board, player, oppenent, x, y);
	}
	// The following is for a left edge choice
	if(y == 0 && x != 0 && x != boardSize-1){
		found = leftEdgeChoice(board, player, oppenent, x, y);
	}
	// The following is for a right edge choice
	if(y == boardSize-1 && x != 0 && x != boardSize-1){
		found = rightEdgeChoice(board, player, oppenent, x, y);
	}
	// The following is for a lower edge choice
	if(x == boardSize-1 && y != 0 && y != boardSize-1){
		found = lowerEdgeChoice(board, player, oppenent, x, y);
	}
	// The following is for a none edge choice
	if(x != 0 && x != boardSize-1 && y != 0 && y != boardSize-1){
		found = noEdgeChoice(board, player, oppenent, x, y);
	}
	return found;
}
