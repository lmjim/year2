#include <iostream>
#include <ncurses.h>
#include "board.hpp"
#include "input.hpp"
#include "randMove.hpp"
#include "aggravation.hpp"

using namespace std;
using namespace aggravation;

void Aggravation::checkColor(){
        // Check if user's terminal supports color
        if(!has_colors()){
                printw("No color! Can't continue :(");
                move(1,0);
                printw("Hit enter to exit");
                refresh();
                getch();
                endwin();
                exit(1);
        }
        start_color();
}

void Aggravation::startBoard(board::AggravationBoard * b){
	// Put pieces at their starting positions
	for(int j = 0; j < 4; j++){
                int i = j + 1;
                b->setPieceAt(vector<int>{i, i}, vector<int>{1, j+1});
                b->setPieceAt(vector<int>{14-i, i}, vector<int>{2, j+1});
                b->setPieceAt(vector<int>{14-i, 14-i}, vector<int>{3, j+1});
                b->setPieceAt(vector<int>{i, 14-i}, vector<int>{4, j+1});
	}
	b->displayBoard();
        b->showScreen();
	return;
}

int Aggravation::getPieceLoc(board::AggravationBoard * b, int piece, int player){
        int pieceLoc = -1; // index in locations for piece
        if(player == 1){
                pieceLoc = piece - 1;
        }
        else if(player == 2){
                pieceLoc = 3 + piece;
        }
        else if(player == 3){
                pieceLoc = 7 + piece;
        }
        else{
                pieceLoc = 11 + piece;
        }
        return pieceLoc;
}

bool Aggravation::withinHomeValid(board::AggravationBoard * b, int fromSpot, int num, int player){
	bool free = false;
	int move = fromSpot+num;
	if(player == 1){
		if(move < 77){
			if(b->getPieceAt(this->positions[move])[0] == 0){
				free = true;
			}
		}
	}
	else if(player == 2){
		if(move < 81){
                        if(b->getPieceAt(this->positions[move])[0] == 0){
                                free = true;
                        }
                }
	}
	else if(player == 3){
		if(move < 85){
                        if(b->getPieceAt(this->positions[move])[0] == 0){
                                free = true;
                        }
                }
	}
	else if(player == 4){
		if(move < 89){
                        if(b->getPieceAt(this->positions[move])[0] == 0){
                                free = true;
                        }
                }
	}
	return free;
}

bool Aggravation::startAvailable(board::AggravationBoard * b, int player){
	bool free = false;
	if(player == 1){
		if(b->getPieceAt(this->positions[1])[0] != 1){
			free = true;
		}
	}
	else if(player == 2){
		if(b->getPieceAt(this->positions[15])[0] != 2){
			free = true;
		}
	}
	else if(player == 3){
		if(b->getPieceAt(this->positions[29])[0] != 3){
			free = true;
		}
	}
	else if(player == 4){
		if(b->getPieceAt(this->positions[43])[0] != 4){
			free = true;
		}
	}
	return free;
}

bool Aggravation::centerExitAvailable(board::AggravationBoard * b, int player){
	bool free = false;
        if(player == 1){
                if(b->getPieceAt(this->positions[48])[0] != 1){
                        free = true;
                }
        }
        else if(player == 2){
                if(b->getPieceAt(this->positions[6])[0] != 2){
                        free = true;
                }
        }
        else if(player == 3){
                if(b->getPieceAt(this->positions[20])[0] != 3){
                        free = true;
                }
        }
        else if(player == 4){
                if(b->getPieceAt(this->positions[34])[0] != 4){
                        free = true;
                }
        }
        return free;
}

bool Aggravation::validLoopMove(board::AggravationBoard * b, int fromSpot, int num, int player){
	bool free = false;
	if(player == 1){
		if(fromSpot == 48){
			if(b->getPieceAt(this->positions[48+num])[0] != 1){
				free = true;
			}
		}
		else if(fromSpot == 34){
			if(b->getPieceAt(this->positions[48+num-1])[0] != 1){
				free = true;
			}
		}
		else if(fromSpot == 20){
			if(num == 1){
				if(b->getPieceAt(this->positions[34])[0] != 1){
					free = true;
				}
			}
			else{
				if(b->getPieceAt(this->positions[48+num-2])[0] != 1){
					free = true;
				}
			}
		}
		else if(fromSpot == 6){
			if(num == 1){
				if(b->getPieceAt(this->positions[20])[0] != 1){
					free = true;
				}
			}
			else if(num == 2){
				if(b->getPieceAt(this->positions[34])[0] != 1){
					free = true;
				}
			}
			else{
				if(b->getPieceAt(this->positions[48+num-3])[0] != 1){
					free = true;
				}
			}
		}
	}
	else if(player == 2){
		if(fromSpot == 6){
                        if(b->getPieceAt(this->positions[6+num])[0] != 2){
                                free = true;
                        }
                }
                else if(fromSpot == 48){
                        if(b->getPieceAt(this->positions[6+num-1])[0] != 2){
                                free = true;
                        }
                }
                else if(fromSpot == 34){
                        if(num == 1){
                                if(b->getPieceAt(this->positions[48])[0] != 2){
                                        free = true;
                                }
                        }
                        else{
                                if(b->getPieceAt(this->positions[6+num-2])[0] != 2){
                                        free = true;
                                }
                        }
                }
                else if(fromSpot == 20){
                        if(num == 1){
                                if(b->getPieceAt(this->positions[34])[0] != 2){
                                        free = true;
                                }
                        }
                        else if(num == 2){
                                if(b->getPieceAt(this->positions[48])[0] != 2){
                                        free = true;
                                }
                        }
                        else{
                                if(b->getPieceAt(this->positions[6+num-3])[0] != 2){
                                        free = true;
                                }
                        }
                }
	}
	else if(player == 3){
		if(fromSpot == 20){
                        if(b->getPieceAt(this->positions[20+num])[0] != 3){
                                free = true;
                        }
                }
                else if(fromSpot == 6){
                        if(b->getPieceAt(this->positions[20+num-1])[0] != 3){
                                free = true;
                        }
                }
                else if(fromSpot == 48){
                        if(num == 1){
                                if(b->getPieceAt(this->positions[6])[0] != 3){
                                        free = true;
                                }
                        }
                        else{
                                if(b->getPieceAt(this->positions[20+num-2])[0] != 3){
                                        free = true;
                                }
                        }
                }
                else if(fromSpot == 34){
                        if(num == 1){
                                if(b->getPieceAt(this->positions[48])[0] != 3){
                                        free = true;
                                }
                        }
                        else if(num == 2){
                                if(b->getPieceAt(this->positions[6])[0] != 3){
                                        free = true;
                                }
                        }
                        else{
                                if(b->getPieceAt(this->positions[20+num-3])[0] != 3){
                                        free = true;
                                }
                        }
                }
	}
	else if(player == 4){
		if(fromSpot == 34){
                        if(b->getPieceAt(this->positions[34+num])[0] != 4){
                                free = true;
                        }
                }
                else if(fromSpot == 20){
                        if(b->getPieceAt(this->positions[34+num-1])[0] != 4){
                                free = true;
                        }
                }
                else if(fromSpot == 6){
                        if(num == 1){
                                if(b->getPieceAt(this->positions[20])[0] != 4){
                                        free = true;
                                }
                        }
                        else{
                                if(b->getPieceAt(this->positions[34+num-2])[0] != 4){
                                        free = true;
                                }
                        }
                }
                else if(fromSpot == 48){
                        if(num == 1){
                                if(b->getPieceAt(this->positions[6])[0] != 4){
                                        free = true;
                                }
                        }
                        else if(num == 2){
                                if(b->getPieceAt(this->positions[20])[0] != 4){
                                        free = true;
                                }
                        }
                        else{
                                if(b->getPieceAt(this->positions[34+num-3])[0] != 4){
                                        free = true;
                                }
                        }
                }
	}
	return free;
}

bool Aggravation::enterHomeValid(board::AggravationBoard * b, int fromSpot, int num, int player){
	bool free = false;
	int inHome = 0;
	if(player == 1){
		inHome = fromSpot + num - 55;
		if(inHome <= 4){
			if(b->getPieceAt(this->positions[72+inHome])[0] == 0){
				free = true;
			}
		}
	}
	else if(player == 2){
		inHome = fromSpot + num - 13;
		if(inHome <= 4){
                        if(b->getPieceAt(this->positions[76+inHome])[0] == 0){
                                free = true;
                        }
                }
	}
	else if(player == 3){
		inHome = fromSpot + num - 27;
		if(inHome <= 4){
                        if(b->getPieceAt(this->positions[80+inHome])[0] == 0){
                                free = true;
                        }
                }
	}
	else if(player == 4){
		inHome = fromSpot + num - 41;
		if(inHome <= 4){
                        if(b->getPieceAt(this->positions[84+inHome])[0] == 0){
                                free = true;
                        }
                }
	}
	return free;
}

bool Aggravation::validMove(board::AggravationBoard * b, vector<int> movePiece, int player){
	// movePiece vector = {piece chose, num of spaces to move}
	int pieceLoc = getPieceLoc(b, movePiece[0], player);
	int fromSpot = this->locations[pieceLoc];
	int num = movePiece[1];
	if(fromSpot > 72){
		// piece is within home
		if(!withinHomeValid(b, fromSpot, num, player)){
			return false;
		}
	}
	else if(fromSpot > 56){
		// piece is in base
		if(num != 1 && num != 6){
			// need a 1 or 6 to exit base
			return false;
		}
		if(!startAvailable(b, player)){
			return false;
		}
	}
	else if(fromSpot == 0){
		// piece in center
		if(num != 1){
			return false;
		}
		if(!centerExitAvailable(b, player)){
			return false;
		}
	}
	else if(fromSpot == 6 || fromSpot == 20 || fromSpot == 34 || fromSpot == 48){
		// piece on loop
		if(!validLoopMove(b, fromSpot, num, player)){
			return false;
		}
	}
	else if((player == 1 && (fromSpot <= 55 && fromSpot+num > 55)) || (player == 2 && (fromSpot <= 13 && fromSpot+num > 13)) || (player == 3 && (fromSpot <= 27 && fromSpot+num > 27)) || (player == 4 && (fromSpot <= 41 && fromSpot+num > 41))){
		// piece is in range of home
		if(!enterHomeValid(b, fromSpot, num, player)){
			return false;
		}
	}
	else if(fromSpot+num == 7 || fromSpot+num == 21 || fromSpot+num == 35 || fromSpot+num == 49){
		// piece could move into center
		int normSpot = b->getPieceAt(this->positions[fromSpot+num])[0];
		int center = b->getPieceAt(this->positions[0])[0];
		if(normSpot == player && center == player){
			return false;
		}
	}
	else if(fromSpot+num > 56){
		// piece continues normally (spot 56 -> spot 1)
		if(b->getPieceAt(this->positions[fromSpot+num-56])[0] == player){
                        return false;
                }
	}
	else{
		// piece continues normally
		if(b->getPieceAt(this->positions[fromSpot+num])[0] == player){
			return false;
		}
	}
	return true; // passed all false cases
}

bool Aggravation::canMove(board::AggravationBoard * b, int roll, int player){
	bool canMove = false;
	if(validMove(b, vector<int>{1,roll}, player) || validMove(b, vector<int>{2,roll}, player) || validMove(b, vector<int>{3,roll}, player) || validMove(b, vector<int>{4,roll}, player)){
		canMove = true;
	}
	return canMove;
}

bool Aggravation::wantToMoveToCenter(WINDOW * w){
	// ask player if they want to move to center
	wmove(w, 3, 0);
	wclrtoeol(w);
	wprintw(w, "Would you like to move the piece into the center (y/n)? ");
	wrefresh(w);
	bool center = false;
	bool valid = false;
        while(!valid){
                char cstr[10]; // c string for curses input
                wgetstr(w, cstr); // get user input
                string input(cstr); // convert c string to c++ string
                if(input.find_first_not_of("yn") != string::npos || input.empty() || input.size() != 1){
                        wmove(w, 3, 0);
                        wclrtoeol(w);
                        wprintw(w, "Invalid entry. Would you like to move the piece into the center (y/n)? ");
                        wrefresh(w);
                }
                else{
                        char choice = cstr[0];
                        if(choice == 'y'){
				center = true;
                        }
			valid = true;
			wmove(w, 3, 0);
                        wclrtoeol(w);
			wrefresh(w);
                }
        }
	return center;
}

int Aggravation::getToSpot(board::AggravationBoard * b, WINDOW * w, int pieceLoc, int num, int player){
	int fromSpot = this->locations[pieceLoc];
	int toSpot = -1;
	if(fromSpot > 72){
		// piece is within home
		toSpot = fromSpot + num;
	}
	else if(fromSpot > 56){
		// piece is in base
		if(player == 1){
			toSpot = 1;
		}
		else if(player == 2){
			toSpot = 15;
		}
		else if(player == 3){
			toSpot = 29;
		}
		else if(player == 4){
			toSpot = 43;
		}
	}
	else if(fromSpot == 0){
		// piece in center
		if(player == 1){
	                toSpot = 48;
	        }
	        else if(player == 2){
	                toSpot = 6;
	        }
	        else if(player == 3){
	                toSpot = 20;
	        }
	        else if(player == 4){
	                toSpot = 34;
	        }
	}
	else if(fromSpot == 6 || fromSpot == 20 || fromSpot == 34 || fromSpot == 48){
		// piece on loop
		if(player == 1){
			if(fromSpot == 48){toSpot = 48+num;}
			else if(fromSpot == 34){toSpot = 48+num-1;}
			else if(fromSpot == 20){
				if(num == 1){toSpot = 34;}
				else{toSpot = 48+num-2;}
			}
			else if(fromSpot == 6){
				if(num == 1){toSpot = 20;}
				else if(num == 2){toSpot = 34;}
				else{toSpot = 48+num-3;}
			}
		}
		else if(player == 2){
			if(fromSpot == 6){toSpot = 6+num;}
		        else if(fromSpot == 48){toSpot = 6+num-1;}
		        else if(fromSpot == 34){
		                if(num == 1){toSpot = 48;}
		                else{toSpot = 6+num-2;}
		        }
		        else if(fromSpot == 20){
		                if(num == 1){toSpot = 34;}
		                else if(num == 2){toSpot = 48;}
		                else{toSpot = 6+num-3;}
		        }
		}
		else if(player == 3){
			if(fromSpot == 20){toSpot = 20+num;}
		        else if(fromSpot == 6){toSpot = 20+num-1;}
		        else if(fromSpot == 48){
		                if(num == 1){toSpot = 6;}
		                else{toSpot = 20+num-2;}
		        }
		        else if(fromSpot == 34){
		                if(num == 1){toSpot = 48;}
		                else if(num == 2){toSpot = 6;}
		                else{toSpot = 20+num-3;}
		        }
		}
		else if(player == 4){
			if(fromSpot == 34){toSpot = 34+num;}
		        else if(fromSpot == 20){toSpot = 34+num-1;}
		        else if(fromSpot == 6){
		                if(num == 1){toSpot = 20;}
		                else{toSpot = 34+num-2;}
		        }
		        else if(fromSpot == 48){
		                if(num == 1){toSpot = 6;}
		                else if(num == 2){toSpot = 20;}
		                else{toSpot = 34+num-3;}
		        }
		}
	}
	else if((player == 1 && (fromSpot <= 55 && fromSpot+num > 55)) || (player == 2 && (fromSpot <= 13 && fromSpot+num > 13)) || (player == 3 && (fromSpot <= 27 && fromSpot+num > 27)) || (player == 4 && (fromSpot <= 41 && fromSpot+num > 41))){
		// piece is in range of home
		int inHome = 0;
		if(player == 1){
			inHome = fromSpot + num - 55;
			toSpot = 72 + inHome;
		}
		else if(player == 2){
			inHome = fromSpot + num - 13;
			toSpot = 76 + inHome;
		}
		else if(player == 3){
			inHome = fromSpot + num - 27;
			toSpot = 80 + inHome;
		}
		else if(player == 4){
			inHome = fromSpot + num - 41;
			toSpot = 84 + inHome;
		}
	}
	else if(fromSpot+num == 7 || fromSpot+num == 21 || fromSpot+num == 35 || fromSpot+num == 49){
		// piece could move into center
		// Check if it can go in center/if it must go in center
		// If it can go either way, prompt player for choice
		int normSpot = b->getPieceAt(this->positions[fromSpot+num])[0];
		int center = b->getPieceAt(this->positions[0])[0];
		if(normSpot != player && center != player){
			if(wantToMoveToCenter(w)){
				toSpot = 0;
			}
			else{
				toSpot = fromSpot + num;
			}
		}
		else if(normSpot == player && center != player){
			toSpot = 0;
		}
		else if(normSpot != player && center == player){
			toSpot = fromSpot + num;
		}
	}
	else if(fromSpot+num > 56){
		// piece continues normally (spot 56 -> spot 1)
		toSpot = fromSpot + num - 56;
	}
	else{
		// piece continues normally
		toSpot = fromSpot + num;
	}
	return toSpot;
}

void Aggravation::pieceMove(board::AggravationBoard * b, int pieceLoc, int toSpot){
	vector<int> pieceAt = b->getPieceAt(this->positions[toSpot]);
	if(pieceAt[0] == 1){
		if(pieceAt[1] == 1){
			b->movePiece(this->positions[toSpot], this->positions[57]);
			this->locations[0] = 57;
		}
		else if(pieceAt[1] == 2){
                        b->movePiece(this->positions[toSpot], this->positions[58]);
                        this->locations[1] = 58;
                }
		else if(pieceAt[1] == 3){
                        b->movePiece(this->positions[toSpot], this->positions[59]);
                        this->locations[2] = 59;
                }
		else if(pieceAt[1] == 4){
                        b->movePiece(this->positions[toSpot], this->positions[60]);
                        this->locations[3] = 60;
                }
	}
	else if(pieceAt[0] == 2){
		if(pieceAt[1] == 1){
                        b->movePiece(this->positions[toSpot], this->positions[61]);
                        this->locations[4] = 61;
                }
                else if(pieceAt[1] == 2){
                        b->movePiece(this->positions[toSpot], this->positions[62]);
                        this->locations[5] = 62;
                }
                else if(pieceAt[1] == 3){
                        b->movePiece(this->positions[toSpot], this->positions[63]);
                        this->locations[6] = 63;
                }
                else if(pieceAt[1] == 4){
                        b->movePiece(this->positions[toSpot], this->positions[64]);
                        this->locations[7] = 64;
                }
	}
	else if(pieceAt[0] == 3){
		if(pieceAt[1] == 1){
                        b->movePiece(this->positions[toSpot], this->positions[65]);
                        this->locations[8] = 65;
                }
                else if(pieceAt[1] == 2){
                        b->movePiece(this->positions[toSpot], this->positions[66]);
                        this->locations[9] = 66;
                }
                else if(pieceAt[1] == 3){
                        b->movePiece(this->positions[toSpot], this->positions[67]);
                        this->locations[10] = 67;
                }
                else if(pieceAt[1] == 4){
                        b->movePiece(this->positions[toSpot], this->positions[68]);
                        this->locations[11] = 68;
                }
	}
	else if(pieceAt[0] == 4){
		if(pieceAt[1] == 1){
                        b->movePiece(this->positions[toSpot], this->positions[69]);
                        this->locations[12] = 69;
                }
                else if(pieceAt[1] == 2){
                        b->movePiece(this->positions[toSpot], this->positions[70]);
                        this->locations[13] = 70;
                }
                else if(pieceAt[1] == 3){
                        b->movePiece(this->positions[toSpot], this->positions[71]);
                        this->locations[14] = 71;
                }
                else if(pieceAt[1] == 4){
                        b->movePiece(this->positions[toSpot], this->positions[72]);
                        this->locations[15] = 72;
                }
	}

	int fromSpot = this->locations[pieceLoc];
	b->movePiece(this->positions[fromSpot], this->positions[toSpot]);
	this->locations[pieceLoc] = toSpot;
	b->displayBoard();
	b->showScreen();
	return;
}

bool Aggravation::active(){
	int p1 = 0;
	int p2 = 0;
	int p3 = 0;
	int p4 = 0;
	for(int i=0; i < 16; i++){
		if(this->locations[i] > 72){
			// all spots above 72 indicate a player's home spot
			if(i<4){p1++;}
			else if(i<8){p2++;}
			else if(i<12){p3++;}
			else if(i<16){p4++;}
		}
	}
	bool active = true;
	if(p1 == 4 || p2 == 4 || p3 == 4 || p4 == 4){
		active = false;
	}
	return active;
}

void Aggravation::endGame(WINDOW * w){
	int p1 = 0;
        int p2 = 0;
        int p3 = 0;
        int p4 = 0;
        for(int i=0; i < 16; i++){
                if(this->locations[i] > 72){
                        // all spots above 72 indicate a player's home spot
                        if(i<4){p1++;}
                        else if(i<8){p2++;}
                        else if(i<12){p3++;}
                        else if(i<16){p4++;}
                }
        }
	wclear(w);
	mvwprintw(w, 0, 0, "Game Over");
	if(p1 == 4){
		mvwprintw(w, 1, 0, "Player 1 won!");
	}
	else if(p2 == 4){
		mvwprintw(w, 1, 0, "Player 2 won!");
	}
	else if(p3 == 4){
		mvwprintw(w, 1, 0, "Player 3 won!");
	}
	else if(p4 == 4){
		mvwprintw(w, 1, 0, "Player 4 won!");
	}
	mvwprintw(w, 2, 0, "Hit enter to exit");
	wrefresh(w);
	wgetch(w);
	return;
}

void Aggravation::runAggravation(){
	// Start ncurses
        initscr();
        // Hide cursor
        curs_set(0);
        // Check if user's terminal supports color
        checkColor();
        // Start Board
        board::AggravationBoard b;
	startBoard(&b);
	// Start IO
        input::Input i;
        i.setWin(); // Start IO window
        WINDOW * w = i.getWin();
	// Access to dice roll function
	randMove::RandMove r;

	// Run the game
	int again;
	int roll;
	vector<int> choice;
	int pieceLoc;
	int toSpot;
	while(active()){
		// player 1 turn
		again = 1;
		while(again){
			roll = r.diceRoll();
			if(canMove(&b, roll, 1)){
				choice = i.pieceChoice(4, &b, this, 1, roll);
				pieceLoc = getPieceLoc(&b, choice[0], 1);
				toSpot = getToSpot(&b, w, pieceLoc, choice[1], 1); 
				pieceMove(&b, pieceLoc, toSpot);
				again = choice[2];
			}
			else{
				wclear(w);
				mvwprintw(w, 0, 0, "Player 1's turn");
				mvwprintw(w, 1, 0, "You rolled a %d", roll);
				mvwprintw(w, 2, 0, "No moves to make. Hit enter to continue");
				wrefresh(w);
				wgetch(w);
				if(roll != 6){
					again = 0;
				}
			}
			if(!active()){break;}
		}

		// check if active
		if(!active()){break;}

		// player 2 turn
		again = 1;
                while(again){
                        roll = r.diceRoll();
                        if(canMove(&b, roll, 2)){
				wmove(w, 3, 0);
				wclrtoeol(w);
                                choice = i.pieceChoice(4, &b, this, 2, roll);
                                pieceLoc = getPieceLoc(&b, choice[0], 2);
                                toSpot = getToSpot(&b, w, pieceLoc, choice[1], 2);
                                pieceMove(&b, pieceLoc, toSpot);
                                again = choice[2];
                        }
                        else{
                                wclear(w);
                                mvwprintw(w, 0, 0, "Player 2's turn");
                                mvwprintw(w, 1, 0, "You rolled a %d", roll);
                                mvwprintw(w, 2, 0, "No moves to make. Hit enter to continue");
                                wrefresh(w);
                                wgetch(w);
                                if(roll != 6){
                                        again = 0;
                                }
                        }
                        if(!active()){break;}
                }

		// check if active
		if(!active()){break;}

		// player 3 turn
		again = 1;
                while(again){
                        roll = r.diceRoll();
                        if(canMove(&b, roll, 3)){
                                choice = i.pieceChoice(4, &b, this, 3, roll);
                                pieceLoc = getPieceLoc(&b, choice[0], 3);
                                toSpot = getToSpot(&b, w, pieceLoc, choice[1], 3);
                                pieceMove(&b, pieceLoc, toSpot);
                                again = choice[2];
                        }
                        else{
                                wclear(w);
                                mvwprintw(w, 0, 0, "Player 3's turn");
                                mvwprintw(w, 1, 0, "You rolled a %d", roll);
                                mvwprintw(w, 2, 0, "No moves to make. Hit enter to continue");
                                wrefresh(w);
                                wgetch(w);
                                if(roll != 6){
                                        again = 0;
                                }
                        }
                        if(!active()){break;}
                }

		// check if active
		if(!active()){break;}

		// player 4 turn
		again = 1;
                while(again){
                        roll = r.diceRoll();
                        if(canMove(&b, roll, 4)){
                                choice = i.pieceChoice(4, &b, this, 4, roll);
                                pieceLoc = getPieceLoc(&b, choice[0], 4);
                                toSpot = getToSpot(&b, w, pieceLoc, choice[1], 4);
                                pieceMove(&b, pieceLoc, toSpot);
                                again = choice[2];
                        }
                        else{
                                wclear(w);
                                mvwprintw(w, 0, 0, "Player 4's turn");
                                mvwprintw(w, 1, 0, "You rolled a %d", roll);
                                mvwprintw(w, 2, 0, "No moves to make. Hit enter to continue");
                                wrefresh(w);
                                wgetch(w);
                                if(roll != 6){
                                        again = 0;
                                }
                        }
                        if(!active()){break;}
                }

		// loop checks if active
	}
	endGame(w); // Print winner and prompt to close game
	
	/* debugging for moving pieces
	wclear(w);
	mvwprintw(w, 0, 0, "Player 1 piece 2 is at location: %d", this->locations[1]);
	mvwprintw(w, 1, 0, "That location is position: %d, %d", this->positions[this->locations[1]][0], this->positions[this->locations[1]][1]);
	mvwprintw(w, 2, 0, "Hit enter to continue");
	wrefresh(w);
	wgetch(w);

	pieceMove(&b, 1, 1);
	b.displayBoard();
	b.showScreen();
	wclear(w);
        mvwprintw(w, 0, 0, "Player 1 piece 2 is at location: %d", this->locations[1]);
        mvwprintw(w, 1, 0, "That location is position: %d, %d", this->positions[this->locations[1]][0], this->positions[this->locations[1]][1]);
        mvwprintw(w, 2, 0, "Hit enter to continue");
        wrefresh(w);
        wgetch(w);
	*/ // end debugging
	
	endwin();
	return;
}
