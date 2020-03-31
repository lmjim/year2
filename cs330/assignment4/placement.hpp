#ifndef __PLACEMENT_HPP
#define __PLACEMENT_HPP

namespace placement{
	class Placement{
	public:
		Placement() {}
		typedef int*** Board; // Make use of board easier and look nicer
		typedef enum {None, Black, White} Disc;
		int isValidPlacement(Board board, int boardSize, int player, int x, int y); // Checks if xy is valid placement for disc
		int toLeft(Board board, int player, int oppenent, int x, int y);
		int toRight(Board board, int boardSize, int player, int oppenent, int x, int y);
		int upLeft(Board board, int player, int oppenent, int x, int y);
		int upwards(Board board, int player, int oppenent, int x, int y);
		int upRight(Board board, int boardSize, int player, int oppenent, int x, int y);
		int downLeft(Board board, int boardSize, int player, int oppenent, int x, int y);
		int downwards(Board board, int boardSize, int player, int oppenent, int x, int y);
		int downRight(Board board, int boardSize, int player, int oppenent, int x, int y);
	private:
		int upperLeftChoice(Board board, int boardSize, int player, int oppenent, int x, int y);
		int upperRightChoice(Board board, int boardSize, int player, int oppenent, int x, int y);
		int lowerLeftChoice(Board board, int boardSize, int player, int oppenent, int x, int y);
		int lowerRightChoice(Board board, int player, int oppenent, int x, int y);
		int upperEdgeChoice(Board board, int boardSize, int player, int oppenent, int x, int y);
		int leftEdgeChoice(Board board, int boardSize, int player, int oppenent, int x, int y);
		int rightEdgeChoice(Board board, int boardSize, int player, int oppenent, int x, int y);
		int lowerEdgeChoice(Board board, int boardSize, int player, int oppenent, int x, int y);
		int noEdgeChoice(Board board, int boardSize, int player, int oppenent, int x, int y);
	};
}
#endif /* __PLACEMENT_HPP */
