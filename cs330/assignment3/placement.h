#ifndef PLACEMENT_H_
#define PLACEMENT_H_

int placementBoardSize(int size); // Set board size in placement file

int toLeft(Board board, int player, int oppenent, int x, int y);

int toRight(Board board, int player, int oppenent, int x, int y);

int upLeft(Board board, int player, int oppenent, int x, int y);

int upwards(Board board, int player, int oppenent, int x, int y);

int upRight(Board board, int player, int oppenent, int x, int y);

int downLeft(Board board, int player, int oppenent, int x, int y);

int downwards(Board board, int player, int oppenent, int x, int y);

int downRight(Board board, int player, int oppenent, int x, int y);

int isValidPlacement(Board board, int player, int x, int y); // Checks if xy is valid placement for disc

#endif /* PLACEMENT_H_ */
