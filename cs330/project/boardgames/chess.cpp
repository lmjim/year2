#include <iostream>
#include <vector>
#include <ncurses.h>
#include "chess.hpp"
#include "input.hpp"
#include <iostream>
#include <string>
#include <algorithm>
// TODO

using namespace std;
using namespace chess;

template <typename T>
static void printDebug(const vector<T>& args){}



vector<int> Chess::findKing(board::Board * b, int side){
	//side 1 == player 1, side 2 == player 2
	/*
		Search all valid chessboard positions to find the king pawn
	*/
	for(int x = 0; x < 8; x++){
		for(int y = 0; y < 8; y++){
			if(b->getPieceAt(vector<int>{x,y}).at(0) == side && (b->getPieceAt(vector<int>{x,y}).at(1) == 0 ||b->getPieceAt(vector<int>{x,y}).at(1) == -1)){
				/*
					Test to see if the piece at the position is:
						a) of the same side we are searching for (which is the first argument)
						b) of type 0 (king).
					Because the shortcircuiting nature of if statements, the second is only
					evaluated if the former is true, so we don't end up with issues with vector
					containing only 1 element.
					
				*/
				return vector<int>{x,y};
			}
		}
	}
	return vector<int>{-1,-1}; // Return -1,-1 if it doesn't exist.
}

bool Chess::anyValidMoves(board::Board * b, int side){
	//Determine all possible moves that will allow us to do something. If something
	// can be done without causing the issue of not having a king exposed...well then we good.
	for(int x = 0; x < 8; x++){
		for(int y = 0; y < 8; y++){
			if(b->getPieceAt(vector<int>{x,y}).at(0) == side){
				// Determine if the piece belows to us, then get all possible actions for that
				// 		piece. If there is a SINGLE move that is declared valid, return true.
				vector<vector<int> > amoves = this->getAllAttackableTiles(b, vector<int>{x,y}, side);
				for(auto i = amoves.begin(); i != amoves.end(); i++){
					
					if(this->validMove(b, vector<int>{x,y,(*i).at(0), (*i).at(1)}, side)){
						return true;
					}
				}
			}
		}
	}
	return false; //Otherwise return false as it is a checkmate...
	
}
	
// Checks to see if the move is valid.
bool Chess::validMove(board::Board * b, vector<int> args, int side){
	//args: PAWNX, PAWNY, TOX, TOY
	// Get all the attackable tiles from the piece's perspective.
	vector<vector<int> > allowed = this->getAllAttackableTiles(b, vector<int>{args.at(0), args.at(1)}, side);
	bool xk = false;
	for(auto i = allowed.begin(); i != allowed.end(); i++){
		if(!xk && (*i).at(0) == args.at(2) && (*i).at(1) == args.at(3)){
			// See if the proposed move is valid.
			xk = true;
			break;
		}
	}
	if(xk == false){
		// If there isn't any valid moves, return false.
		return false;
	}
	vector<int> swapped = b->getPieceAt(vector<int>{args.at(2), args.at(3)});
	
	b->movePiece(vector<int>{args.at(0),args.at(1)},vector<int>{args.at(2),args.at(3)});
	// Move (and replace) the piece [do the attack]
	bool rts = false; 
	if(this->isKingVun(b, side)){
		// This would leave the king exposed! Not a valid move.
		rts = false;
	}else{
		// A valid move.
		rts = true;
	}
	// Reset the board so no side effects occur
	b->setPieceAt(vector<int>{args.at(0), args.at(1)}, swapped);
	b->swapPieces(vector<int>{args.at(0),args.at(1)},vector<int>{args.at(2),args.at(3)});
	return rts;
}

// Determines if the king is vunerable with a current board state
bool Chess::isKingVun(board::Board * b, int side){
	vector<int> getKing = this->findKing(b, side); // find the king
	if(getKing.at(0) == -1){
		return true; // The king is dead...so yeah, it is vunerable.
	}
	int anti = (side == 1 ? 2 : 1);
	//Search all enemy pawns
	for(int x = 0; x < 8; x++){
		for(int y = 0; y < 8; y++){
			if(b->getPieceAt(vector<int>{x,y}).at(0) == anti){
				auto ab = this->getAllAttackableTiles(b, vector<int>{x,y}, anti);
				// Get all attackable tiles from this pawn
				for(auto i = ab.begin(); i != ab.end(); i++){
					if(i->at(0) == getKing.at(0) && i->at(1) == getKing.at(1)){
						// If the king is at this attackable tile, then it is vunerable.
						return true;
					}
				}
			}
		}
	}
	// Not vunerable.
	return false;
}

// This check will see if the parameters are with in the boards size. (Don't index out of range)
bool Chess::safeTileCheck(board::Board * b, vector<int> check){
	return !(check.at(0) < 0 || check.at(1) < 0 || check.at(0) >= 8 || check.at(1) >= 8);
}

// Takes a pawn and finds all possible positions that could be attacked by this piece.
vector<vector<int> > Chess::getAllAttackableTiles(board::Board * b, vector<int> args, int side, bool recurse){
	if(b->getPieceAt(vector<int>{args.at(0), args.at(1)}).size() <= 1){
		return vector<vector<int> >{}; // Not a pawn, hence no attackable positions.
	}
	int type = b->getPieceAt(vector<int>{args.at(0), args.at(1)}).at(1); // Type of pawn
	vector<vector<int> > bb; // Attackable positions
	vector<vector<int> > horses{{1,2}, {2,1}, {-1,2}, {-2,1}, {1,-2},{2,-1}, {-1,-2}, {-2,-1}}; // hardcoded horses positions
	switch(type){
	case -1: 
	// Potential Castlable king... Falls out to the next case. The KING must do the castling move...
	{
		if(recurse){
			int anti = (side == 1 ? 2 : 1);
			//Search all enemy pawns
			bool left = true;
			bool right = true;
			
			//pre-process the kings ability to castle
			left = b->getPieceAt(vector<int>{0, args.at(1)}).at(0) == side && b->getPieceAt(vector<int>{0, args.at(1)}).at(1) == 7;
			right = b->getPieceAt(vector<int>{7, args.at(1)}).at(0) == side && b->getPieceAt(vector<int>{7, args.at(1)}).at(1) == 7;
			
			if(left == right && !left){
				//straight up just convert this king..
				b->setPieceAt(vector<int>{args.at(0), args.at(1)}, vector<int>{side, 0});
			}else{
				
				for(int x = 0; x < 8; x++){
					for(int y = 0; y < 8; y++){
						if(b->getPieceAt(vector<int>{x,y}).at(0) == anti){
							if(left == false && left == right){
								continue;
							}
							auto ab = this->getAllAttackableTiles(b, vector<int>{x,y}, anti, false);
							// Get all attackable tiles from this pawn
							for(auto i = ab.begin(); i != ab.end(); i++){
								if(i->at(0) == args.at(0) && i->at(1) == args.at(1)){
									// King is currently in check
									left = false;
									right = false;
									break;
								}
								// determine if something is in the space to castle.
								if(i->at(0) == args.at(0) - 1 && i->at(1) == args.at(1)){
									left = false;
								}
								if(i->at(0) == args.at(0) - 2 && i->at(1) == args.at(1)){
									left = false;
								}
								if(i->at(0) == args.at(0) + 2 && i->at(1) == args.at(1)){
									right = false;
								}
								if(i->at(0) == args.at(0) + 1 && i->at(1) == args.at(1)){
									right = false;
								}
							}
							
						}
					}
				}
			}
			// If left or right castling is allowed, add it to possible moves
			if(left){
				bb.push_back(vector<int>{args.at(0) - 2, args.at(1)});
			}
			if(right){
				bb.push_back(vector<int>{args.at(0) + 2, args.at(1)});
			}
		}
	}
	case 0: 
	// King moving
		for(int x = -1; x <= 1; x++){
			for(int y = -1; y <= 1; y++){
				if(x==y && x == 0){continue;} // Has to move, not allowed a "nothing" move.
				if(this->safeTileCheck(b, vector<int>{x+args.at(0),y+args.at(1)})){
					if(b->getPieceAt(vector<int>{x+args.at(0), y+args.at(1)}).at(0) != side ){
						bb.push_back(vector<int>{x+args.at(0), y+args.at(1)});
						// Can attack/move to any position not occupied by the same side
						// Castling done above
					}
				}
			}
		}
		break;
	case 1: 
	// Queen
		//literally sweep until first interference
		for(int x = -1; x <= 1; x++){
			for(int y = -1; y <= 1; y++){
				if(x==y && x == 0){continue;} // Ignore the 'staying still' case.
				for(int d = 1; d < 9; d++){// Go along the path until the first hit.
					if(this->safeTileCheck(b, vector<int>{d*x+args.at(0),d*y+args.at(1)})){
						if(b->getPieceAt(vector<int>{d*x+args.at(0), d*y+args.at(1)}).at(0) != side ){
							bb.push_back(vector<int>{d*x+args.at(0), d*y+args.at(1)});
							//However, if the tile is OWNED by the other side, that is the furtherest we can go.
							if(b->getPieceAt(vector<int>{d*x+args.at(0), d*y+args.at(1)}).at(0) != 0 ){
								break;
							}
						}else{
							break; // Occupied by our own piece
						}
					}else{
						break; // Outside the board, so stop checking along this line.
					}
				}
			}
		}
		break;
	case 7: 
	// Castleable rook...falls through.
		;
	case 3: 
	// Rook
		for(int x = -1; x <= 1; x++){
			for(int y = -1; y <= 1; y++){
				if(x && y || (x == 0 && y == 0)){continue;} // If a value is not equal to 0, then it is true, so if x and y are not 0, (or x = y = 0), then we don't search that path.
				for(int d = 1; d < 9; d++){// Go along the path until the first hit.
					if(this->safeTileCheck(b, vector<int>{d*x+args.at(0),d*y+args.at(1)})){
						if(b->getPieceAt(vector<int>{d*x+args.at(0), d*y+args.at(1)}).at(0) != side ){
							bb.push_back(vector<int>{d*x+args.at(0), d*y+args.at(1)});
							//However, if the tile is OWNED by the other side, that is the furtherest we can go.
							if(b->getPieceAt(vector<int>{d*x+args.at(0), d*y+args.at(1)}).at(0) != 0 ){
								break;
							}
						}else{
							break; // Occupied by our own piece
						}
					}else{
						break; // Outside of the board, so stop checking along this line.
					}
				}
			}
		}
		break;
	case 2: 
	// Bishop
		for(int x = -1; x <= 1; x++){
			for(int y = -1; y <= 1; y++){
				if(x == 0 || y == 0){continue;} // If x or y is 0, then we are dealing with either a N,W,S,E direction or x=y=0. Either way, don't search that path
				for(int d = 1; d < 9; d++){ // Go along the path until the fist hit
					if(this->safeTileCheck(b, vector<int>{d*x+args.at(0),d*y+args.at(1)})){
						if(b->getPieceAt(vector<int>{d*x+args.at(0), d*y+args.at(1)}).at(0) != side ){
							bb.push_back(vector<int>{d*x+args.at(0), d*y+args.at(1)});
							//However, if the tile is OWNED by the other side, that is the furtherest we can go.
							if(b->getPieceAt(vector<int>{d*x+args.at(0), d*y+args.at(1)}).at(0) != 0 ){
								break;
							}
						}else{
							break; // Occupied by our own piece
						}
					}else{
						break; // Outside of the board, so stop checking along this line.
					}
				}
			}
		}
		break;
	case 4:
	// Horse/Knight
		for(auto s = horses.begin(); s != horses.end(); s++){
			if(this->safeTileCheck(b, vector<int>{args.at(0) + (*s).at(0), args.at(1) + (*s).at(1)})){
				if(b->getPieceAt(vector<int>{args.at(0) + (*s).at(0), args.at(1) + (*s).at(1)}).at(0) != side){
					bb.push_back(vector<int>{args.at(0) + (*s).at(0), args.at(1) + (*s).at(1)}); // Add all valid horse positions
				}
			}
		}
		break;	
	case 5: 
	// Pawn/Peasant
		// We do logic by side, so side 1 goes up (-y) and side 2 goes down (+y).
		if(args.at(1) == 1 && side == 2){ // Double move allowed
			//allow moving down..
			if(b->getPieceAt(vector<int>{args.at(0), 3}).at(0) == 0 && b->getPieceAt(vector<int>{args.at(0), 2}).at(0) == 0){
				// Check to see if nothing is blocking the pawn in front of it.
				bb.push_back(vector<int>{args.at(0), 2});
				bb.push_back(vector<int>{args.at(0), 3});
			}
		}else if(args.at(1) == 6 && side == 1){// Double move allowed
			//allow moving up...
			if(b->getPieceAt(vector<int>{args.at(0), 4}).at(0) == 0 && b->getPieceAt(vector<int>{args.at(0), 5}).at(0) == 0){
				// Check to see if nothing is blocking the pawn in front of it.
				bb.push_back(vector<int>{args.at(0), 4});
				bb.push_back(vector<int>{args.at(0), 5});
			}
		}else if(side == 1){
			// If already moved once, check to see if it can move forward
			if(this->safeTileCheck(b, vector<int>{args.at(0), args.at(1)-1})){
				if(b->getPieceAt(vector<int>{args.at(0), args.at(1)-1}).at(0) == 0){
					bb.push_back(vector<int>{args.at(0), args.at(1)-1});
				}
			}
		}else if(side == 2){
			// If already moved once, check to see if it can move forward
			if(this->safeTileCheck(b, vector<int>{args.at(0), args.at(1)+1})){
				if(b->getPieceAt(vector<int>{args.at(0), args.at(1)+1}).at(0) == 0){
					bb.push_back(vector<int>{args.at(0), args.at(1)+1});
				}
			}
		}
		//check for attacks, seeing it needs to attack diagonal.
		if(side == 1){
			for(int i = -1; i <= 1; i++){
				if(i == 0){continue;} // Can't attack in front
				if(this->safeTileCheck(b, vector<int>{args.at(0) + i, args.at(1) - 1})){
					if(b->getPieceAt(vector<int>{args.at(0)+i, args.at(1)-1}).at(0) == 2){
						bb.push_back(vector<int>{args.at(0)+i, args.at(1)-1});
					}
				}
				// En passant check. Namely a pawn that has moved twice on opening can be captured by a pawn as if it moved only once.
				if(this->safeTileCheck(b, vector<int>{args.at(0) + i, args.at(1)})){
					auto passantPiece = b->getPieceAt(vector<int>{args.at(0)+i, args.at(1)});
					if(passantPiece.at(0) == 2 && passantPiece.at(1) == 6){
						// EN PASSANT!
						bb.push_back(vector<int>{args.at(0) + i, args.at(1)-1});
					}
				}
			}
		}else{
			for(int i = -1; i <= 1; i++){
				if(i == 0){continue;}// Can't attack in front
				if(this->safeTileCheck(b, vector<int>{args.at(0) + i, args.at(1) + 1})){
					if(b->getPieceAt(vector<int>{args.at(0)+i, args.at(1)+1}).at(0) == 1){
						bb.push_back(vector<int>{args.at(0)+i, args.at(1)+1});
					}
				}
				// En passant check. Namely a pawn that has moved twice on opening can be captured by a pawn as if it moved only once.
				if(this->safeTileCheck(b, vector<int>{args.at(0) + i, args.at(1)})){
					auto passantPiece = b->getPieceAt(vector<int>{args.at(0)+i, args.at(1)});
					if(passantPiece.at(0) == 1 && passantPiece.at(1) == 6){
						// EN PASSANT!
						bb.push_back(vector<int>{args.at(0) + i, args.at(1)+1});
					}
				}
			}
		}
		break;
	default:
		// Sorry aliens, can't handle your checks.
		break;
	}
	return bb;
}



void Chess::checkColor(){
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
// Starts/sets up the board.
void Chess::startBoard(board::Board * b){
	// Define what the checkers look like
	b->setBoardPiece(vector<int>{0,0}, "", COLOR_BLACK); // Default blank piece
	b->setBoardPiece(vector<int>{0}, "", COLOR_BLACK); // Default blank piece
	b->setBoardPiece(vector<int>{-1}, "", COLOR_WHITE); // Default blank piece
	int i = 0;
	/*
		Key:
			K = King
			Q = Queen
			R = Rook
			B = Bishop
			H = Horse (Knight, but you know, K is taken)
			P = Pawn
	*/
	// Player 1 is red, Player 2 is blue.
	auto color_1 = COLOR_RED; 
	auto color_2 = COLOR_BLUE;
	
	for(int p = 1;p <= 2; p++){
		i = 0;
		
		auto cc = (p == 1 ? color_1 : color_2);
		b->setBoardPiece(vector<int>{p}, "", cc);
		b->setBoardPiece(vector<int>{p, i++}, "K", cc); 
		b->setBoardPiece(vector<int>{p,-1}, "K", cc);  // Castleable king
		b->setBoardPiece(vector<int>{p,i++}, "Q", cc); 
		b->setBoardPiece(vector<int>{p,i++}, "B", cc); 
		b->setBoardPiece(vector<int>{p,i++}, "R", cc); 
		b->setBoardPiece(vector<int>{p,7}, "R", cc);  // Castleable rook
		b->setBoardPiece(vector<int>{p,i++}, "H", cc); 
		b->setBoardPiece(vector<int>{p,i++}, "P", cc); 
		b->setBoardPiece(vector<int>{p,i++}, "P", cc); // En Passont peasant, displays the same but allows the game to identify it.
	}
	

	// Place chess on the board
	for(int i=0; i < 8; i++){
		// Player 2 chess at top of board
		b->setPieceAt(vector<int>{i,1}, vector<int>{2,5});
		// Player 1 chess at bottom of board (closer to user)
		b->setPieceAt(vector<int>{i,6}, vector<int>{1,5});
	}
	
	// Set up the board (placing pawns in their respective positions)
	b->setPieceAt(vector<int>{0,0}, vector<int>{2,7});
	b->setPieceAt(vector<int>{7,0}, vector<int>{2,7});
	b->setPieceAt(vector<int>{1,0}, vector<int>{2,4});
	b->setPieceAt(vector<int>{6,0}, vector<int>{2,4});
	b->setPieceAt(vector<int>{2,0}, vector<int>{2,2});
	b->setPieceAt(vector<int>{5,0}, vector<int>{2,2});
	b->setPieceAt(vector<int>{3,0}, vector<int>{2,1});
	b->setPieceAt(vector<int>{4,0}, vector<int>{2,-1});
	
	b->setPieceAt(vector<int>{0,7}, vector<int>{1,7});
	b->setPieceAt(vector<int>{7,7}, vector<int>{1,7});
	b->setPieceAt(vector<int>{1,7}, vector<int>{1,4});
	b->setPieceAt(vector<int>{6,7}, vector<int>{1,4});
	b->setPieceAt(vector<int>{2,7}, vector<int>{1,2});
	b->setPieceAt(vector<int>{5,7}, vector<int>{1,2});
	b->setPieceAt(vector<int>{3,7}, vector<int>{1,1});
	b->setPieceAt(vector<int>{4,7}, vector<int>{1,-1});
	
	b->displayBoard();
	b->showScreen();
}

// After any double move, once play goes back to the user, en-passant wears off, so revert any peasants at the start of the turn.
void Chess::convertPeasants(board::Board * b, int side){
	// search for all passants...then set it to a normal peasant 
	for(int x = 0; x < 8; x++){
		for(int y = 0; y < 8; y++){
			if(b->getPieceAt(vector<int>{x,y}).at(0) == side && b->getPieceAt(vector<int>{x,y}).at(1) == 6){
				b->setPieceAt(vector<int>{x,y}, vector<int>{side, 5});
			}
		}
	}
}

// Get the english locale of the piece.
string Chess::getPawnName(board::Board * b, vector<int> pos){
	switch(b->getPieceAt(pos).at(1)){
	case -1:
	case 0:
		return "KING";
		//Should never actually occur since we catch checkmates......
	case 1:
		return "QUEEN";
	case 2:
		return "BISHOP";
	case 7:
	case 3:
		return "ROOK";
	case 4:
		return "KNIGHT";
	case 5:
	case 6:
		return "PAWN";
	default:
		return "wat"; // Clearly an error...
	}
}

// Describes the move. 
void Chess::describeMove(WINDOW * w,board::Board * b, vector<int> from, vector<int> to, vector<int> attacked, bool enpassant, bool castles){
	wmove(w, 3, 0);
	wclrtoeol(w);
	
	string pawn = this->getPawnName(b, to); // Get the pawn's name.
	string retail = ""; 
	int side = b->getPieceAt(to).at(0); // Get the side of the player that just moved.
	if(attacked.at(0) != -3){ // Determine if the player attacked.
		// State the attack, and maybe the name of the move if it is special (en passant).
		retail = ", capturing Player " + to_string(side == 1 ? 2 : 1) + "'s " + this->getPawnName(b, attacked) + (enpassant ? " by En passant" : "");  
	}else if(castles){
		retail = " by castling";
	}
	if(this->isKingVun(b, (side == 1 ? 2 : 1))){ // Determine if the king of the opposite side is vunerable.
		if(this->anyValidMoves(b, (side == 1 ? 2 : 1))){ // Determine if the other side can move
			retail = retail + ". Check"; // Check only.
		}else{
			retail = retail + ". Checkmate, player " + to_string(side) + " wins"; // Checkmate, the game will end.
		}
	}
	retail = retail + "."; // Add a . for good measure.
	
	
	
	// CITATION: COPYING STRING FROM C++ to C CHAR ARRAYS
	/*
		https://www.techiedelight.com/convert-string-char-array-cpp/
	*/
	char cs[pawn.size() + 1];
	char re[retail.size() + 1];
	pawn.copy(cs, pawn.size()+1);
	cs[pawn.size()] = '\0';
	retail.copy(re, retail.size() + 1);
	re[retail.size()] = '\0';
	// Print the message in ncurses
	wprintw(w, "Player %d moves his %s from (%d, %d) to (%d, %d)%s", side, cs, from.at(0), from.at(1), to.at(0), to.at(1), re);
	// Refresh the view.
	wrefresh(w);
}

void Chess::runChess(){
	// Start ncurses
	initscr();
	// Hide cursor
	curs_set(0);
	// Check if user's terminal supports color
	checkColor();
	// Start Board
	board::Board b;
	startBoard(&b);
	b.showScreen();
	// Start IO
	input::Input i;
	i.setWin(); // Start IO window
	int side = 1;
	this->gutter1 = 0;// Gutter count, those pawns who have been killed
	this->gutter2 = 0;
	bool castling = false;
	WINDOW * inputWindow = i.getWin(); // Input window to draw on.
	while(this->anyValidMoves(&b, side)){ // Determine if any moves can be made by this player.
		castling = false;
		this->convertPeasants(&b, side); // Convert peasants that have moved twice back to normal peasants.
		b.displayBoard(); //Draw the current game board to the back buffer
		b.showScreen(); // Display the buffer
		vector<int> args = i.moveLocationChoice(1, &b, side); // Ask the player for their next move (side is player)
		if(b.getPieceAt(vector<int>{args.at(0), args.at(1)}).at(1) == 5 && abs(args.at(1) - args.at(3)) == 2){
			// If it is a peasant and the peasant hasn't moved, allow it to move two rows.
			b.movePiece(vector<int>{args.at(0), args.at(1)}, vector<int>{args.at(2), args.at(3)}); // Move the piece because it is a move
			b.setPieceAt(vector<int>{args.at(2), args.at(3)}, vector<int>{side, 6}); // Switch it to an en-passant pawn that could be captured next turn.
		}else if(b.getPieceAt(vector<int>{args.at(0), args.at(1)}).at(1) == 7){
			b.swapPieces(vector<int>{args.at(0),args.at(1)},vector<int>{args.at(2),args.at(3)}); // Just swap the locations (old position may contain an enemy piece)
			b.setPieceAt(vector<int>{args.at(2), args.at(3)}, vector<int>{side, 3});
		}else if(b.getPieceAt(vector<int>{args.at(0), args.at(1)}).at(1) == -1 && abs(args.at(0) - args.at(2)) == 2){
			//Castled...
			b.movePiece(vector<int>{args.at(0), args.at(1)}, vector<int>{args.at(2), args.at(3)});
			auto posFrom = vector<int>{((args.at(2) - args.at(0)) == 2 ? 7 : 0),args.at(1)};
			auto posTo = vector<int>{((args.at(2) - args.at(0)) == 2 ? args.at(2)-1 : args.at(2)+1),args.at(3)};
			b.movePiece(posFrom, posTo);
			b.setPieceAt(posTo, vector<int>{side, 3});
			
			if(b.getPieceAt(vector<int>{posFrom.at(0) == 7 ? 0 : 7, args.at(1)} ).at(0) == side && b.getPieceAt(vector<int>{posFrom.at(0) == 7 ? 0 : 7,args.at(1)}).at(1) == 7){
				b.setPieceAt(vector<int>{posFrom.at(0) == 7 ? 0 : 7, args.at(1)}, vector<int>{side, 3});
			}
			castling = true;
		}else{
			b.swapPieces(vector<int>{args.at(0),args.at(1)},vector<int>{args.at(2),args.at(3)}); // Just swap the locations (old position may contain an enemy piece)
		}
		if(side == 1){
			if(b.getPieceAt(vector<int>{args.at(0), args.at(1)}).at(0) != 0){ // Old location contains an enemy piece
				b.swapPieces(vector<int>{args.at(0), args.at(1)}, vector<int>{(this->gutter2 % 2) - 2, this->gutter2/2}); // Move it to the next gutter location
				this->describeMove(inputWindow, &b, vector<int>{args.at(0), args.at(1)}, vector<int>{args.at(2), args.at(3)}, vector<int>{(this->gutter2 % 2) - 2, this->gutter2/2}, false, false); // Describe it.
				this->gutter2++; // Point to the next gutter location
			}else{
				 // If it is zero, check the moved piece (if it is a pawn then we did en-passant)
				 if(abs(args.at(0) - args.at(2)) == 1 && b.getPieceAt(vector<int>{args.at(2), args.at(3)}).at(1) == 5){
					 //en-PASSANT!!!
					b.swapPieces(vector<int>{args.at(2), args.at(1)}, vector<int>{(this->gutter2 % 2) - 2, this->gutter2/2}); // move it to the next gutter location
					this->describeMove(inputWindow, &b, vector<int>{args.at(0), args.at(1)}, vector<int>{args.at(2), args.at(3)}, vector<int>{(this->gutter2 % 2) - 2, this->gutter2/2}, true, false);// Describe it.
					this->gutter2++;
				 }else{
					 
					 this->describeMove(inputWindow, &b, vector<int>{args.at(0), args.at(1)}, vector<int>{args.at(2), args.at(3)}, vector<int>{-3,-3}, false, castling); // Just describe it.
				 }
			}
			side = 2; // Player 2 goes next.
		}else{
			// Basically the same as above, just different logic for player 2.
			if(b.getPieceAt(vector<int>{args.at(0), args.at(1)}).at(0) != 0){
				b.swapPieces(vector<int>{args.at(0), args.at(1)}, vector<int>{(this->gutter1 % 2) + 8, this->gutter1/2});
				this->describeMove(inputWindow, &b, vector<int>{args.at(0), args.at(1)}, vector<int>{args.at(2), args.at(3)}, vector<int>{(this->gutter1 % 2) + 8, this->gutter1/2}, false, false);
				this->gutter1++;
			}else{
				 // If it is zero, check the moved piece (if it is a pawn then we did en-passant)
				 if(abs(args.at(0) - args.at(2)) == 1 && b.getPieceAt(vector<int>{args.at(2), args.at(3)}).at(1) == 5){
					 //en-PASSANT!!!
					b.swapPieces(vector<int>{args.at(2), args.at(1)}, vector<int>{(this->gutter1 % 2) - 2, this->gutter1/2});
					this->describeMove(inputWindow, &b, vector<int>{args.at(0), args.at(1)}, vector<int>{args.at(2), args.at(3)}, vector<int>{(this->gutter1 % 2) + 8, this->gutter1/2}, true, false);
					this->gutter1++;
				 }else{
					 this->describeMove(inputWindow, &b, vector<int>{args.at(0), args.at(1)}, vector<int>{args.at(2), args.at(3)}, vector<int>{-3,-3}, false, castling);
				 }
			}
			side = 1; // Switch back to player one.
		}
		int os = (side == 1 ? 2 : 1); // Original side...
		
		if(b.getPieceAt(vector<int>{args.at(2), args.at(3)}).at(1) == 5 && ((args.at(3) == 0 && b.getPieceAt(vector<int>{args.at(2), args.at(3)}).at(0) == 1)||(args.at(3) == 7 && b.getPieceAt(vector<int>{args.at(2), args.at(3)}).at(0) == 2))){
			// We begin by prompting the user to choose what type of piece this should become.
			wmove(inputWindow, 1, 0);
			wclrtoeol(inputWindow);
			wprintw(inputWindow, "A pawn can be promoted! Available units: (Q)ueen, (K)night, (R)ook, (B)ishop.");
			wmove(inputWindow, 2, 0);
			wclrtoeol(inputWindow);
			wprintw(inputWindow, "Please enter the letter for the unit to be promoted to: ");
			bool valid = false;
			int promo = -1;
			while(!valid){
				// Straight from the input.cpp section
				char cstr[100]; // c string for curses input
				wgetstr(inputWindow, cstr); // get user input
				string input(cstr); // convert c string to c++ string
				if(input.find_first_not_of("QKRB") != string::npos || input.empty() || input.size() != 1){
					wmove(inputWindow, 2, 0);
					wclrtoeol(inputWindow);
					wprintw(inputWindow, "Invalid entry. Please enter the letter for the unit to be promoted to (Q,K,R,B): ");
					wrefresh(inputWindow);
					continue;
				}
				valid = true;
				switch(input[0]){
				case 'Q':
					promo = 1;
					break;
				case 'K':
					promo = 4;
					break;
				case 'R':
					promo = 3;
					break;
				case 'B':
					promo = 2;
					break;
				default:
					//how?!
					break;
				}
				
			}
			b.setPieceAt(vector<int>{args.at(2), args.at(3)}, vector<int>{os, promo});
		}
	}
	//Game end, close the window
	endwin();
}