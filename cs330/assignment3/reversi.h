#ifndef REVERSI_H_
#define REVERSI_H_

// Credits:
// 	learning about enum: https://www.geeksforgeeks.org/enumeration-enum-c/
// 	learning about Othello: https://www.wikihow.com/Play-Othello
// 				https://www.youtube.com/watch?v=XDxuPNhBfZs
// 	learning about strtok: https://www.geeksforgeeks.org/strtok-strtok_r-functions-c-examples/


typedef int*** Board; // Make use of board easier and look nicer

typedef enum {None, Black, White} Disc; // Any position on the board can either be no disc, black disc, or white disc

typedef struct{
	int p1; // Player One
	int p2; // Player Two
} Score;

void setBoardSize(int size); // Set the user given board size

int askBoardSize(); // Get user input for board size

void initBoard(Board board); // Initialize an empty board of a certain size

void runGame(Board board); // Run the game with the given board

void cleanBoard(Board board); // Free up the board

#endif /* REVERSI_H_ */
