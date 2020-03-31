#ifndef __RANDMOVE_HPP
#define __RANDMOVE_HPP
#include <vector>
namespace randMove{

	class RandMove{
		public:
		RandMove() {} // Default Constructor
		~RandMove() {} // Default Deconstructor
		int diceRoll(); // simulates a standard 6 sided dice roll
                int cardDraw(int deckSize, const std::vector<int>& cards); // draws a card from the Sorry deck, '0' represents a 'sorry' card (finite cards)
				int cardDrawInf();// draws a card from the Sorry deck, '0' represents a 'sorry' card (infinite cards)
		// TODO this is where we will implement computer player functionality
	};

}

#endif /* __RANDMOVE_HPP */

/* 45 Sorry Cards:
 * five 1 cards, can move piece out of start or piece forward one
 * four of each of the following cards
 * 2, can move piece out of start or piece forward two, draw again
 * 3, move forward three
 * 4, move BACKWARD four
 * 5, move forward five
 * 7, move forward seven or move two piece for a total of seven spaces
 * 8, move forward eight
 * 10, move forward ten or BACKWARDS one
 * 11, move forward eleven or switch piece with oppenent
 * 12, move forward twelve
 * SORRY!, in this case 0, move piece from your start to oppenent's location and bump them back to their start 
 */
