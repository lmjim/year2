#ifndef __CHECKERS_HPP
#define __CHECKERS_HPP

#include <vector>
#include <ncurses.h>
#include "board.hpp"

namespace checkers{
	class Checkers{
		public:
		Checkers() {}
		~Checkers() {}
		void runCheckers();
		bool validMove(board::Board * b, vector<int> movePiece, int player); /* returns T/F
											based on if the player
											can move a piece from a to b
											movePiece is {from x, from y, to x, to y}
										     */
		private:
		void checkColor();
		void startBoard(board::Board * b);
		bool checkValidMoves(board::Board * b, int player, vector<int> from); /* returns T/F
											 based on if the given piece
											 has ANY available moves
										      */
		int validMovesRemaining(board::Board * b); /* returns value based on moves remaining
							      0: no moves remaining
							      1: only player 1 has move(s)
							      2: only player 2 has move(s)
							      3: both players have moves
							   */
		void pieceMove(board::Board * b, vector<int> movePiece, int player); // actually performs the move on the board
		void endGame(board::Board * b, WINDOW * w); /* prints out who won
							       has user hit enter to exit game
							    */
	}; // end class Checkers
} // end namespace checkers

#endif /* __CHECKERS_HPP */
