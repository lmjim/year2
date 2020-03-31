#ifndef BOARD_HPP_
#define BOARD_HPP_
#include <vector>
#include <string>
#include <ncurses.h>
#include <map>

using namespace std;

namespace board{
	class Board{
	public:
	// Default chess board
	Board();
	/*Constructor: Takes arguments (in args) width, height, gutter_width
	  Constructs an 8x8 chessboard with 2x8 gutters on the left and right side.
		The width of every chess cell is 2*width + 1 [in characters width]
		The height of every chess cell is height [in character height]
		The width of the gutter width is gutter_width [in character width]
	*/
	Board(const vector<int>& args); 
	~Board(); // Deconstructor
		
	/*Arguments vector:
		POSX: Starting position x to draw,
		POSY: Starting position y to draw,
		SIZEX: Width of the cell to draw,
		SIZEY: Height of the cell to draw,
		COLOR_PAIR_INDEX: The color pair to draw the cell with
		TOKEN_FOREGROUND_COLOR: The color to draw the text with
	  The line is the string to render in the center of the tile.	
	  This function draws a string, centered vertically and horizontally in a cell
	  The cell is drawn at the position X,Y (top left corner) and has a size of X,Y
	*/
	void displayLine(const vector<int>& args, string line); 
		
	// This function draws a SINGLE cell, however, only draws the space character (so effectively sets a single background)
	void setTileDisplay(const vector<int>& args); // Somehow manipulates the screen based on args
		
	// This function will tell ncurses to refresh the CHESSBOARD screen and draw any changes.
	void showScreen();
		
	// This function will tell ncurses to clear the CHESSBOARD screen. Note: this does not mean it will update the display, you need to call showScreen.
	void clearScreen();
		
	// This function will draw the board to the CHESSBOARD screen, but will not update the display.
	void displayBoard();
		
	// Retrieves the piece at a given location on the board.
	vector<int> getPieceAt(const vector<int>& pos); 
		
	// Sets the tile at 'pos' to have the "piece" newVal.
	void setPieceAt(const vector<int>& pos, const vector<int>& newVal);
		
	// Add a color pair to ncurses to render on the screen. Takes a foreground color, background color, and a pair ID
	void setColorPair(int fg, int bg, int id);
		
	// This will register a board "piece", with it's ID, its foreground rendering color, its string to display.
	void setBoardPiece(vector<int> piece, string str, int colorID);
		
	// Swaps the pieces at the locations from and 'to'
	void swapPieces(const vector<int>& from, const vector<int>& to); 
		
	// Takes the tile at from, moves it to location 'to', and sets the 'from' to blank (vector<int>{0})
	void movePiece(const vector<int>& from, const vector<int>& to); 

	protected:
		map< vector<int>, vector<int> > board; // The board's internal information.
		int startX, startY; // The start and end X/Y for the board to be displayed at.
		map<vector<int>, string> boardPawnSet;// The strings to be used to display what occupies each space.
		vector<int> boardStats; // Universal board statuses. May be useful, maybe useless.
		WINDOW *win;
		map<vector<int>, int> boardPawnFGCol; // The foreground color to be used to display what occupies each space.
		map<vector<int> , int> cpairMap; // A map for registering color combinations (pairs -> IDs).
		map<int, vector<int> > colorMap; // A map for registering color combinations (IDs -> pairs).
	};
	class SorryBoard : public Board{
	public:
		SorryBoard();
		~SorryBoard();
		void displayLine(const vector<int>& args, string line); 
		
		// Similar to displayLine, however it will repeat characters in line either horizontally or vertically.
		void repeatLine(const vector<int>& args, string line, bool horizontally); 
		
		
		// This function draws a SINGLE cell, however, only draws the space character (so effectively sets a single background)
		void setTileDisplay(const vector<int>& args); // Somehow manipulates the screen based on args
			
		// This function will tell ncurses to refresh the CHESSBOARD screen and draw any changes.
		void showScreen();
			
		// This function will tell ncurses to clear the CHESSBOARD screen. Note: this does not mean it will update the display, you need to call showScreen.
		void clearScreen();
			
		// This function will draw the board to the CHESSBOARD screen, but will not update the display.
		void displayBoard();
			
		// Retrieves the piece at a given location on the board.
		vector<int> getPieceAt(const vector<int>& pos); 
			
		// Sets the tile at 'pos' to have the "piece" newVal.
		void setPieceAt(const vector<int>& pos, const vector<int>& newVal);
			
		// Add a color pair to ncurses to render on the screen. Takes a foreground color, background color, and a pair ID
		void setColorPair(int fg, int bg, int id);
			
		// This will register a board "piece", with it's ID, its foreground rendering color, its string to display.
		void setBoardPiece(vector<int> piece, string str, int colorID);
			
		// Swaps the pieces at the locations from and 'to'
		void swapPieces(const vector<int>& from, const vector<int>& to); 
			
		// Takes the tile at from, moves it to location 'to', and sets the 'from' to blank (vector<int>{0})
		void movePiece(const vector<int>& from, const vector<int>& to); 
		
		void flashToken(const vector<int>& pos, attr_t attributes);
	protected:
		map< vector<int>, vector<int> > board; // The board's internal information.
		int startX, startY; // The start and end X/Y for the board to be displayed at.
		map<vector<int>, string> boardPawnSet;// The strings to be used to display what occupies each space.
		vector<int> boardStats; // Universal board statuses. May be useful, maybe useless.
		WINDOW *win;
		map<vector<int>, int> boardPawnFGCol; // The foreground color to be used to display what occupies each space.
		map<vector<int> , int> cpairMap; // A map for registering color combinations (pairs -> IDs).
		map<int, vector<int> > colorMap; // A map for registering color combinations (IDs -> pairs).
		int getColAlt(int fg);
	};
	
	class AggravationBoard : public Board{
	public:
		AggravationBoard();
		~AggravationBoard();
		void displayLine(const vector<int>& args, string line); 
		
		// This function draws a SINGLE cell, however, only draws the space character (so effectively sets a single background)
		void setTileDisplay(const vector<int>& args); // Somehow manipulates the screen based on args
			
		// This function will tell ncurses to refresh the CHESSBOARD screen and draw any changes.
		void showScreen();
			
		// This function will tell ncurses to clear the CHESSBOARD screen. Note: this does not mean it will update the display, you need to call showScreen.
		void clearScreen();
			
		// This function will draw the board to the CHESSBOARD screen, but will not update the display.
		void displayBoard();
			
		// Retrieves the piece at a given location on the board.
		vector<int> getPieceAt(const vector<int>& pos); 
			
		// Sets the tile at 'pos' to have the "piece" newVal.
		void setPieceAt(const vector<int>& pos, const vector<int>& newVal);
			
		// Add a color pair to ncurses to render on the screen. Takes a foreground color, background color, and a pair ID
		void setColorPair(int fg, int bg, int id);
			
		// This will register a board "piece", with it's ID, its foreground rendering color, its string to display.
		void setBoardPiece(vector<int> piece, string str, int colorID);
			
		// Swaps the pieces at the locations from and 'to'
		void swapPieces(const vector<int>& from, const vector<int>& to); 
			
		// Takes the tile at from, moves it to location 'to', and sets the 'from' to blank (vector<int>{0})
		void movePiece(const vector<int>& from, const vector<int>& to); 
	protected:
		map< vector<int>, vector<int> > board; // The board's internal information.
		int startX, startY; // The start and end X/Y for the board to be displayed at.
		map<vector<int>, string> boardPawnSet;// The strings to be used to display what occupies each space.
		vector<int> boardStats; // Universal board statuses. May be useful, maybe useless.
		WINDOW *win;
		map<vector<int>, int> boardPawnFGCol; // The foreground color to be used to display what occupies each space.
		map<vector<int> , int> cpairMap; // A map for registering color combinations (pairs -> IDs).
		map<int, vector<int> > colorMap; // A map for registering color combinations (IDs -> pairs).
	};
}

#endif // BOARD_HPP_
