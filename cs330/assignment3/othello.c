#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "othello.h"
#include "placement.h"
#include "flip.h"

// Global Variable
static int boardSize = 0;

void setBoardSize(int size){
	boardSize = size; // Set global variable for size of board
	placementBoardSize(size);
	flipBoardSize(size);
}

int askBoardSize(){
        int valid = 0;
        long number = 0;
        while(!valid){
                printf("Please enter the size of the board (4-16): "); // Ask for input
                int max = 15;
                char input[max];
                fgets(input, max, stdin); // Read input
                char *end;
                number = strtol(input, &end, 10); // Convert input from string to long
                if(strcmp(end, "\n") != 0){
                        printf("Invalid entry.\n"); // Do not accept input with anything other than a number
                }
                else if(number > 16 || number <4){
                        printf("Invalid size.\n"); // Minimum board size is 4 and maximum is 16
                }
                else{
                        valid = 1;
                }
        }
        return (int) number;
}

void mallocBoard(Board board){
	// Dynamically allocate 2d array for board
        *board = (int **)malloc(boardSize * sizeof(int*));
        for(int i=0; i<boardSize; i++){
                (*board)[i] = (int*)malloc(boardSize * sizeof(int));
        }
}

void initBoard(Board board){
	// Dynamically allocate 2d array for board
	mallocBoard(board);

	// Set all the spots on the board to be empty
	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++){
			(*board)[i][j] = None;
		}
	}

	// Set middle 4 squares with 2 black and 2 white
	// If boardSize is odd, pieces will be offset from center left and up by 1
	int place = boardSize / 2;
	(*board)[place][place] = White;
	(*board)[place-1][place-1] = White;
	(*board)[place-1][place] = Black;
	(*board)[place][place-1] = Black;
}

void initScore(Score *score){
	score->p1 = 2; // Each player starts with 2 discs on the board
	score->p2 = 2; // Each player starts with 2 discs on the board
}

void updateScore(Board board, Score *score){
	int black = 0;
	int white = 0;
	for(int i=0; i<boardSize; i++){
                for(int j=0; j<boardSize; j++){
                        Disc d = (*board)[i][j];
			if(d == Black){
				black++;
			}
			else if(d == White){
				white++;
			}
                }
        }
	score->p1 = black;
	score->p2 = white;
}

void printScore(Score *score){
	printf("You: %d\tComputer: %d\n", score->p1, score->p2);
}

void printBoard(Board board){
	// Print board with 0's as no disc, 1's for player1 (or black pieces), and
	//					2's for player2 (or white pieces)
	printf("  ");
	for(int i=0; i<boardSize; i++){
		if(i < 10){
			printf(" "); // When the board size is greater than 9 this prevents alignment issues
		}
		printf("%d ", i);
	}
	printf("\n");
	for(int i=0; i<boardSize; i++){
		if(i < 10){
			printf(" "); // When the board size is greater than 9 this prevents alignment issues
		}
		printf("%d ", i);
		for(int j=0; j<boardSize; j++){
			Disc d = (*board)[i][j];
			if(d == Black){
				printf("#  "); // Black discs are '#'
			}
			else if(d == White){
				printf("O  "); // White discs are 'O'
			}
			else{
				printf(".  "); // No disc is '.'
			}
		}
		printf("\n");
	}
	printf("\n");
}

void messageToPlayers(){
	printf("Game started\n");
	// Logistics to make players aware of
	printf("\'.\' represents no disc\n\'#\' represents a black disc\n\'O\' represents a white disc\n"); // Explain how symbols match up to discs
	printf("Your color is black\nComputer's color is white\n\n"); // Tell players' their colors
}

int * getTurnInput(Board board, int player){
	int valid = 0;
	long x = 0;
        long y = 0;
        while(!valid){
                printf("Player's turn, choose row and col for new disc. Input 2 numbers: "); // Ask for input
                int max = 15;
                char input[max];
                fgets(input, max, stdin); // Read input
		char *token = NULL;
		token = strtok(input, " ");
		char *end1 = NULL;
		x = strtol(token, &end1, 10); // Convert input from string to long
		token = strtok(NULL, " "); // Get next token
                char *end2 = NULL;
		if(token != NULL){
	                y = strtol(token, &end2, 10); // Convert input from string to long, if there is a second token
		}
                if(strcmp(end1, "\0") != 0 || strcmp(end2, "\n") != 0){
                        printf("Invalid entry.\n"); // Do not accept input with anything other than two numbers separated by a space
                }
		else if(!isValidPlacement(board, player, x, y)){
			printf("Invalid choice.\n");
		}
                else{
                        valid = 1;
                }
        }
	int position[2] = {(int) x, (int) y};
        int *xy = position;
	printf("You chose %d %d.\n\n", xy[0], xy[1]);
	return xy;
}

void placeAndFlip(Board board, int player, int x, int y){
	(*board)[x][y] = player; // Place new disc
	doFlip(board, player, x, y); // Flip discs
}

void player1Turn(Board board, Score *score){
	int player = 1;
	int *xy =getTurnInput(board, player);
	int x = xy[0];
	int y = xy[1];
	placeAndFlip(board, player, x, y);
	updateScore(board, score);
	printScore(score);
	printBoard(board);
}

int * computerChoice(Board board){
	int x = boardSize / 2; // Will always have a disc because of how the board starts
	int y = boardSize / 2; // Will always have a disc because of how the board starts
	while((*board)[x][y] != None){
                // This is to prevent messages to user when computer is choosing
                x = rand() % boardSize;
                y = rand() % boardSize;
        }
	while(!isValidPlacement(board, 2, x, y)){
		x = rand() % boardSize;
		y = rand() % boardSize;
		while((*board)[x][y] != None){
			// This is to prevent messages to user when computer is choosing
			x = rand() % boardSize;
			y = rand() % boardSize;
		}
	}
	int position[2] = {(int) x, (int) y};
	int *xy = position;
	printf("Computer chose %d %d.\n\n", xy[0], xy[1]);
	return xy;
}

void player2Turn(Board board, Score *score){
	int player = 2;
	int *xy = computerChoice(board);
        int x = xy[0];
        int y = xy[1];
        placeAndFlip(board, player, x, y);
        updateScore(board, score);
        printScore(score);
        printBoard(board);
}

int isTurnsRemaining(Board board){
	int p1 = 0;
	int p2 = 0;
	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++){
			if((*board)[i][j] == None){
				p1 += isValidPlacement(board, 1, i, j);
				p2 += isValidPlacement(board, 2, i, j);
				if(p1 != 0 && p2 != 0){
					return 3;
				}
			}
		}
	}
	if(p1 != 0){
		return 1;
	}
	else if(p2 != 0){
		return 2;
	}
	else{
		return 0;
	}
}

void gameOver(Score *score){
        printf("Final Score: \n");
        printScore(score);
        if(score->p1 > score->p2){
                printf("You win!\n");
        }else if(score->p1 < score->p2){
                printf("Computer wins.\n");
        }else{
                printf("It's a tie!\n");
        }
	printf("Game Over\n");
}

void runGame(Board board){
	// Initialize score
	Score score;
	initScore(&score);

	// Give players some information about gameplay
	messageToPlayers();
	printBoard(board);

	// Run actual game
	int turnsRemaining = isTurnsRemaining(board);
	while(turnsRemaining){
		if(turnsRemaining == 1 || turnsRemaining == 3){
			player1Turn(board, &score);
			turnsRemaining = isTurnsRemaining(board);
		}
		else{
			printf("No moves for you to play. Switching to computer's turn.\n");
		}
		if(turnsRemaining == 0){
			break;
		}
		if(turnsRemaining == 2 || turnsRemaining == 3){
			player2Turn(board, &score);
			turnsRemaining = isTurnsRemaining(board);
		}
		else{
			printf("No moves for computer to play. Switching back to you.\n");
		}
	}
	// Game Over message
	gameOver(&score);
}

void cleanBoard(Board board){
	// Free dynamically created arrays
	for(int i=0; i<boardSize; i++){
		free((*board)[i]);
	}
	free(*board);
}

