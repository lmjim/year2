#include <iostream>
#include <ncurses.h>
#include <vector>
#include <sstream>
#include <cstring>
#include "input.hpp"
#include "randMove.hpp"
#include "board.hpp"
#include "chess.hpp"
#include "checkers.hpp"
 #include "sorry.hpp" 
#include "aggravation.hpp"

using namespace std;

int input::Input::gameChoice(vector<string> choices){
	// Ask what game user would like to play
	cout << "What game would you like to play? Your choices are:" << endl;
	int numChoices = choices.size();
	for(int i=0; i<numChoices; i++){
		cout << (i+1) << ": " << choices[i] << "    ";
	}
	cout << endl;
	bool correct = false;
	string input;
	int in;
	// Keep asking until user inputs a valid choice
	while(!correct){
		cout << "Please enter the number corresponding to the game: ";
		getline(cin, input);
		if(std::cin.fail() || input.find_first_not_of("0123456789") != std::string::npos || input.empty()){
			cout << "Invalid Entry" << endl;
		}
		else{
			in = stoi(input);
			if(in > numChoices){
				cout << in << " was not an option" << endl;
			}
			else{
				correct = true;
			}
		}
	}
	// Notify user what was chosen
	cout << "You chose " << choices[in-1] << endl;
	return in; // Note: 'in' is +1 index off of the game chosen in the vector
}

vector<int> input::Input::getLocation(){
	vector<int> location{0,0};
	bool valid = false;
	while(!valid){
		char cstr[100]; // c string for curses input
		wgetstr(this->win, cstr); // get user input
		string input(cstr); // convert c string to c++ string
		if(input.find_first_not_of("1234567890 ") != string::npos || input.empty()){
			wmove(this->win, 2, 0);
			wclrtoeol(this->win);
			wprintw(this->win, "Invalid entry. Please enter position (x y): ");
			wrefresh(this->win);
		}
		else{
			stringstream inputStream(input);
			vector<string> tokens;
			string tokenRemaining;
			// split line into tokens
			while(getline(inputStream, tokenRemaining, ' ')){
				tokens.push_back(tokenRemaining);
			}
			// check that there are two tokens
			if(tokens.size() != 2){
				wmove(this->win, 2, 0);
	                        wclrtoeol(this->win);
	                        wprintw(this->win, "Invalid entry. Please enter position (x y): ");
	                        wrefresh(this->win);
			}
			// check that tokens aren't empty
			else if(tokens[0].empty() || tokens[1].empty()){
				wmove(this->win, 2, 0);
                                wclrtoeol(this->win);
                                wprintw(this->win, "Invalid entry. Please enter position (x y): ");
                                wrefresh(this->win);
			}
			else{
				// convert token string to int
				location[0] = stoi(tokens[0]);
				location[1] = stoi(tokens[1]);
				if(location[0] > 8 || location[1] > 8 || location[0] < 0 || location[1] < 0){
					wmove(this->win, 2, 0);
	                                wclrtoeol(this->win);
	                                wprintw(this->win, "Not a place on the board. Please enter position (x y): ");
	                                wrefresh(this->win);
				}
				else{
					valid = true;
				}
			}
		}
	}
	return location;
}

vector<int> input::Input::movingPieceLocation(board::Board * b, int player){
	vector<int> location;
	bool valid = false;
	wmove(this->win, 1, 0);
	wclrtoeol(this->win);
	wprintw(this->win, "Which piece would you like to move?"); // Ask which piece to move
	while(!valid){
		wmove(this->win, 2, 0);
		wclrtoeol(this->win);
		wprintw(this->win, "Please enter position (x y): "); // Ask for position
		wrefresh(this->win);
		location = Input::getLocation(); // Read in valid board position
		vector<int> piece = b->getPieceAt(location); // Get piece at that position
		if(piece[0] == 0){ // If there is not piece present as that position
			wmove(this->win, 1, 0);
			wclrtoeol(this->win);
			wprintw(this->win, "No piece present there. Which piece would you like to move? ");
		}
		else if(piece[0] != player){ // If the player didn't choose their own piece
			wmove(this->win, 1, 0);
			wclrtoeol(this->win);
			wprintw(this->win, "Cannot choose that piece. Which piece would you like to move? ");
		}
		else{ // Player chose their own piece
			valid = true;
		}
	}
	return location;
}

vector<int> input::Input::moveToLocation(vector<int> pieceToMove){
	vector<int> location;
	bool valid = false;
	wmove(this->win, 1, 0);
	wclrtoeol(this->win);
	wprintw(this->win, "Where would you like to move the piece at %d %d to?", pieceToMove[0], pieceToMove[1]); // Ask where to move piece to
	wmove(this->win, 2, 0);
	wclrtoeol(this->win);
	wprintw(this->win, "Please enter position (x y): "); // Ask for position
	wrefresh(this->win);
	location = Input::getLocation();
	// Note: checking if location is a valid move will happen in moveLocationChoice
	return location;
}

vector<int> input::Input::moveLocationChoice(int game, board::Board * b, int player){
	bool valid = false;
	vector<int> movePiece{0,0,0,0};
	wmove(this->win, 0, 0);
        wclrtoeol(this->win);
        wprintw(this->win, "Player %d's turn", player); // Notify who's turn it is
	while(!valid){
	        vector<int> pieceToMove = movingPieceLocation(b, player); // from location m
	        vector<int> placeToMoveTo = moveToLocation(pieceToMove); // to location n
		movePiece[0] = pieceToMove[0];
		movePiece[1] = pieceToMove[1];
		movePiece[2] = placeToMoveTo[0];
		movePiece[3] = placeToMoveTo[1];
		// check if piece can be moved from m to n
		bool validMove = false;
		chess::Chess chessGame; // access to chess functions
		checkers::Checkers checkersGame; // access to checkers functions
		switch(game){
			case 1:
				validMove = chessGame.validMove(b, movePiece, player); // check if piece can be moved from m to n when playing chess
				break;
			case 2:
				validMove = checkersGame.validMove(b, movePiece, player); // check if piece cna be moved from m to n when playing checkers
				break;
			default:
				validMove = false; // an issue has occured, the game number passed in is not an implemented game
				break;
		}
		if(!validMove){ // notify user that they made an invalid choice
			wmove(this->win, 1, 0);
			wclrtoeol(this->win);
			wprintw(this->win, "Cannot move %d %d to %d %d", movePiece[0], movePiece[1], movePiece[2], movePiece[3]);
			wmove(this->win, 2, 0);
			wclrtoeol(this->win);
			wprintw(this->win, "Hit enter to choose again");
			wrefresh(this->win);
			wgetch(this->win);
		}
		else{
			valid = true;
		}
	}

	/* debugging lines:
	wmove(this->win,1,0);
	wclrtoeol(this->win);
	wprintw(this->win, "You chose %d %d to move", movePiece[0], movePiece[1]);
	wmove(this->win,2,0);
	wclrtoeol(this->win);
	wprintw(this->win, "You chose to move it to %d %d", movePiece[2], movePiece[3]);
	wrefresh(this->win);
	wgetch(this->win);
	*/ // end debugging lines
	
	return movePiece; // return {from x, from y, to x, to y}
}

int input::Input::getPiece(){
	int piece = -1;
	wmove(this->win, 2, 0);
        wclrtoeol(this->win);
        wprintw(this->win, "Which piece would you like to move? "); // Ask which piece to move
	bool valid = false;
	while(!valid){
		char cstr[100]; // c string for curses input
                wgetstr(this->win, cstr); // get user input
                string input(cstr); // convert c string to c++ string
                if(input.find_first_not_of("1234567890") != string::npos || input.empty()){
                        wmove(this->win, 2, 0);
                        wclrtoeol(this->win);
                        wprintw(this->win, "Invalid entry. Which piece would you like to move? ");
                        wrefresh(this->win);
                }
		else{
			piece = stoi(input);
			if(piece < 1 || piece > 4){
				wmove(this->win, 2, 0);
				wclrtoeol(this->win);
				wprintw(this->win, "Not a piece. Which piece would you like to move?  ");
				wrefresh(this->win);
			}
			else{
				valid = true;
			}
		}
	}
	return piece;
}

vector<int> input::Input::pieceChoice(int game, board::AggravationBoard * b, aggravation::Aggravation * aggravationGame, int player, int num){
	/* Game passes in number rolled
	   This way if the player cannot move any pieces with that number
	   They are not prompted to select a piece
	*/
	int again = 0;
	if(num == 6){
		again = 1;
	}
	wmove(this->win, 0, 0);
        wclrtoeol(this->win);
        wprintw(this->win, "Player %d's turn", player); // Notify who's turn it is
	wmove(this->win, 1, 0);
	wclrtoeol(this->win);
	wprintw(this->win, "You rolled a %d", num);
	wrefresh(this->win);
	int piece = 0;
	vector<int> movePiece;
	movePiece.push_back(piece);
	movePiece.push_back(num);
	bool valid = false;
	while(!valid){
		movePiece[0] = getPiece();
		bool validMove = aggravationGame->validMove(b, movePiece, player);
		if(!validMove){
			wmove(this->win, 1, 0);
                        wclrtoeol(this->win);
			if(num != 0){
	                        wprintw(this->win, "Cannot move piece %d by %d", movePiece[0], movePiece[1]);
			}
                        wmove(this->win, 2, 0);
                        wclrtoeol(this->win);
                        wprintw(this->win, "Hit enter to choose again");
                        wrefresh(this->win);
                        wgetch(this->win);
			wmove(this->win, 1, 0);
			wclrtoeol(this->win);
			wprintw(this->win, "You rolled a %d", num);
			wrefresh(this->win);
		}
		else{
			valid = true;
		}
	}
	movePiece.push_back(again); 

	/* debugging lines:
        wmove(this->win,1,0);
        wclrtoeol(this->win);
        wprintw(this->win, "You chose piece %d to move by %d", movePiece[0], movePiece[1]);
        wmove(this->win,2,0);
        wclrtoeol(this->win);
	if(movePiece[2] == 0){
		wprintw(this->win, "You do not get another turn");
	}
	else{
		wprintw(this->win, "You get another turn");
	}
        wrefresh(this->win);
        wgetch(this->win);
        */ // end debugging lines
	
	return movePiece; // 0 = piece chosen to move; 1 = number of spaces it must move; 2 = if player gets to go again
}

vector<int> input::Input::pieceChoice(int game, board::SorryBoard * b, sorry::Sorry * sorryGame, int player, int num){
	int again = 0;
	if(num == 2){
		again = 1;
	}
	wmove(this->win, 0, 0);
        wclrtoeol(this->win);
        wprintw(this->win, "Player %d's turn", player); // Notify who's turn it is
	wmove(this->win, 1, 0);
	wclrtoeol(this->win);
	if(num == 0){
		wprintw(this->win, "You drew a Sorry! card");
	}
	else{
		wprintw(this->win, "You drew a %d", num);
	}
	wrefresh(this->win);
	int piece = 0;
	vector<int> movePiece;
	movePiece.push_back(piece);
	movePiece.push_back(num);
	bool valid = false;
	while(!valid){
		if(num != 0){
			movePiece[0] = getPiece();
			bool validMove = sorryGame->validMove(b, movePiece, player);
			if(!validMove){
				wmove(this->win, 1, 0);
		                wclrtoeol(this->win);
			        wprintw(this->win, "Cannot move piece %d by %d", movePiece[0], movePiece[1]);
		                wmove(this->win, 2, 0);
		                wclrtoeol(this->win);
		                wprintw(this->win, "Hit enter to choose again");
		                wrefresh(this->win);
		                wgetch(this->win);
				wmove(this->win, 1, 0);
				wclrtoeol(this->win);
				wprintw(this->win, "You drew a %d", num);
				wrefresh(this->win);
			}
			else{
				valid = true;
			}
		}
		else{
			// TODO Sorry! card has different logic than the rest of them, put it here
		}
	}
	movePiece.push_back(again);
	return movePiece;
}
