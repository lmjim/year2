#include "board.hpp"
#include <vector>
#include <string>
#include <ncurses.h>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;
using namespace board;

/* 
For the soul who is reading this, this is mostly a lot of hacks trying to get ncurses to behave without it screaming and committing suicide at the first 
sight of changing colors.

But nonetheless, this is a chessboard class that will, when interfaced properly, keep track of and display a chessboard to the user. This class mearly handles the 
heavy lifting of the display, as all pieces, colors and the such are defined elsewhere. However, three colors shall be pre-defined in the 1, 2, and 3 COLOR_PAIRS
Namely, black, white and red (border) [both background and foreground should be defined as those colors]. 
*/

// Default Constructor: default chess board
Board::Board(){
	vector<int> args = vector<int>{3, 3, 7}; // Chess board with a width of 7 characters, height of 3 characters, gutter width of 7 characters.
	// Auto-initialized chess board to 8x8
	// 12 spots, 3 width, 1 height, 2 buffer each
	this->boardStats = vector<int>{5 + 8*(2*args.at(0)+1) + 4*(args.at(2)), 3+ 8*args.at(1), 2*args.at(0) + 1, args.at(1), args.at(2)};
	this->startX = (COLS - this->boardStats.at(0))/2; // Center the window in the middle of screen
	this->startY = (LINES - this->boardStats.at(1))/2;
	if(this->startX < 0 || this->startY < 0){
		throw "Screen too small exception.";
	}
	for(int x = -2; x < 10; x++){
			for(int y = 0; y < 8; y++){
					this->board.insert({vector<int>{x,y}, vector<int>{0,0}}); // Initialize all potential spots for the chess board (chess board + 4 columns for the gutters)
			}
	}
	this->boardPawnSet.insert({vector<int>{0,0}, ""}); // Set the "Blank" pawn for the chessboard.
	this->setBoardPiece(vector<int>{-1}, "", COLOR_WHITE);
	this->setBoardPiece(vector<int>{3}, "", COLOR_RED);
	this->win = newwin(this->boardStats.at(1), this->boardStats.at(0), this->startY, this->startX); // Create the window in ncurses

	setColorPair(COLOR_RED, COLOR_BLACK, 1); // Black tile
	setColorPair(COLOR_BLUE,COLOR_WHITE, 2); // White tile
	setColorPair(COLOR_RED, COLOR_RED, 3); // Red border
	
}

/*Constructor: Takes arguments (in args) width, height, gutter_width
Constructs an 8x8 chessboard with 2x8 gutters on the left and right side.
The width of every chess cell is 2*width + 1 [in characters width]
The height of every chess cell is height [in character height]
The width of the gutter width is gutter_width [in character width]
*/
Board::Board(const vector<int>& args){
	// Auto-initialized chess board to 8x8
	// 12 spots, 3 width, 1 height, 2 buffer each
	this->boardStats = vector<int>{4 + 8*(2*args.at(0)+1) + 4*(args.at(2)), 2+ 8*args.at(1), 2*args.at(0) + 1, args.at(1), args.at(2)};
	this->startX = (COLS - this->boardStats.at(0))/2; // Center the window in the middle of screen
	this->startY = (LINES - this->boardStats.at(1))/2;
	for(int x = -2; x < 10; x++){
		for(int y = 0; y < 8; y++){
			this->board.insert({vector<int>{x,y}, vector<int>{0,0}}); // Initialize all potential spots for the chess board (chess board + 4 columns for the gutters)
		}
	}
	this->boardPawnSet.insert({vector<int>{0,0}, ""}); // Set the "Blank" pawn for the chessboard.
	
	this->setBoardPiece(vector<int>{-1}, "", COLOR_WHITE);
	this->win = newwin(this->boardStats.at(1), this->boardStats.at(0), this->startY, this->startX); // Create the window in ncurses
	setColorPair(COLOR_RED, COLOR_BLACK, 1); // Black tile
	setColorPair(COLOR_BLUE,COLOR_WHITE, 2); // White tile
	setColorPair(COLOR_RED, COLOR_RED, 3); // Red border
	this->setBoardPiece(vector<int>{3}, "", COLOR_RED);
}

Board::~Board(){
	// Deconstructor
	delwin(this->win);
}

/*
Arguments vector:
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
template <typename T>
static void printDebug(const vector<T>& args){
	
}


void Board::displayLine(const vector<int>& args, string line){
	// ARGS VECTOR: POSX, POSY, SIZEX, SIZEY, COLOR_PAIR_INDEX, TOKEN_FOREGROUND_COLOR
	// Along with the line to draw.
	// Note: SIZEY > 1 will call this function over and over, placing line on the center line(-ish, to lower half).
	if(args.at(2) <= 0 || args.at(3) <= 0){
		cerr << "Bad arguments for Chessboard displayLine! Sizes can not be negative or zero!!" << endl;
		return; // Bad arguments!
	}
	if(args.at(2) + args.at(0) > this->boardStats.at(0) || args.at(0) < 0 || args.at(1) < 0 || args.at(3) + args.at(1) > this->boardStats.at(1)){
		cerr << "Bad arguments for Chessboard displayLine! Drawing position is out of bounds!"<<args.at(2) << " " << this->boardStats.at(0) <<  " " <<args.at(3) << " " <<this->boardStats.at(1) << " " << args.at(0) << " "<< args.at(1) << endl; 
		return; // Bad arguments!
	}
	if(line.length() == 0){
		// No string to render, just render a square of "white"-space
		wattron(this->win,COLOR_PAIR(args.at(4))); // Set the color to the COLOR_PAIR_INDEX
		for(int i = 0; i < args.at(3); i++){
			for(int j = 0; j < args.at(2); j++){
				mvwaddch(this->win, i + args.at(1), j + args.at(0),' '); // Draw the "white"-space character to the screen.
			}
		}
		wattroff(this->win,COLOR_PAIR(args.at(4))); 
		// Reset the color.
	}else{
		int w = line.length(); // Get the length of the string to render
		if(w > args.at(2)){ // Don't allow strings that are larger than the cells to be rendered.
			cerr << "Size of string is bigger than area to render it in" << endl;
			return; // Bad argument!!!
		}
		int rx = (args.at(2) - (w))/2; // Center the string in the X direction
		int h = (args.at(3))/2; // Center the string in the Y direction
		for(int y = 0; y < args.at(3); y++){
			if(y != h){
				//Render blank line, calls this function with empty string
				this->displayLine(vector<int>{args.at(0), y+args.at(1), args.at(2), 1, args.at(4)}, "");
			}else{
				// determine what color we need from the 5th param and the background of the 4th param
				int bg = (this->colorMap.at(args.at(4))).at(1);
				int fg = this->boardPawnFGCol.at(vector<int>{(args.at(5))});
				int CPID = 0; // Color Pair ID
				if(this->cpairMap.find(vector<int>{fg, bg}) == this->cpairMap.end()){ // See if the color pair exists already
					//Doesn't exist. Add it to the list.
					int size = this->cpairMap.size() + 1; // Colors are indexed starting at 1, so shift the size by 1.
					this->setColorPair(fg, bg, size);
					CPID = size;
				}else{	
					//Does exist, get the color pair ID
					CPID = this->cpairMap.at(vector<int>{fg, bg}); // Gets the color pair ID from map
				}
				wattron(this->win, COLOR_PAIR(CPID)); // Set the foreground and background colors
				for(int x = 0; x < args.at(2); x++){
					if(x < rx){ // If we are rendering a string before characters should be appears (left white-space fill)
						mvwaddch(this->win, y + args.at(1), x + args.at(0), ' ');
					}else if(x < rx + w){ // Render the characters of the string
						mvwaddch(this->win, y + args.at(1), x + args.at(0), line.at(x - rx));
					}else{ // Render whitespace at the end of the string to right fill
						mvwaddch(this->win, y + args.at(1), x + args.at(0), ' ');
					}
				}
				wattroff(this->win, COLOR_PAIR(CPID)); // Turn off the foreground/background colors
			}
		}
	}
}

// This function draws a SINGLE cell, however, only draws the space character (so effectively sets a single background)
void Board::setTileDisplay(const vector<int>& args){
	// Simply colors a SINGLE square on the screen.
	// ARGS VECTOR: POSX, POSXY, COLOR_PAIR_INDEX
	if(args.at(0)>= this->boardStats.at(0) || args.at(0) < 0 || args.at(1) < 0 || args.at(1) >= this->boardStats.at(1)){
		cerr << "Bad arguments for Chessboard displayLine! Drawing position is out of bounds!" << endl;
		return;
	}
	wattron(this->win, COLOR_PAIR(args.at(2))); 
	mvwaddch(this->win, args.at(1), args.at(0), ' ');
	wattroff(this->win, COLOR_PAIR(args.at(2)));
}
		
// This function will tell ncurses to refresh the CHESSBOARD screen and draw any changes.
void Board::showScreen(){
	// Simply refresh the board's display!
	wrefresh(this->win);
}		

/*
This function will tell ncurses to clear the CHESSBOARD screen. 
Note: this does not mean it will update the display, you need to call showScreen.
*/
void Board::clearScreen(){
	//Clears the board's screen by writing over every tile.
	for(int i = 0; i < this->boardStats.at(0); i++){
		for(int j = 0; j < this->boardStats.at(1); j++){
			mvwaddch(this->win,j,i,' ');
		}
	}
}
		

// This function will draw the board to the CHESSBOARD screen, but will not update the display.
void Board::displayBoard(){
	// Display the chess board
	//Draw the four corners of the border
	this->displayLine(vector<int>{1+2 * this->boardStats.at(4), 0,2,1,3},"");
	this->displayLine(vector<int>{3 + 2 * this->boardStats.at(4) + 8 * this->boardStats.at(2), 0,2,1,3},"");
	this->displayLine(vector<int>{1+2 * this->boardStats.at(4), 1+ 8*this->boardStats.at(3),2,1,3},"");
	this->displayLine(vector<int>{3 + 2 * this->boardStats.at(4) + 8 * this->boardStats.at(2), 1+ 8*this->boardStats.at(3),2,1,3},"");
	
	
	
	for(int y = 0; y < 8; y++){
		
		for(int x = -2; x <10; x++){
			if(x < 0){ // Display the left gutter
				this->displayLine(
					vector<int>{
						(x+2)* this->boardStats.at(4), 
						1+ this->boardStats.at(3) * y, 
						this->boardStats.at(4), 
						this->boardStats.at(3), 
						1,
						(this->board.at(vector<int>{x,y})).at(0)
					},
					this->boardPawnSet.at((this->board.at(vector<int>{x,y})))
				);
			}else if(x >= 8){ // Display the right gutter
				this->displayLine(
					vector<int>{
						5+ (x-6)* this->boardStats.at(4) + 8 * this->boardStats.at(2), 
						1+ this->boardStats.at(3) * y, 
						this->boardStats.at(4), 
						this->boardStats.at(3), 
						1,
						(this->board.at(vector<int>{x,y})).at(0)
					},
					this->boardPawnSet.at((this->board.at(vector<int>{x,y})))
				);
			}else{ // Display the actual chess board
				this->displayLine(
					vector<int>{
						3+ 2* this->boardStats.at(4) + x * this->boardStats.at(2), 
						1+ this->boardStats.at(3) * y, 
						this->boardStats.at(2), 
						this->boardStats.at(3), 
						!((x ^ y) & 0x1) + 1, 
						(this->board.at(vector<int>{x,y})).at(0)
					},
					this->boardPawnSet.at((this->board.at(vector<int>{x,y})))
				);
			}
			//This will render the squares of the chess board, along with rendering the entity on the square.
			
		}
		this->displayLine(
			vector<int>{
				2 * this->boardStats.at(4),
				1 + this->boardStats.at(3) * y,
				1,
				this->boardStats.at(3),
				1,
				-1
			}, to_string(y)
		);
		this->displayLine(
			vector<int>{
				3 + 2* this->boardStats.at(4) + y * this->boardStats.at(2),
				2 + 8 * this->boardStats.at(3),
				this->boardStats.at(4),
				1,
				1,
				-1
			}, to_string(y)
		);
		// Display the border
		this->displayLine(vector<int>{3+ 2* this->boardStats.at(4) + y * this->boardStats.at(2),0,this->boardStats.at(2),1,3}, "");// Top border of the chessboard (3, for red outline)
		this->displayLine(vector<int>{3+ 2* this->boardStats.at(4) + y * this->boardStats.at(2),0+ this->boardStats.at(3) * 8 + 1,this->boardStats.at(2),1,3}, "");// Bottom border of the chessboard (3, for red outline)
		this->displayLine(vector<int>{1+ 2 * this->boardStats.at(4),1 + this->boardStats.at(3) * y,2,this->boardStats.at(3),3}, "");// Left border of the chessboard (3, for red outline)
		this->displayLine(vector<int>{3 + 2 * this->boardStats.at(4) + 8 * this->boardStats.at(2),1 + this->boardStats.at(3) * y,2,this->boardStats.at(3),3}, "");// Right border of the chessboard (3, for red outline)
	}
	this->displayLine(vector<int>{2 * this->boardStats.at(4), 0,1,1,1,-1},"Y");
	this->displayLine(
		vector<int>{
			4+ 2* this->boardStats.at(4) + 8 * this->boardStats.at(2),
			2 + 8 * this->boardStats.at(3),
			1,
			1,
			1,
			-1
		}, "X"
	);

}

// Retrieves the piece at a given location on the board.
vector<int> Board::getPieceAt(const vector<int>& pos){
	return this->board.at(pos);
}

// Sets the tile at 'pos' to have the "piece" newVal.
void Board::setPieceAt(const vector<int>& pos, const vector<int>& newVal){
	auto it = this->board.find(pos);
	if(it != this->board.end()){
		it->second = newVal;
	}else{
		this->board.insert({pos, newVal});
	}
}

// Add a color pair to ncurses to render on the screen. Takes a foreground color, background color, and a pair ID
void Board::setColorPair(int fg, int bg, int id){
	// Create a new color pair (can hold to 256 of them), by creating a two-way mapping of it to its ID.
	this->cpairMap.insert({vector<int>{fg, bg}, id});
	this->colorMap.insert({id, vector<int>{fg,bg}});
	init_pair(id, fg, bg);
}

// This will register a board "piece", with it's ID, its foreground rendering color, its string to display.
void Board::setBoardPiece(vector<int> vec, string str, int fg){
	// Set the board pawn, the string to render for the pawn and the color to render with the pawn.
	this->boardPawnSet.insert({vec, str});
	this->boardPawnFGCol.insert({vec, fg});
}

// Swaps the pieces at the locations from and 'to'
void Board::swapPieces(const vector<int>& from, const vector<int>& to){
	auto temp = this->getPieceAt(from);
	this->setPieceAt(from, this->getPieceAt(to));
	this->setPieceAt(to, temp);
}

// Takes the tile at from, moves it to location 'to', and sets the 'from' to blank (vector<int>{0})
void Board::movePiece(const vector<int>& from, const vector<int>& to){
	this->setPieceAt(to, this->getPieceAt(from));
	this->setPieceAt(from, vector<int>{0});
}
