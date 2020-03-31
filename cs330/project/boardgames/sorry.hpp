#ifndef __SORRY_HPP
#define __SORRY_HPP

#include <vector>
#include <utility>
#include "board.hpp"

namespace sorry{
	class Sorry{
		public:
		Sorry() {
			try{
				sorryDeck = new vector<int>{4, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4};
				boardPositions = new vector<std::pair<int,int> >{};
				// All possible board positions for interactable tiles... (60 public tiles)
				for(int i = 0; i < 15; i++){
					boardPositions->push_back(std::pair<int,int>{i, 0});
				}
				for(int i = 0; i < 15; i++){
					boardPositions->push_back(std::pair<int,int>{15, i});
				}
				for(int i = 0; i < 15; i++){
					boardPositions->push_back(std::pair<int,int>{15-i, 15});
				}
				for(int i = 0; i < 15; i++){
					boardPositions->push_back(std::pair<int,int>{0, 15-i});
				}
				//reds home starts at 60
				for(int i = 0; i < 6; i++){
					boardPositions->push_back(std::pair<int,int>{13, 14-i});
				}
				//blue's home starts at 66
				for(int i = 0; i < 6; i++){
					boardPositions->push_back(std::pair<int,int>{1+i, 13});
				}
				//green's home starts at 72
				for(int i = 0; i < 6; i++){
					boardPositions->push_back(std::pair<int,int>{14 -i, 2});
				}
				//magenta's home starts at 78
				for(int i = 0; i < 6; i++){
					boardPositions->push_back(std::pair<int,int>{2, 1+i});
				}
				// All other locations are not tracked due to not having to interact with them...
			}catch(...){
				std::cout << "An issue with allocating space has occured. Please try again later." << std::endl;
				exit(1);
			}
			sorryDeckOfCardsAmount = 45;
		}
		~Sorry() {
			delete sorryDeck;
		}
		void runSorry();
		bool validMove(board::SorryBoard * b, vector<int> movePiece, int player) {return true;} // TODO CHANGE
		private:
		void checkColor();
		void startBoard(board::SorryBoard * b);
		bool validMove(board::SorryBoard * b, int player, vector<int> from, vector<int> to); /* returns T/F
                                                                                                   based on if the player (1 or 2)
                                                                                                   can move a piece from a to b
                                                                                                */
		int validMovesRemaining(board::SorryBoard * b); /* returns value based on moves remaining
							      0: no moves remaining
							      1: only player 1 has move(s)
							      2: only player 2 has move(s)
							      3: both players have moves
							   */
		protected:
			int sorryDeckOfCardsAmount;
			vector<int>* sorryDeck;
			vector<std::pair<int, int> >* boardPositions;
	}; // end class Sorry
} // end namespace sorry

#endif /* __SORRY_HPP */
