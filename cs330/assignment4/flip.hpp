#ifndef __FLIP_HPP
#define __FLIP_HPP

namespace flip{
	class Flip{
	public:
		Flip() {}
		typedef int*** Board; // Make use of board easier and look nicer
		typedef enum {None, Black, White} Disc;
		void doFlip(Board board, int boardSize, int player, int x, int y); // Flip discs given place of new disc
	private:
		void toLeftFlip(Board board, int player, int oppenent, int x, int y);
		void toRightFlip(Board board, int boardSize, int player, int oppenent, int x, int y);
		void upLeftFlip(Board board, int player, int oppenent, int x, int y);
		void upwardsFlip(Board board, int player, int oppenent, int x, int y);
		void upRightFlip(Board board, int boardSize, int player, int oppenent, int x, int y);
		void downLeftFlip(Board board, int boardSize, int player, int oppenent, int x, int y);
		void downwardsFlip(Board board, int boardSize, int player, int oppenent, int x, int y);
		void downRightFlip(Board board, int boardSize, int player, int oppenent, int x, int y);
		void upperLeftChoiceFlip(Board board, int boardSize, int player, int oppenent, int x, int y, placement::Placement p);
		void upperRightChoiceFlip(Board board, int boardSize, int player, int oppenent, int x, int y, placement::Placement p);
		void lowerLeftChoiceFlip(Board board, int boardSize, int player, int oppenent, int x, int y, placement::Placement p);
		void lowerRightChoiceFlip(Board board, int player, int oppenent, int x, int y, placement::Placement p);
		void upperEdgeChoiceFlip(Board board, int boardSize, int player, int oppenent, int x, int y, placement::Placement p);
		void leftEdgeChoiceFlip(Board board, int boardSize, int player, int oppenent, int x, int y, placement::Placement p);
		void rightEdgeChoiceFlip(Board board, int boardSize, int player, int oppenent, int x, int y, placement::Placement p);
		void lowerEdgeChoiceFlip(Board board, int boardSize, int player, int oppenent, int x, int y, placement::Placement p);
		void noEdgeChoiceFlip(Board board, int boardSize, int player, int oppenent, int x, int y, placement::Placement p);
	};
}
#endif /* __FLIP_HPP */
