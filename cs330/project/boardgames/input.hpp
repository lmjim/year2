#ifndef __INPUT_HPP
#define __INPUT_HPP

#include <ncurses.h>
#include "board.hpp"
#include "aggravation.hpp"
#include "sorry.hpp"

using namespace std;

namespace input{
	class Input{
		public:
		Input() {} // Default constructor
		~Input() {delwin(win);} // Default deconstructor
		void setWin() {win = newwin(5,100,0,0);} // Start IO window
		WINDOW * getWin() {return win;} // Return pointer for IO window
		int gameChoice(vector<string> choices); /* Ask what game user would like to play, 
							   returns number associated with game chosen, 
							   this takes place before starting curses mode */
		vector<int> moveLocationChoice(int game, board::Board * b, int player); /* returns from and to location
								for piece getting moved, 
								vector = {from x, from y, to x, to y},
								'game' indicates which game is being played,
								'b' is the state of the board
								'player' indicates which player is taking their turn 
								NOTE: this function relies on the game's validMove checker*/
		vector<int> pieceChoice(int game, board::AggravationBoard * b, aggravation::Aggravation * aggravationGame, int player, int num); /* Pass in the number the player rolled or drew
											     Only call this function if you know there is
											     a valid move the player can make with that number
							  then this function will ask which piece they would like to move,
							  returns the piece they chose and if they get to go again
							  0 = turn goes to next player
							  1 = player goes again
							  vector = {piece chose, num of spaces to move, repeat turn T/F},
							  (calls diceRoll and cardDraw from randMove) */
		vector<int> pieceChoice(int game, board::SorryBoard * b, sorry::Sorry * sorryGame, int player, int num);
		private:
		WINDOW *win; // Window where io will happen
		vector<int> getLocation(); // Reads in 'chess' board location given by user
		vector<int> movingPieceLocation(board::Board * b, int player); /* Ask for and return the location 
								of the piece the user wants to move 
								(calls getLocation) */
		vector<int> moveToLocation(vector<int> pieceToMove); /* Ask for and return the location 
									that the piece will move to 
									(calls getLocation) */
		int getPiece(); // Reads in piece number user chose
	};
}

#endif /*__INPUT_HPP*/
