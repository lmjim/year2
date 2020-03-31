#ifndef __REVERSI_HPP
#define __REVERSI_HPP

// Credits:
// 	learning about Othello: https://www.wikihow.com/Play-Othello
// 				https://www.youtube.com/watch?v=XDxuPNhBfZs
// 	learning about c++:
// 		https://www.dynamicguru.com/tips/cpp-check-if-input-is-valid-data-type-using-cin-fail/
//      	https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
//      	http://www.cplusplus.com/reference/string/string/find_first_not_of/
//      	http://www.cplusplus.com/reference/string/stoi/
//      	https://stackoverflow.com/questions/9235296/how-to-detect-empty-lines-while-reading-from-istream-object-in-c
//      	https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
//      	http://www.cplusplus.com/reference/sstream/stringstream/stringstream/
//      	https://www.geeksforgeeks.org/advantages-of-vector-over-array-in-c/
//     		https://www.geeksforgeeks.org/initialize-a-vector-in-cpp-different-ways/
//     		http://www.math.uaa.alaska.edu/~afkjm/csce211/handouts/SeparateCompilation.pdf

#include <vector>

namespace reversi{
	class Reversi{
	public:
		Reversi() {}
		typedef int*** Board; // Make use of board easier and look nicer
		typedef enum {None, Black, White} Disc; // Any position on the board can either be no disc, black disc, or white disc
		typedef struct{
			int p1; // Player One
			int p2; // Player Two
		} Score;
		void setBoardSize(int size); // Set the user given board size
		int askBoardSize(); // Get user input for board size
		void initBoard(Board board); // Initialize an empty board of a certain size
		void runGame(Board board); // Run the game with the given board
		void cleanBoard(Board board); // Free up the board
	private:
		int boardSize;
		void newBoard(Board board);
		void initScore(Score *score);
		void updateScore(Board board, Score *score);
		void printScore(Score *score);
		void printBoard(Board board);
		void messageToPlayers();
		std::vector<int> getTurnInput(Board board, int player);
		void placeAndFlip(Board board, int player, int x, int y);
		void player1Turn(Board board, Score *score);
		void player2Turn(Board board, Score *score);
		int isTurnsRemaining(Board board);
		void gameOver(Score *score);
	};
}

#endif /* __REVERSI_HPP */
