#include "board.hpp"
#include <vector>
#include <string>
#include <ncurses.h>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;
using namespace board;



// Default Constructor: default agg. board
AggravationBoard::AggravationBoard(){
	vector<int> args{3, 1};
	// Initialize the board to be a 15x15, 3 wide, 1 tall, 2 wide border, 1 tall border...
	// However, there are "blank" spaces, these spaces are meant to isolate
	// 	other spaces.
	this->boardStats = vector<int>{(1 + 1 + 2) + (15*args.at(0) * 2) - args.at(0), (15 * 2*args.at(1))+ (1 + 1) - args.at(1) , args.at(0), args.at(1)};
	
	this->startX = (COLS - this->boardStats.at(0))/2; // Center the window in the middle of screen
	this->startY = (LINES - this->boardStats.at(1))/2;
	if(this->startX < 0 || this->startY < 0){
		throw "Screen too small exception.";
	}
	for(int x = 0; x < 15; x++){
			for(int y = 0; y < 15; y++){
					this->board.insert({vector<int>{x,y}, vector<int>{0,-1}}); // Initialize all potential spots for the agg. board
			}
	}
	
	
	this->boardPawnSet.insert({vector<int>{0,0}, ""}); // Set the "not rendered" spot...
	this->boardPawnSet.insert({vector<int>{0,-1}, ""}); // Set the "not rendered" spot...
	
	vector<short> player_colors{COLOR_RED, COLOR_BLUE, COLOR_GREEN, COLOR_MAGENTA};
	for(int i = 0; i < 4; i++){
		//add 1 to i to get player number (1 - 4)
		this->setBoardPiece(vector<int>{i+1}, "", player_colors.at(i)); // Set the player color...
		for(int j = 0; j < 4; j++){
			this->setBoardPiece(vector<int>{i+1,j+1}, to_string(j+1), player_colors.at(i)); // Player i is col, 0 is active pawn
		}
		setColorPair(COLOR_WHITE, player_colors.at(i), i+1); // Color/base tokens
	}
	this->setBoardPiece(vector<int>{0}, "", COLOR_WHITE); // Set the player color...
	this->setBoardPiece(vector<int>{5}, "", COLOR_WHITE); // Set the player color...
	this->setBoardPiece(vector<int>{6}, "", COLOR_BLACK); // Set the player color...
	
	
	this->win = newwin(this->boardStats.at(1), this->boardStats.at(0), this->startY, this->startX); // Create the window in ncurses

	setColorPair(COLOR_WHITE, COLOR_WHITE, 5); // White tile
	setColorPair(COLOR_BLACK, COLOR_BLACK, 6); // Black tile
	setColorPair(COLOR_CYAN, COLOR_CYAN, 7); // Red tile
	
	
	
	
}



AggravationBoard::~AggravationBoard(){
	// Deconstructor
	delwin(this->win);
}


template <typename T>
static void printDebug(const vector<T>& args){
	
}

/*
Arguments vector:
	POSX: Starting position x to draw,
	POSY: Starting position y to draw,
	SIZEX: Width of the cell to draw,
	SIZEY: Height of the cell to draw,
	COLOR_PAIR_INDEX: The color pair to draw the cell with
	COLOR_BACKGROUND_INDEX: For rendering cells with text, this sets the background to a DIFFERENT color when not rendering the token, useful for isolating the token identifier. (UNUSED DUE TO DESIGN DECISION ON 3/4/19)
	TOKEN_FOREGROUND_COLOR: The color to draw the text with
	The line is the string to render in the center of the tile.
	This function draws a string, centered vertically and horizontally in a cell
	The cell is drawn at the position X,Y (top left corner) and has a size of X,Y
*/
void AggravationBoard::displayLine(const vector<int>& args, string line){
	// ARGS VECTOR: POSX, POSY, SIZEX, SIZEY, COLOR_PAIR_INDEX, COLOR_BACKGROUND_INDEX, TOKEN_FOREGROUND_COLOR
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
		wattron(this->win,COLOR_PAIR(args.at(5))); // Set the color to the COLOR_PAIR_INDEX
		for(int i = 0; i < args.at(3); i++){
			for(int j = 0; j < args.at(2); j++){
				mvwaddch(this->win, i + args.at(1), j + args.at(0),' '); // Draw the "white"-space character to the screen.
			}
		}
		wattroff(this->win,COLOR_PAIR(args.at(5))); 
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
				this->displayLine(vector<int>{args.at(0), y+args.at(1), args.at(2), 1, args.at(4), args.at(5)}, "");
			}else{
				// determine what color we need from the 5th param and the background of the 4th param
				int bg = (this->colorMap.at(args.at(4))).at(1);
				int fg = this->boardPawnFGCol.at(vector<int>{(args.at(6))});
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
					if(x == rx){
						wattroff(this->win, COLOR_PAIR(CPID)); // Set the foreground and background colors
						wattron(this->win, COLOR_PAIR(CPID)); // Set the foreground and background colors
						
					}
					if(x == rx + w){
						wattroff(this->win, COLOR_PAIR(CPID)); // Set the foreground and background colors
						wattron(this->win, COLOR_PAIR(CPID)); // Set the foreground and background colors
					}
					if(x < rx){ // If we are rendering a string before characters should be appears (left white-space fill)
						mvwaddch(this->win, y + args.at(1), x + args.at(0), ' ');
					}else if(x < rx + w){ // Render the characters of the string
						mvwaddch(this->win, y + args.at(1), x + args.at(0), line.at(x - rx));
					}else{ // Render whitespace at the end of the string to right fill
						mvwaddch(this->win, y + args.at(1), x + args.at(0), ' ');
					}
				}
				wattroff(this->win, COLOR_PAIR(CPID)); // Turn off the foreground/background colors
				wattroff(this->win, COLOR_PAIR(CPID)); // Set the foreground and background colors
			}
		}
	}
}

// This function draws a SINGLE cell, however, only draws the space character (so effectively sets a single background)
void AggravationBoard::setTileDisplay(const vector<int>& args){
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
void AggravationBoard::showScreen(){
	// Simply refresh the board's display!
	wrefresh(this->win);
}		

/*
This function will tell ncurses to clear the CHESSBOARD screen. 
Note: this does not mean it will update the display, you need to call showScreen.
*/
void AggravationBoard::clearScreen(){
	//Clears the board's screen by writing over every tile.
	for(int i = 0; i < this->boardStats.at(0); i++){
		for(int j = 0; j < this->boardStats.at(1); j++){
			mvwaddch(this->win,j,i,' ');
		}
	}
}
		

// A function for determining the color to display the token with, depending on the background color...
// 		Piece's will either render themselves, or will render black/white if the colors match
// Tile color is the color of the tile, Piece Color is the color of the piece.
int changeColorOnOtherSquares(int tileColor, int pieceColor){
	if(tileColor == pieceColor){
		if(pieceColor != 3){
			// Make the piece white when rendered on its own tiles...
			return 5;
		}else{
			// Make the piece black when rendered on its own tiles.
			return 6;
		}
	}
	return pieceColor;
}
// A function that is literally just to shorten calling the function above.
int CCOOS(int tileColor, int pieceColor){
	return changeColorOnOtherSquares(tileColor, pieceColor);
}

// This function will draw the board to the CHESSBOARD screen, but will not update the display.
void AggravationBoard::displayBoard(){
	// Draw numbers/indexing...
	/*for(int i = 0; i < 15; i++){
		this->displayLine(vector<int>{
			2 + 2 * (this->boardStats.at(2) * (i+1)) - this->boardStats.at(2),
			2 + 2 * (this->boardStats.at(3) * 15) - 1,
			2,
			this->boardStats.at(3),
			6,
			0
		}, to_string(i));
		this->displayLine(vector<int>{
			0,
			2 * (i + 1) - 1,
			2,
			this->boardStats.at(3),
			6,
			0
		}, to_string(i));
	}
	this->displayLine(vector<int>{
		0,
		0,
		2,
		1,
		6,
		0
	}, "Y");
	
	this->displayLine(vector<int>{
		5 + 2 * (this->boardStats.at(2) * (15)) - this->boardStats.at(2),
		2 + 2 * (this->boardStats.at(3) * 15) - 1,
		1,
		1,
		6,
		0
	}, "X");
	*/
	// Draw the border
	this->displayLine(vector<int>{
		0,
		0,
		2*this->boardStats.at(2) * 15 + 4 - this->boardStats.at(2),
		1,
		7,
		7,
		0
	}, "");
	this->displayLine(vector<int>{
		0,
		2 * this->boardStats.at(3) * 15 + 1 - this->boardStats.at(3),
		2 * this->boardStats.at(2) * 15 + 4 - this->boardStats.at(2),
		1,
		7,
		7,
		0
	}, "");
	this->displayLine(vector<int>{
		0,
		0,
		2,
		2*this->boardStats.at(3) * 15 + 2 - this->boardStats.at(3),
		7,
		7,
		0
	}, "");
	this->displayLine(vector<int>{
		this->boardStats.at(2) * 2 * 15 + 2 - this->boardStats.at(2),
		0,
		2,
		2*this->boardStats.at(3) * 15 + 2 - this->boardStats.at(3),
		7,
		7,
		0
	}, "");
	
	/*
		Notes: The rendering of pawns HAS to occur in the following functions
			otherwise, the logic for determining what piece goes where needs
			to be effectively repeated.
	*/
	
	
	//Now display base/home areas..
	for(int i = 1; i < 5; i++){
		//red's base
		this->displayLine(vector<int>{
			2 + 2 * this->boardStats.at(2) * (i),
			1 + 2* this->boardStats.at(3) * (i),
			this->boardStats.at(2),
			this->boardStats.at(3),
			1,
			1,
			CCOOS(1,(this->board.at(vector<int>{i,i})).at(0))
		}, this->boardPawnSet.at((this->board.at(vector<int>{i,i}))));
		
		//red's home
		this->displayLine(vector<int>{
			2 + 2* this->boardStats.at(2) * 7 ,
			1 + 2*this->boardStats.at(3) * (i),
			this->boardStats.at(2),
			this->boardStats.at(3),
			1,
			1,
			CCOOS(1,(this->board.at(vector<int>{7,i})).at(0))
		}, this->boardPawnSet.at((this->board.at(vector<int>{7,i}))));
		
		//blue's base
		this->displayLine(vector<int>{
			2 + 2* this->boardStats.at(2) * (14 - i),
			1 + 2* this->boardStats.at(3) * i,
			this->boardStats.at(2),
			this->boardStats.at(3),
			2,
			2,
			CCOOS(2, (this->board.at(vector<int>{14-i,i})).at(0))
		}, this->boardPawnSet.at((this->board.at(vector<int>{14-i,i}))));
		
		//blue's home
		this->displayLine(vector<int>{
			2 + 2* this->boardStats.at(2) * (14 -i) ,
			1 + 2*this->boardStats.at(3) * 7,
			this->boardStats.at(2),
			this->boardStats.at(3),
			2,
			2,
			CCOOS(2,(this->board.at(vector<int>{14-i,7})).at(0))
		}, this->boardPawnSet.at((this->board.at(vector<int>{14-i,7}))));
		
		//green's base 
		this->displayLine(vector<int>{
			2 + 2*this->boardStats.at(2) * (14 - i),
			1 + 2*this->boardStats.at(3) * (14 - i),
			this->boardStats.at(2),
			this->boardStats.at(3),
			3,
			3,
			CCOOS(3,(this->board.at(vector<int>{14-i,14-i})).at(0))
		}, this->boardPawnSet.at((this->board.at(vector<int>{14-i,14-i}))));
		
		//green's home
		this->displayLine(vector<int>{
			2 + 2* this->boardStats.at(2) * 7 ,
			1 + 2*this->boardStats.at(3)* (14 - i),
			this->boardStats.at(2),
			this->boardStats.at(3),
			3,
			3,
			CCOOS(3,(this->board.at(vector<int>{7,14-i})).at(0))
		}, this->boardPawnSet.at((this->board.at(vector<int>{7,14-i}))));
		
		//magenta's base
		this->displayLine(vector<int>{
			2 + 2*this->boardStats.at(2) * i,
			1 + 2*this->boardStats.at(3) * (14-i),
			this->boardStats.at(2),
			this->boardStats.at(3),
			4,
			4,
			CCOOS(4,(this->board.at(vector<int>{i,14-i})).at(0))
		}, this->boardPawnSet.at((this->board.at(vector<int>{i,14-i}))));
		
		//magenta's home
		this->displayLine(vector<int>{
			2 + 2* this->boardStats.at(2) * (i) ,
			1 + 2*this->boardStats.at(3) * 7,
			this->boardStats.at(2),
			this->boardStats.at(3),
			4,
			4,
			CCOOS(4,(this->board.at(vector<int>{i,7})).at(0))
		}, this->boardPawnSet.at((this->board.at(vector<int>{i,7}))));
		
	}
	
	this->displayLine(vector<int>{
		2 + 2 * this->boardStats.at(2) * 7,
		1 + 2 * this->boardStats.at(3) * 7,
		this->boardStats.at(2),
		this->boardStats.at(3),
		5,
		5,
		CCOOS(5, (this->board.at(vector<int>{7,7})).at(0))
	}, this->boardPawnSet.at((this->board.at(vector<int>{7,7}))));
	
	// Now for the fun part, the board itself!
	for(int i = 0; i < 6; i++){
		// Left side
		this->displayLine(vector<int>{
			2 + 2 * this->boardStats.at(2) * (i),
			1 + 2 * this->boardStats.at(3) * 5,
			this->boardStats.at(2),
			this->boardStats.at(3),
			5,
			5,
			CCOOS(5, (this->board.at(vector<int>{i,5})).at(0))
		}, this->boardPawnSet.at((this->board.at(vector<int>{i,5}))));
		
		this->displayLine(vector<int>{
			2 + 2 * this->boardStats.at(2) * (i),
			1 + 2 * this->boardStats.at(3) * 9,
			this->boardStats.at(2),
			this->boardStats.at(3),
			5,
			5,
			CCOOS(5, (this->board.at(vector<int>{i,9})).at(0))
		}, this->boardPawnSet.at((this->board.at(vector<int>{i,9}))));
		// Right side
		this->displayLine(vector<int>{
			2 + 2 * this->boardStats.at(2) * (14 - i),
			1 + 2 * this->boardStats.at(3) * 5,
			this->boardStats.at(2),
			this->boardStats.at(3),
			5,
			5,
			CCOOS(5, (this->board.at(vector<int>{14-i,5})).at(0))
		}, this->boardPawnSet.at((this->board.at(vector<int>{14-i,5}))));
		
		this->displayLine(vector<int>{
			2 + 2 * this->boardStats.at(2) * (14 - i),
			1 + 2 * this->boardStats.at(3) * 9,
			this->boardStats.at(2),
			this->boardStats.at(3),
			5,
			5,
			CCOOS(5, (this->board.at(vector<int>{14-i,9})).at(0))
		}, this->boardPawnSet.at((this->board.at(vector<int>{14-i,9}))));
		// Top side
		this->displayLine(vector<int>{
			2 + 2 * this->boardStats.at(2) * 5,
			1 + 2 * this->boardStats.at(3) * i,
			this->boardStats.at(2),
			this->boardStats.at(3),
			5,
			5,
			CCOOS(5, (this->board.at(vector<int>{5,i})).at(0))
		}, this->boardPawnSet.at((this->board.at(vector<int>{5,i}))));
		
		this->displayLine(vector<int>{
			2 + 2 * this->boardStats.at(2) * (9),
			1 + 2 * this->boardStats.at(3) * i,
			this->boardStats.at(2),
			this->boardStats.at(3),
			5,
			5,
			CCOOS(5, (this->board.at(vector<int>{9,i})).at(0))
		}, this->boardPawnSet.at((this->board.at(vector<int>{9,i}))));
		// Bottom side
		this->displayLine(vector<int>{
			2 + 2 * this->boardStats.at(2) * 5,
			1 + 2 * this->boardStats.at(3) * (14-i),
			this->boardStats.at(2),
			this->boardStats.at(3),
			5,
			5,
			CCOOS(5, (this->board.at(vector<int>{5,14-i})).at(0))
		}, this->boardPawnSet.at((this->board.at(vector<int>{5,14-i}))));
		
		this->displayLine(vector<int>{
			2 + 2 * this->boardStats.at(2) * (9),
			1 + 2 * this->boardStats.at(3) * (14-i),
			this->boardStats.at(2),
			this->boardStats.at(3),
			5,
			5,
			CCOOS(5, (this->board.at(vector<int>{9,14-i})).at(0))
		}, this->boardPawnSet.at((this->board.at(vector<int>{9,14-i}))));
	}	

	// Rendering the "edges" for each player, only 3 spaces, one colored...
	int startingSquare = 10;
	for(int i = 0; i < 4; i++){
		this->displayLine(vector<int>{
			2 + 2 * this->boardStats.at(2) * (8 - i),
			1 + 2 * this->boardStats.at(3) * 14,
			this->boardStats.at(2),
			this->boardStats.at(3),
			(i == startingSquare ? 3 : 5),
			(i == startingSquare ? 3 : 5),
			CCOOS((i == startingSquare ? 3 : 5),(this->board.at(vector<int>{8-i,14})).at(0))
		}, this->boardPawnSet.at((this->board.at(vector<int>{8-i,14}))));
		
		this->displayLine(vector<int>{
			2 + 2 * this->boardStats.at(2) * (6 + i),
			1,
			this->boardStats.at(2),
			this->boardStats.at(3),
			(i == startingSquare ? 1 : 5),
			(i == startingSquare ? 1 : 5),
			CCOOS((i == startingSquare ? 1 : 5), (this->board.at(vector<int>{6+i,0})).at(0))
		}, this->boardPawnSet.at((this->board.at(vector<int>{6+i,0}))));
		
		this->displayLine(vector<int>{
			2 + 2 * this->boardStats.at(2) * 14,
			1 + 2 * this->boardStats.at(3) * (6+i),
			this->boardStats.at(2),
			this->boardStats.at(3),
			(i == startingSquare ? 2 : 5),
			(i == startingSquare ? 2 : 5),
			CCOOS((i == startingSquare ? 2 : 5),(this->board.at(vector<int>{14,6+i})).at(0))
		}, this->boardPawnSet.at((this->board.at(vector<int>{14,6+i}))));
		
		this->displayLine(vector<int>{
			2,
			1 + 2 * this->boardStats.at(3) *(8-i),
			this->boardStats.at(2),
			this->boardStats.at(3),
			(i == startingSquare ? 4 : 5),
			(i == startingSquare ? 4 : 5),
			CCOOS((i == startingSquare ? 4 : 5),(this->board.at(vector<int>{0,8-i})).at(0))
		}, this->boardPawnSet.at((this->board.at(vector<int>{0,8-i}))));
	}
	
	
	
	
	

}

// Retrieves the piece at a given location on the board.
vector<int> AggravationBoard::getPieceAt(const vector<int>& pos){
	return this->board.at(pos);
}

// Sets the tile at 'pos' to have the "piece" newVal.
void AggravationBoard::setPieceAt(const vector<int>& pos, const vector<int>& newVal){
	auto it = this->board.find(pos);
	if(it != this->board.end()){
		it->second = newVal;
	}else{
		this->board.insert({pos, newVal});
	}
}

// Add a color pair to ncurses to render on the screen. Takes a foreground color, background color, and a pair ID
void AggravationBoard::setColorPair(int fg, int bg, int id){
	// Create a new color pair (can hold to 256 of them), by creating a two-way mapping of it to its ID.
	this->cpairMap.insert({vector<int>{fg, bg}, id});
	this->colorMap.insert({id, vector<int>{fg,bg}});
	init_pair(id, fg, bg);
}

// This will register a board "piece", with it's ID, its foreground rendering color, its string to display.
void AggravationBoard::setBoardPiece(vector<int> vec, string str, int fg){
	// Set the board pawn, the string to render for the pawn and the color to render with the pawn.
	this->boardPawnSet.insert({vec, str});
	this->boardPawnFGCol.insert({vec, fg});
}

// Swaps the pieces at the locations from and 'to'
void AggravationBoard::swapPieces(const vector<int>& from, const vector<int>& to){
	auto temp = this->getPieceAt(from);
	this->setPieceAt(from, this->getPieceAt(to));
	this->setPieceAt(to, temp);
}

// Takes the tile at from, moves it to location 'to', and sets the 'from' to blank (vector<int>{0})
void AggravationBoard::movePiece(const vector<int>& from, const vector<int>& to){
	this->setPieceAt(to, this->getPieceAt(from));
	this->setPieceAt(from, vector<int>{0});
}
