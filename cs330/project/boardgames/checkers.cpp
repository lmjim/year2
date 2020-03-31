#include <iostream>
#include <vector>
#include <ncurses.h>
#include "checkers.hpp"
#include "input.hpp"

using namespace std;
using namespace checkers;

void Checkers::checkColor(){
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

void Checkers::startBoard(board::Board * b){
	// Define what the checkers look like
	b->setBoardPiece(vector<int>{0}, "", COLOR_BLACK); // Default blank piece
	b->setBoardPiece(vector<int>{0,0}, "", COLOR_BLACK); // Default blank piece
	b->setBoardPiece(vector<int>{1}, "", COLOR_RED); // Default P1 piece
	b->setBoardPiece(vector<int>{1,0}, "*", COLOR_RED); // Player 1 is red
	b->setBoardPiece(vector<int>{1,1}, "#", COLOR_RED); // Player 1 crowned piece
	b->setBoardPiece(vector<int>{2}, "", COLOR_BLUE); // Default P2 piece
	b->setBoardPiece(vector<int>{2,0}, "*", COLOR_BLUE); // Player 2 is blue
	b->setBoardPiece(vector<int>{2,1}, "#", COLOR_BLUE); // Player 2 crowned piece

	// Place checkers on the board
	for(int i=0; i < 7; i++){
		b->setPieceAt(vector<int>{i+1,0}, vector<int>{2,0}); // Player 2 checkers at top of board
		b->setPieceAt(vector<int>{i,1}, vector<int>{2,0});
		b->setPieceAt(vector<int>{i+1,2}, vector<int>{2,0});

		b->setPieceAt(vector<int>{i,5}, vector<int>{1,0}); // Player 1 checkers at bottom of board (closer to user)
		b->setPieceAt(vector<int>{i+1,6}, vector<int>{1,0});
		b->setPieceAt(vector<int>{i,7}, vector<int>{1,0});

		i++; // Place piece every other spot
	}
	b->displayBoard();
	b->showScreen();
}

bool Checkers::validMove(board::Board * b, vector<int> movePiece, int player){
	// movePiece is {from x, from y, to x, to y}
	int fx = movePiece[0];
	int fy = movePiece[1];
	int tx = movePiece[2];
	int ty = movePiece[3];
	int xDiff = abs(fx - tx);
	int yDiff = abs(fy - ty);
	if(xDiff != yDiff){
		return false; // Piece is not moving diagonally
	}
	vector<int> toPlace = b->getPieceAt(vector<int>{tx,ty});
	if(toPlace[0] != 0){
		// spot is not empty
		return false;
	}
	int opponent;
	if(player == 1){
		opponent = 2;
	}
	else{
		opponent = 1;
	}
	vector<int> fromPiece = b->getPieceAt(vector<int>{fx,fy});
	int crown = fromPiece[1];
	if(crown == 0){
		// piece is not crowned, can only move forwards
		if(player == 1){
			// y decrease
			if(ty > fy){
				return false; // moving in wrong direction
			}
			if(xDiff != 1){
				// check if jumping correctly
				if(tx > fx){
					// moving to the right
					int i = tx - 1;
					int j = ty + 1;
					int alt = 1;
					for(i; i > fx; i--){
						vector<int> p = b->getPieceAt(vector<int>{i,j});
						if((alt % 2) == 1 && p[0] != opponent){
							return false; // should have been opponent's piece
						}
						if((alt % 2) == 0 && p[0] != 0){
							return false; // should have been a blank spot to hop on
						}
						alt++;
						j++;
					}
				}
				else{
					// moving to the left
					int i = tx + 1;
                                        int j = ty + 1;
                                        int alt = 1;
                                        for(i; i < fx; i++){
                                                vector<int> p = b->getPieceAt(vector<int>{i,j});
                                                if((alt % 2) == 1 && p[0] != opponent){
                                                        return false; // should have been opponent's piece
                                                }
                                                if((alt % 2) == 0 && p[0] != 0){
                                                        return false; // should have been a blank spot to hop on
                                                }
						alt++;
						j++;
                                        }
				}
			}
		}
		else{
			// player 2, y increases
			if(ty < fy){
				return false; // moving in wrong direction
			}
			if(xDiff != 1){
                                // check if jumping correctly
				if(tx > fx){
					// moving to the right
					int i = tx - 1;
                                        int j = ty - 1;
                                        int alt = 1;
                                        for(i; i > fx; i--){
                                                vector<int> p = b->getPieceAt(vector<int>{i,j});
                                                if((alt % 2) == 1 && p[0] != opponent){
                                                        return false; // should have been opponent's piece
                                                }
                                                if((alt % 2) == 0 && p[0] != 0){
                                                        return false; // should have been a blank spot to hop on
                                                }
						alt++;
						j--;
                                        }
				}
				else{
					// moving to the left
					int i = tx + 1;
                                        int j = ty - 1;
                                        int alt = 1;
                                        for(i; i < fx; i++){
                                                vector<int> p = b->getPieceAt(vector<int>{i,j});
                                                if((alt % 2) == 1 && p[0] != opponent){
                                                        return false; // should have been opponent's piece
                                                }
                                                if((alt % 2) == 0 && p[0] != 0){
                                                        return false; // should have been a blank spot to hop on
                                                }
						alt++;
						j--;
                                        }
				}
                        }
		}
	}
	else{
		// piece is crowned, can move forwards and back
		if(xDiff != 1){
			if(ty < fy){
				if(tx > fx){
					// moving to the right
					int i = tx - 1;
					int j = ty + 1;
					int alt = 1;
					for(i; i > fx; i--){
						vector<int> p = b->getPieceAt(vector<int>{i,j});
						if((alt % 2) == 1 && p[0] != opponent){
							return false; // should have been opponent's piece
						}
						if((alt % 2) == 0 && p[0] != 0){
							return false; // should have been a blank spot to hop on
						}
						alt++;
						j++;
					}
				}
				else{
					// moving to the left
					int i = tx + 1;
                                        int j = ty + 1;
                                        int alt = 1;
                                        for(i; i < fx; i++){
                                                vector<int> p = b->getPieceAt(vector<int>{i,j});
                                                if((alt % 2) == 1 && p[0] != opponent){
                                                        return false; // should have been opponent's piece
                                                }
                                                if((alt % 2) == 0 && p[0] != 0){
                                                        return false; // should have been a blank spot to hop on
                                                }
						alt++;
						j++;
                                        }
				}
			}
			else{ // ty > fy
				if(tx > fx){
					// moving to the right
					int i = tx - 1;
                                        int j = ty - 1;
                                        int alt = 1;
                                        for(i; i > fx; i--){
                                                vector<int> p = b->getPieceAt(vector<int>{i,j});
                                                if((alt % 2) == 1 && p[0] != opponent){
                                                        return false; // should have been opponent's piece
                                                }
                                                if((alt % 2) == 0 && p[0] != 0){
                                                        return false; // should have been a blank spot to hop on
                                                }
						alt++;
						j--;
                                        }
				}
				else{
					// moving to the left
					int i = tx + 1;
                                        int j = ty - 1;
                                        int alt = 1;
                                        for(i; i < fx; i++){
                                                vector<int> p = b->getPieceAt(vector<int>{i,j});
                                                if((alt % 2) == 1 && p[0] != opponent){
                                                        return false; // should have been opponent's piece
                                                }
                                                if((alt % 2) == 0 && p[0] != 0){
                                                        return false; // should have been a blank spot to hop on
                                                }
						alt++;
						j--;
                                        }
				}
			}
		}
	}
	return true; // passed all false cases
}

bool Checkers::checkValidMoves(board::Board * b, int player, vector<int> from){
	bool valid = false;
	int x = from[0];
	int y = from[1];
	vector<int> movePiece;
	movePiece.push_back(from[0]);
	movePiece.push_back(from[1]);
	movePiece.push_back(0);
	movePiece.push_back(0);
	int crown = b->getPieceAt(vector<int>{from[0],from[1]})[1];
	if(crown == 0){
		// piece is not crowned, can only move forwards
		if(player == 1){
			// y decreases to move forward
			// y != 0 because piece is not crowned
			if(x == 0){ // Piece is on left edge
				// x must increase
				movePiece[2] = 1; // from x is 0, so to x is 1
				movePiece[3] = y - 1;
				if(validMove(b, movePiece, player)){
					valid = true;
				}
				if(y != 1){
					movePiece[2] = 2; // if piece gets to jump oppenent at least once
					movePiece[3] = y - 2;
					if(validMove(b, movePiece, player)){
	                                        valid = true;
	                                }
				}
			}
			else if(x == 7){ // Piece is on right edge
				// x must decrease
				movePiece[2] = 6; // from x is 7, so to x is 6
                                movePiece[3] = y - 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
                                if(y != 1){
                                        movePiece[2] = 5; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y - 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
                                }
			}
			else if(x == 1){ // Piece near left edge
				// x can decrease by 1 or increase
				movePiece[2] = x + 1;
                                movePiece[3] = y - 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
                                movePiece[2] = x - 1;
                                movePiece[3] = y - 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
                                if(y != 1){
                                        movePiece[2] = x + 2; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y - 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
                                }
			}
			else if(x == 6){ // Piece near right edge
				// x can increase by 1 or decrease
				movePiece[2] = x + 1;
                                movePiece[3] = y - 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
                                movePiece[2] = x - 1;
                                movePiece[3] = y - 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
                                if(y != 1){
                                        movePiece[2] = x - 2; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y - 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
                                }
			}
			else{ // Piece is in middle
				// x can increase or decrease
				movePiece[2] = x + 1;
                                movePiece[3] = y - 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
				movePiece[2] = x - 1;
                                movePiece[3] = y - 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
                                if(y != 1){
                                        movePiece[2] = x + 2; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y - 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
					movePiece[2] = x - 2; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y - 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
                                }
			}
		}
		else{ // player 2
			// y increases to move forward for player 2
                        // y != 7 because piece is not crowned
                        if(x == 0){ // Piece is on left edge
                                // x must increase
                                movePiece[2] = 1; // from x is 0, so to x is 1
                                movePiece[3] = y + 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
                                if(y != 6){
                                        movePiece[2] = 2; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y + 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
                                }
                        }
                        else if(x == 7){ // Piece is on right edge
                                // x must decrease
                                movePiece[2] = 6; // from x is 7, so to x is 6
                                movePiece[3] = y + 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
                                if(y != 6){
                                        movePiece[2] = 5; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y + 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
                                }
                        }
			else if(x == 1){ // Piece near left edge
                                // x can decrease by 1 or increase
                                movePiece[2] = x + 1;
                                movePiece[3] = y + 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
                                movePiece[2] = x - 1;
                                movePiece[3] = y + 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
                                if(y != 6){
                                        movePiece[2] = x + 2; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y + 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
                                }
                        }
                        else if(x == 6){ // Piece near right edge
                                // x can increase by 1 or decrease
                                movePiece[2] = x + 1;
                                movePiece[3] = y + 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
                                movePiece[2] = x - 1;
                                movePiece[3] = y + 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
                                if(y != 6){
                                        movePiece[2] = x - 2; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y + 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
                                }
                        }
			else{ // Piece is in middle
                                // x can increase or decrease
                                movePiece[2] = x + 1;
                                movePiece[3] = y + 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
                                movePiece[2] = x - 1;
                                movePiece[3] = y + 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
                                if(y != 6){
                                        movePiece[2] = x + 2; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y + 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
                                        movePiece[2] = x - 2; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y + 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
                                }
                        }
		}
	}
	else{
		// piece is crowned, can move forwards and back
		// player # does not matter because they have the same eligible moves (forwards/backwards)
                        if(x == 0){ // Piece is on left edge
                                // x must increase
				if(y > 0){
                                movePiece[2] = 1; // from x is 0, so to x is 1
                                movePiece[3] = y - 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
				}
                                if(y > 1){
                                        movePiece[2] = 2; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y - 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
                                }
				if(y < 7){
				movePiece[2] = 1; // from x is 0, so to x is 1
                                movePiece[3] = y + 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
				}
                                if(y < 6){
                                        movePiece[2] = 2; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y + 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
                                }
                        }
                        else if(x == 7){ // Piece is on right edge
                                // x must decrease
				if(y > 0){
                                movePiece[2] = 6; // from x is 7, so to x is 6
                                movePiece[3] = y - 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
				}
                                if(y > 1){
                                        movePiece[2] = 5; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y - 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
                                }
				if(y < 7){
				movePiece[2] = 6; // from x is 7, so to x is 6
                                movePiece[3] = y + 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
				}
                                if(y < 6){
                                        movePiece[2] = 5; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y + 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
                                }
                        }
			else if(x == 1){ // Piece near left edge
                                // x can decrease by 1 or increase
				if(y > 0){
                                movePiece[2] = x + 1;
                                movePiece[3] = y - 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
                                movePiece[2] = x - 1;
                                movePiece[3] = y - 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
				}
                                if(y > 1){
                                        movePiece[2] = x + 2; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y - 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
                                }
				if(y < 7){
				movePiece[2] = x + 1;
                                movePiece[3] = y + 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
                                movePiece[2] = x - 1;
                                movePiece[3] = y + 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
				}
                                if(y < 6){
                                        movePiece[2] = x + 2; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y + 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
                                }
                        }
                        else if(x == 6){ // Piece near right edge
                                // x can increase by 1 or decrease
				if(y > 0){
                                movePiece[2] = x + 1;
                                movePiece[3] = y - 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
                                movePiece[2] = x - 1;
                                movePiece[3] = y - 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
				}
                                if(y > 1){
                                        movePiece[2] = x - 2; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y - 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
                                }
				if(y < 7){
				movePiece[2] = x + 1;
                                movePiece[3] = y + 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
                                movePiece[2] = x - 1;
                                movePiece[3] = y + 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
				}
                                if(y < 6){
                                        movePiece[2] = x - 2; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y + 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
                                }
                        }
			else{ // Piece is in middle
				// x can increase or decrease
				if(y > 0){
				movePiece[2] = x + 1;
                                movePiece[3] = y - 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
				movePiece[2] = x - 1;
                                movePiece[3] = y - 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
				}
                                if(y > 1){
                                        movePiece[2] = x + 2; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y - 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
					movePiece[2] = x - 2; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y - 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
                                }
				if(y < 7){
				movePiece[2] = x + 1;
                                movePiece[3] = y + 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
                                movePiece[2] = x - 1;
                                movePiece[3] = y + 1;
                                if(validMove(b, movePiece, player)){
                                        valid = true;
                                }
				}
                                if(y < 6){
                                        movePiece[2] = x + 2; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y + 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
                                        movePiece[2] = x - 2; // if piece gets to jump oppenent at least once
                                        movePiece[3] = y + 2;
                                        if(validMove(b, movePiece, player)){
                                                valid = true;
                                        }
                                }
			}
	}
	return valid;
}

int Checkers::validMovesRemaining(board::Board * b){
	bool p1 = false;
	bool p2 = false;
	int count1 = 0;
	int count2 = 0;
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			vector<int> fromPiece = b->getPieceAt(vector<int>{i,j});
			int player = fromPiece[0];
			if(player == 1){
				count1++;
			}
			if(player == 2){
				count2++;
			}
			if(player == 1 && p1 == false){
				p1 = checkValidMoves(b, 1, vector<int>{i,j});
			}
			if(player == 2 && p2 == false){
				p2 = checkValidMoves(b, 2, vector<int>{i,j});
			}
			if(p1 == true && p2 == true){
				return 3; // Both players have moves left
			}
		}
	}
	if(p1 == true && p2 == false && count2 != 0){
		return 1; // Only player 1 has a move
	}
	if(p1 == false && count1 != 0 && p2 == true){
		return 2; // Only player 2 has a move
	}
	return 0; // No moves left
}

void Checkers::pieceMove(board::Board * b, vector<int> movePiece, int player){
	int fx = movePiece[0];
	int fy = movePiece[1];
        int tx = movePiece[2];
	int ty = movePiece[3];
        int xDiff = abs(fx - tx);
	vector<int> fromPiece{fx, fy};
	vector<int> toPlace{tx, ty};
	int crown = b->getPieceAt(fromPiece)[1];
	// always move original piece
	b->movePiece(fromPiece, toPlace);
	if(crown == 0){
                if(player == 1 && ty == 0){
                        b->setPieceAt(toPlace, vector<int>{1,1}); // Override standard piece to crowned piece
                }
                else if(player == 2 && ty == 7){
                        b->setPieceAt(toPlace, vector<int>{2,1}); // Override standard piece to crowned piece
                }
	}
	// if jumping happens, remove oppenent's pieces that were jumped over
	if(xDiff != 1){
		if(crown == 0){
			if(player == 1){
				if(tx > fx){
                                        // moving to the right
                                        int i = tx - 1;
                                        int j = ty + 1;
                                        for(i; i > fx; i--){
                                                b->setPieceAt(vector<int>{i,j}, vector<int>{0});
						i--;
                                                j+=2;
                                        }
                                }
                                else{
                                        // moving to the left
                                        int i = tx + 1;
                                        int j = ty + 1;
                                        for(i; i < fx; i++){
                                                b->setPieceAt(vector<int>{i,j}, vector<int>{0});
						i++;
                                                j+=2;
                                        }
                                }
			}
			if(player == 2){
				if(tx > fx){
                                        // moving to the right
                                        int i = tx - 1;
                                        int j = ty - 1;
                                        for(i; i > fx; i--){
                                                b->setPieceAt(vector<int>{i,j}, vector<int>{0});
						i--;
                                                j-=2;
                                        }
                                }
                                else{
                                        // moving to the left
                                        int i = tx + 1;
                                        int j = ty - 1;
                                        for(i; i < fx; i++){
                                                b->setPieceAt(vector<int>{i,j}, vector<int>{0});
						i++;
                                        	j-=2;
                                        }
                                }
			}
		}
		else{
			// crowned piece, y can increase or decrease
			if(ty < fy){
				if(tx > fx){
                                        // moving to the right
                                        int i = tx - 1;
                                        int j = ty + 1;
                                        for(i; i > fx; i--){
                                                b->setPieceAt(vector<int>{i,j}, vector<int>{0});
						i--;
                                                j+=2;
                                        }
                                }
                                else{
                                        // moving to the left
                                        int i = tx + 1;
                                        int j = ty + 1;
                                        for(i; i < fx; i++){
                                                b->setPieceAt(vector<int>{i,j}, vector<int>{0});
						i++;
                                                j+=2;
                                        }
                                }
			}
			else{ // ty > fy
				if(tx > fx){
                                        // moving to the right
                                        int i = tx - 1;
                                        int j = ty - 1;
                                        for(i; i > fx; i--){
                                                b->setPieceAt(vector<int>{i,j}, vector<int>{0});
						i--;
                                                j-=2;
                                        }
                                }
                                else{
                                        // moving to the left
                                        int i = tx + 1;
                                        int j = ty - 1;
                                        for(i; i < fx; i++){
                                                b->setPieceAt(vector<int>{i,j}, vector<int>{0});
						i++;
                                        	j-=2;
                                        }
                                }
			}
		}
	}
	return;
}

void Checkers::endGame(board::Board * b, WINDOW * w){
	int winner = -1;
	int p1 = 0;
	int p2 = 0;
	for(int i=0; i<8; i++){
                for(int j=0; j<8; j++){
			// Check all pieces on the board
                        vector<int> piece = b->getPieceAt(vector<int>{i,j});
			if(piece[0] == 1){
				p1++; // Add up player 1 pieces
			}
			else if(piece[0] == 2){
				p2++; // Add up player 2 pieces
			}
		}
	}
	// Print winner:
	wclear(w);
	if(p1 > p2){
		mvwprintw(w, 0, 0, "Player 1 won!");
	}
	else if(p2 > p1){
		mvwprintw(w, 0, 0, "Player 2 won!");
	}
	else{
		mvwprintw(w, 0, 0, "It's a draw!");
	}
	mvwprintw(w, 1, 0, "Hit enter to exit"); // Prompt to close game
	wrefresh(w);
	wgetch(w);
	return;
}

//'main' function to actually run the game of checkers
void Checkers::runCheckers(){
	// Start ncurses
	initscr();
	// Hide cursor
	curs_set(0);
	// Check if user's terminal supports color
	checkColor();
	// Start Board
	board::Board b;
	startBoard(&b);
	// Start IO
	input::Input i;
	i.setWin(); // Start IO window
	WINDOW * w = i.getWin();

	// Run the game
	bool running = true;
	int moves = validMovesRemaining(&b);
	vector<int> movePiece;
	while(running){
		if(moves == 1 || moves == 3){ // Player 1 can make a move
			movePiece = i.moveLocationChoice(2, &b, 1);
			pieceMove(&b, movePiece, 1);
			wmove(w, 3, 0);
		        wclrtoeol(w);
		        mvwprintw(w, 3, 0, "%d %d moved to %d %d", movePiece[0], movePiece[1], movePiece[2], movePiece[3]);
			wrefresh(w);
			b.displayBoard();
			b.showScreen();
		}
		moves = validMovesRemaining(&b);
		if(moves == 2 || moves == 3){ // Player 2 can make a move
			movePiece = i.moveLocationChoice(2, &b, 2);
			pieceMove(&b, movePiece, 2);
			wmove(w, 3, 0);
                        wclrtoeol(w);
                        mvwprintw(w, 3, 0, "%d %d moved to %d %d", movePiece[0], movePiece[1], movePiece[2], movePiece[3]);
                        wrefresh(w);
			b.displayBoard();
			b.showScreen();
		}
		moves = validMovesRemaining(&b);
		if(moves == 0){
			running = false;
		}
	}
	endGame(&b, w); // Print winner and prompt to close game

	endwin();
}

