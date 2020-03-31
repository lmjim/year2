#include <iostream>
#include <vector>
#include <sstream>
#include "reversi.hpp"
#include "placement.hpp"
#include "flip.hpp"

namespace reversi{

void Reversi::setBoardSize(int size){
	this->boardSize = size;
}

int Reversi::askBoardSize(){
        int valid = 0;
        int number = 0;
        std::string input;
        while(!valid){
                printf("Please enter the size of the board (4-16): "); // Ask for input
                std::getline(std::cin,  input); // Get input
                if(std::cin.fail() || input.find_first_not_of("0123456789") != std::string::npos || input.empty()){
                        std::cout << "Invalid entry." << std::endl; // Do not accept input with anything other than a number and handle case when input is just 'enter'
                }
                else{
                        number = std::stoi(input); // Convert string to int
                        if(number > 16 || number < 4){
                                std::cout << "Invalid size." << std::endl; // Minimum board size is 4 and maximum is 16
                        }
                        else{
                                valid = 1;
                        }
                }
        }
        std::cout << "You entered: " << number << std::endl;
        return number;
}

void Reversi::newBoard(Board board){
	// Dynamically allocate 2d array for board
        *board = new int * [boardSize];
        for(int i=0; i<boardSize; i++){
                (*board)[i] = new int[boardSize];
        }
}

void Reversi::initBoard(Board board){
	// Dynamically allocate 2d array for board
	newBoard(board);

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

void Reversi::initScore(Score *score){
        score->p1 = 2; // Each player starts with 2 discs on the board
        score->p2 = 2; // Each player starts with 2 discs on the board
}

void Reversi::updateScore(Board board, Score *score){
	int black = 0;
	int white = 0;
	for(int i=0; i<boardSize; i++){
                for(int j=0; j<boardSize; j++){
                        int d = (*board)[i][j];
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

void Reversi::printScore(Score *score){
	std::cout << "Player 1: " << score->p1 << "\tPlayer 2: " << score->p2 << std::endl;
}

void Reversi::printBoard(Board board){
	// Print board with 0's as no disc, 1's for player1 (or black pieces), and
	//					2's for player2 (or white pieces)
	std::cout << "  ";
	for(int i=0; i<boardSize; i++){
		if(i < 10){
			std::cout << " "; // When the board size is greater than 9 this prevents alignment issues
		}
		std::cout << i << " ";
	}
	std::cout << std::endl;
	for(int i=0; i<boardSize; i++){
		if(i < 10){
			std::cout << " "; // When the board size is greater than 9 this prevents alignment issues
		}
		std::cout << i << " ";
		for(int j=0; j<boardSize; j++){
			int d = (*board)[i][j];
			if(d == Black){
				std::cout << "#  "; // Black discs are '#'
			}
			else if(d == White){
				std::cout << "O  "; // White discs are 'O'
			}
			else{
				std::cout << ".  "; // No disc is '.'
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Reversi::messageToPlayers(){
	std::cout << "Game started" << std::endl;
	// Logistics to make players aware of
	std::cout << "\'.\' represents no disc" << std::endl << "\'#\' represents a black disc" << std::endl << "\'O\' represents a white disc" << std::endl; // Explain how symbols match up to discs
	std::cout << "Player 1 is black" << std::endl << "Player 2 is white" << std::endl << std::endl; // Tell players' their colors
}

std::vector<int> Reversi::getTurnInput(Board board, int player){
	placement::Placement p;
	int valid = 0;
	int x = 0;
        int y = 0;
        std::string input;
        while(!valid){
                std::cout << "Player " << player << "\'s turn, choose row and col for new disc. Input 2 numbers: "; // Ask for input
                std::getline(std::cin, input); // Get input
                if(std::cin.fail() || input.find_first_not_of("0123456789 ") != std::string::npos || input.empty()){
                        std::cout << "Invalid entry." << std::endl; // Do not accept input with anything other than a numbers and handle case when input is just 'enter'
                }
                else{
                        std::stringstream inputStream(input);
                        std::vector<std::string> tokens;
                        std::string tokenRemaining;
                        while(getline(inputStream, tokenRemaining, ' ')){
                                tokens.push_back(tokenRemaining); // Split string into pieces to convert to numbers
                        }
                        if(tokens.size() != 2){
                                std::cout << "Invalid entry." << std::endl; // Only process input with two numbers separated by a single space
                        }
                        else{
                                x = std::stoi(tokens[0]); // Convert first number from string to int
                                y = std::stoi(tokens[1]); // Convert second number from string to int
                                if(!p.isValidPlacement(board, boardSize, player, x, y)){
                                        std::cout << "Invalid choice." << std::endl; // Check that choice is valid
                                }
                                else{
                                        valid = 1;
                                }
                        }
                }
        }
        std::vector<int> xy{x, y};
	std::cout << "You chose " << xy[0] << " " << xy[1] << "." << std::endl <<std::endl;
	return xy;
}

void Reversi::placeAndFlip(Board board, int player, int x, int y){
	(*board)[x][y] = player; // Place new disc
	flip::Flip f;
	f.doFlip(board, boardSize, player, x, y); // Flip discs
}

void Reversi::player1Turn(Board board, Score *score){
	int player = 1;
	std::vector<int> xy =getTurnInput(board, player);
	int x = xy[0];
	int y = xy[1];
	placeAndFlip(board, player, x, y);
	updateScore(board, score);
	printScore(score);
	printBoard(board);
}

void Reversi::player2Turn(Board board, Score *score){
	int player = 2;
	std::vector<int> xy =getTurnInput(board, player);
        int x = xy[0];
        int y = xy[1];
        placeAndFlip(board, player, x, y);
        updateScore(board, score);
        printScore(score);
        printBoard(board);
}

int Reversi::isTurnsRemaining(Board board){
	placement::Placement p;
	int p1 = 0;
	int p2 = 0;
	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++){
			if((*board)[i][j] == None){
				p1 += p.isValidPlacement(board, boardSize, 1, i, j);
				p2 += p.isValidPlacement(board, boardSize, 2, i, j);
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

void Reversi::gameOver(Score *score){
	std::cout << "Final Score: " << std::endl;
        printScore(score);
        if(score->p1 > score->p2){
		std::cout << "Player 1 wins!" << std::endl;
        }else if(score->p1 < score->p2){
		std::cout << "Player 2 wins!" << std::endl;
        }else{
		std::cout << "It's a tie!" << std::endl;
        }
	std::cout << "Game Over" << std::endl;
}

void Reversi::runGame(Board board){
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
			std::cout << "No moves for player 1. Switch to player 2." << std::endl;
		}
		if(turnsRemaining == 0){
			break;
		}
		if(turnsRemaining == 2 || turnsRemaining == 3){
			player2Turn(board, &score);
			turnsRemaining = isTurnsRemaining(board);
		}
		else{
			std::cout << "No moves for player 2. Switch to player 1." << std::endl;
		}
	}
	// Game Over message
	gameOver(&score);
}

void Reversi::cleanBoard(Board board){
	// Free dynamically created arrays
	for(int i=0; i<boardSize; i++){
		delete [] (*board)[i];
	}
	delete [] *board;
}
}
