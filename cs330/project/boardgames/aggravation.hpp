#ifndef __AGGRAVATION_HPP
#define __AGGRAVATION_HPP

#include <vector>
#include <ncurses.h>
#include "board.hpp"

namespace aggravation{
	class Aggravation{
		public:
		Aggravation() {}
		~Aggravation() {}
		void runAggravation(); // The 'main' function to run the game
		bool validMove(board::AggravationBoard * b, vector<int> movePiece, int player); // Check if piece chosen can make the given move
		private:
		const vector<vector<int>> positions{vector<int>{7,7},vector<int>{9,0},vector<int>{9,1},
			vector<int>{9,2},vector<int>{9,3},vector<int>{9,4},vector<int>{9,5},vector<int>{10,5},
			vector<int>{11,5},vector<int>{12,5},vector<int>{13,5},vector<int>{14,5},vector<int>{14,6},
			vector<int>{14,7},vector<int>{14,8},vector<int>{14,9},vector<int>{13,9},vector<int>{12,9},
			vector<int>{11,9},vector<int>{10,9},vector<int>{9,9},vector<int>{9,10},vector<int>{9,11},
			vector<int>{9,12},vector<int>{9,13},vector<int>{9,14},vector<int>{8,14},vector<int>{7,14},
			vector<int>{6,14},vector<int>{5,14},vector<int>{5,13},vector<int>{5,12},vector<int>{5,11},
			vector<int>{5,10},vector<int>{5,9},vector<int>{4,9},vector<int>{3,9},vector<int>{2,9},
			vector<int>{1,9},vector<int>{0,9},vector<int>{0,8},vector<int>{0,7},vector<int>{0,6},
			vector<int>{0,5},vector<int>{1,5},vector<int>{2,5},vector<int>{3,5},vector<int>{4,5},
			vector<int>{5,5},vector<int>{5,4},vector<int>{5,3},vector<int>{5,2},vector<int>{5,1},
			vector<int>{5,0},vector<int>{6,0},vector<int>{7,0},vector<int>{8,0},vector<int>{1,1},
			vector<int>{2,2},vector<int>{3,3},vector<int>{4,4},vector<int>{13,1},vector<int>{12,2},
			vector<int>{11,3},vector<int>{10,4},vector<int>{13,13},vector<int>{12,12},vector<int>{11,11},
			vector<int>{10,10},vector<int>{1,13},vector<int>{2,12},vector<int>{3,11},vector<int>{4,10},
			vector<int>{7,1},vector<int>{7,2},vector<int>{7,3},vector<int>{7,4},vector<int>{13,7},
			vector<int>{12,7},vector<int>{11,7},vector<int>{10,7},vector<int>{7,13},vector<int>{7,12},
			vector<int>{7,11},vector<int>{7,10},vector<int>{1,7},vector<int>{2,7},vector<int>{3,7},vector<int>{4,7}}; 
			/* Each position on the board is numbered 
			   (instead of using vector positions for everything)
			*/
		vector<int> locations{57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72}; /* Each piece has a location in the above positions
											 * 0 P1-1    4 P2-1     8 P3-1    12 P4-1
										         * 1 P1-2    5 P2-2     9 P3-2    13 P4-2
										         * 2 P1-3    6 P2-3    10 P3-3    14 P4-3
										         * 3 P1-4    7 P2-4    11 P3-4    15 P4-4
											 * initial definition matches the starting positions of the pieces
										         */
		void checkColor();
		void startBoard(board::AggravationBoard * b); // Put pieces at their initial position
		int getPieceLoc(board::AggravationBoard * b, int piece, int player); // Get index in location vector for a piece
		bool withinHomeValid(board::AggravationBoard * b, int fromSpot, int num, int player); // Check if piece can be moved within home area
		bool startAvailable(board::AggravationBoard * b, int player); // Check if player can move piece onto Start
		bool centerExitAvailable(board::AggravationBoard * b, int player); // Check if player can move piece out of center
		bool validLoopMove(board::AggravationBoard * b, int fromSpot, int num, int player); // Check if player can move piece located on loop
		bool enterHomeValid(board::AggravationBoard * b, int fromSpot, int num, int player); // Check if player can move piece into home spot
		bool canMove(board::AggravationBoard * b, int roll, int player); // See if player can move a piece based on rolled number
		bool wantToMoveToCenter(WINDOW * w); // Ask player if they want to move to center
		int getToSpot(board::AggravationBoard * b, WINDOW * w, int pieceLoc, int num, int player); // Get the position number the piece is moving to
		void pieceMove(board::AggravationBoard * b, int pieceLoc, int toSpot); // Move piece from one spot to another
		bool active(); // Returns false when a player gets all their pieces in home
		void endGame(WINDOW * w); // Notify users of winner, prompt to close game
	}; // end class Aggravation
} // end namespace aggravation

#endif /* __AGGRAVATION_HPP */
