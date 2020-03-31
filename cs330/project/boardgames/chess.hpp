#ifndef __CHESS_HPP
#define __CHESS_HPP
#include <vector>
#include "board.hpp"
#include <ncurses.h>
#include <string>
namespace chess{
	class Chess{
		public:
			Chess() {}
			~Chess() {}
			void runChess();// The 'main' function to run the game
			void checkColor(); // Check if the terminal supports color
			void startBoard(board::Board * b); // Initializes and sets up the game board.
			vector<int> findKing(board::Board * b, int side); // A function to find the sides king
			bool isKingVun(board::Board * b, int side); // A function to determine if an enemy pawn can attack this king
			
			vector<vector<int> > getAllAttackableTiles(board::Board * b, vector<int> args, int side, bool recurse); // Gets all attackable tiles for a given side (with potential recursion based on the king)
			vector<vector<int> > getAllAttackableTiles(board::Board * b, vector<int> args, int side){return this->getAllAttackableTiles(b, args, side, true);} // To prevent kings from recursively asking what moves the other can make.
			bool validMove(board::Board * b, vector<int> movePiece, int side); // Determine if a move is a valid move
			bool safeTileCheck(board::Board * b, vector<int> toPos); // Quickly computes to see if this position is considered in the bounds of the board.
			bool anyValidMoves(board::Board * b, int side); // Determine if the piece can move anywhere
			void convertPeasants(board::Board * b, int side); // Quickly convert all peasants to normal peasants
			void describeMove(WINDOW * w, board::Board *b, vector<int> from, vector<int> to, vector<int> attacked, bool enpassant, bool castle); // Prints a string based on the move.
			std::string getPawnName(board::Board * b, vector<int> pos); // Gets the locale name of the pawn
		private:
			int gutter1 = 0;
			int gutter2 = 0;
	}; // end class Chess
} // end namespace chess

#endif /* __CHESS_HPP */
