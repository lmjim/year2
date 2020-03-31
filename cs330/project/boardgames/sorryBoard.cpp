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
SorryBoard::SorryBoard(){
	vector<int> args{3, 1};
	// Initialize the board to be a 15x15, 3 wide, 1 tall, 2 wide border, 1 tall border...
	// However, there are "blank" spaces, these spaces are meant to isolate
	// 	other spaces.
	this->boardStats = vector<int>{(1 + 1 + 2) + ((2 * 16 - 1)*args.at(0)), ((2 * 16 - 1)*args.at(1))+ (1 + 1), args.at(0), args.at(1)};
	this->startX = (COLS - this->boardStats.at(0))/2; // Center the window in the middle of screen
	this->startY = (LINES - this->boardStats.at(1))/2;
	if(this->startX < 0 || this->startY < 0){
		throw "Screen too small exception.";
	}
	for(int x = 0; x < 16; x++){
			for(int y = 0; y < 16; y++){
					this->board.insert({vector<int>{x,y}, vector<int>{0,0}}); // Initialize all potential spots for the agg. board
			}
	}
	std::cout << "DASdfa" << std::endl;
	auto aa = this->board.at(vector<int>{2,12});
	std::cout << "DASsadajsddfa" << aa[0] << aa[1] <<  std::endl;
	
	
	this->boardPawnSet.insert({vector<int>{0,0}, ""}); // Set the "not rendered" spot...
	
	vector<short> player_colors{COLOR_RED, COLOR_BLUE, COLOR_GREEN, COLOR_MAGENTA};
	for(int i = 0; i < 4; i++){
		//add 1 to i to get player number (1 - 4)
		this->setBoardPiece(vector<int>{i+1}, "", player_colors.at(i)); // Set the player color...
		for(int j = 0; j < 4; j++){
			this->setBoardPiece(vector<int>{i+1,j+1}, to_string(j+1), player_colors.at(i)); // Player i is col, j is pawn number.
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

void SorryBoard::flashToken(const vector<int>& pos, attr_t attributes){
	// first get the position...
	int fg = this->board.at(pos).at(0);
	int bg = ((pos.at(0) == 0 || pos.at(0) == 15) || (pos.at(1) == 0 || pos.at(1) == 15)) ? 5 : -1;
	if(bg == -1){
		// Determine the tile color...
		
	}
	std::string pawnStr = this->boardPawnSet.at(this->board.at(pos));
	if(pawnStr.length() == 0){
		// apply it to the whole cell
		//mvwchgat(this->win, 0,0 ,this->boardStats.at(3), attributes, NULL, NULL);
	}else{
		// apply it to only the character token...
	}
}


SorryBoard::~SorryBoard(){
	// Deconstructor
	delwin(this->win);
}


template <typename T>
static void printDebug(const vector<T>& args){
	
}

int SorryBoard::getColAlt(int fg){
	if(fg == COLOR_YELLOW || fg == COLOR_GREEN || fg == COLOR_MAGENTA){
		// set as black instead of white
		return COLOR_BLACK;
	}else{
		return COLOR_WHITE;
		// set as white...
	}
}

/*
Arguments vector:
	POSX: Starting position x to draw,
	POSY: Starting position y to draw,
	SIZEX: Width of the cell to draw,
	SIZEY: Height of the cell to draw,
	COLOR_PAIR_INDEX: The color pair to draw the cell with
	TOKEN_FOREGROUND_COLOR: The color to draw the text with
	FOREGROUND_BACKUP: The foreground color to draw the text with if they are equal
	The line is the string to render in the center of the tile.
	This function draws a string, centered vertically and horizontally in a cell
	The cell is drawn at the position X,Y (top left corner) and has a size of X,Y
*/
void SorryBoard::displayLine(const vector<int>& args, string line){
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
				if(fg == bg){
					fg = this->getColAlt(fg);
				}
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

// Same arguments as the function above.
void SorryBoard::repeatLine(const vector<int>& args, string line, bool horizontally){
	if(line.length() == 0){
		// Just pass it off, since no characters are being displayed.
		this->displayLine(args, line);
	}else{
		int w = line.length(); // Get the length of the string to render
		if((w > args.at(2) && horizontally) ||(!horizontally && w > args.at(3))){ // Don't allow strings that are larger than the cells to be rendered.
			cerr << "Size of string is bigger than area to render it in" << endl;
			return; // Bad argument!!!
		}
		int rx = 0;
		if(horizontally){
			rx = (args.at(2) - (w))/2; // Center the string in the X direction
		}else{
			rx = (args.at(2) - 1)/2;
		}
		int h = (args.at(3))/2; // Center the string in the Y direction
		int ry = (args.at(3) - w)/2;
		for(int y = 0; y < args.at(3); y++){
			if(y != h && horizontally){
				//Render blank line, calls this function with empty string
				this->displayLine(vector<int>{args.at(0), y+args.at(1), args.at(2), 1, args.at(4), args.at(5)}, "");
			}else{
				// determine what color we need from the 5th param and the background of the 4th param
				int bg = (this->colorMap.at(args.at(4))).at(1);
				int fg = this->boardPawnFGCol.at(vector<int>{(args.at(5))});
				if(fg == bg){
					fg = this->getColAlt(fg);
				}
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
					if(x < rx && !horizontally){ // If we are rendering a string before characters should be appears (left white-space fill)
						mvwaddch(this->win, y + args.at(1), x + args.at(0), ' ');
					}else if(horizontally || x == rx){ // Render the characters of the string
						if(horizontally){
							mvwaddch(this->win, y + args.at(1), x + args.at(0), line.at(((((x - rx) % w) + w)% w)));
						}else{
							try{
								mvwaddch(this->win, y + args.at(1), x + args.at(0), line.at((((y - ry)%w) + w)%w));
							}catch(...){
								throw std::vector<int>{};
							}
						}
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
void SorryBoard::setTileDisplay(const vector<int>& args){
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
void SorryBoard::showScreen(){
	// Simply refresh the board's display!
	wrefresh(this->win);
}		

/*
This function will tell ncurses to clear the CHESSBOARD screen. 
Note: this does not mean it will update the display, you need to call showScreen.
*/
void SorryBoard::clearScreen(){
	//Clears the board's screen by writing over every tile.
	for(int i = 0; i < this->boardStats.at(0); i++){
		for(int j = 0; j < this->boardStats.at(1); j++){
			mvwaddch(this->win,j,i,' ');
		}
	}
}
		

// This function will draw the board to the CHESSBOARD screen, but will not update the display.
void SorryBoard::displayBoard(){
	// Draw the border
	this->displayLine(vector<int>{
		0,
		0,
		this->boardStats.at(2) * (16 * 2 - 1) + 2,
		1,
		7,
		0
	}, "");
	this->displayLine(vector<int>{
		0,
		this->boardStats.at(3) * (16*2 - 1) + 1,
		this->boardStats.at(2) * (16*2 - 1) + 2,
		1,
		7,
		0
	}, "");
	this->displayLine(vector<int>{
		0,
		0,
		2,
		this->boardStats.at(3) * (16*2 - 1) + 2,
		7,
		0
	}, "");
	this->displayLine(vector<int>{
		2 + this->boardStats.at(2) * (2*16 -1),
		0,
		2,
		this->boardStats.at(3) * (2*16-1) + 2,
		7,
		0
	}, "");
	
	
	for(int i = 0; i < 15; i++){
		this->displayLine(vector<int>{
			this->boardStats.at(2) * 2 * i + 2,
			1,
			this->boardStats.at(2),
			this->boardStats.at(3),
			5,
			(this->board.at(vector<int>{i,0})).at(0)
		},this->boardPawnSet.at(this->board.at(vector<int>{i,0})));
		
		this->displayLine(vector<int>{
			this->boardStats.at(2) * 2 * (15 - i) + 2,
			1 + this->boardStats.at(3) * 2 * 15,
			this->boardStats.at(2),
			this->boardStats.at(3),
			5,
			(this->board.at(vector<int>{15-i,15})).at(0)
		},this->boardPawnSet.at(this->board.at(vector<int>{15-i, 15})));
		
		this->displayLine(vector<int>{
			this->boardStats.at(2) * 2 * 15 + 2,
			1 + this->boardStats.at(3) * 2 * i,
			this->boardStats.at(2),
			this->boardStats.at(3),
			5,
			(this->board.at(vector<int>{15,i})).at(0)
		},this->boardPawnSet.at(this->board.at(vector<int>{15,i})));
		
		this->displayLine(vector<int>{
			2,
			1 + this->boardStats.at(3) * 2 * (15-i),
			this->boardStats.at(2),
			this->boardStats.at(3),
			5,
			(this->board.at(vector<int>{0,15-i})).at(0)
		},this->boardPawnSet.at(this->board.at(vector<int>{0,15-i})));
		
	}
	wattron(this->win, A_BOLD);
	for(int i = 0; i < 2*4 + 1; i++){
		this->repeatLine(vector<int>{
			2 + (0 * this->boardStats.at(2)),
			1 + (this->boardStats.at(3) * (2*2 + i)),
			this->boardStats.at(2),
			this->boardStats.at(3),
			((i % 2) == 0 ? 5: 6),
			2
		},"H", false);
		this->repeatLine(vector<int>{
			2 + 15*2 *this->boardStats.at(2),
			1 + (this->boardStats.at(3) * (2*13 - i)),
			this->boardStats.at(2),
			this->boardStats.at(3),
			((i % 2) == 0 ? 5 : 6),
			3
		}, "H", false);
		this->repeatLine(vector<int>{
			2 + (2*6 - i) *this->boardStats.at(2),
			1 + (this->boardStats.at(3) * (2*15)),
			this->boardStats.at(2),
			this->boardStats.at(3),
			((i % 2) == 0 ? 5 : 6),
			1
		}, "=", true);
		this->repeatLine(vector<int>{
			2 + (2*9 + i) *this->boardStats.at(2),
			1 + (this->boardStats.at(3) * (0)),
			this->boardStats.at(2),
			this->boardStats.at(3),
			((i % 2) == 0 ? 5 : 6),
			4
		}, "=", true);
	}
	// Draw the arrows and circles
	this->displayLine(vector<int>{
		2,
		(this->boardStats.at(3) * (2*2 + 9 + 1) - 1),
		this->boardStats.at(2),
		1,
		5,
		2
	},"^");
	this->displayLine(vector<int>{
		2,
		1+(this->boardStats.at(3) * (2*2)),
		this->boardStats.at(2),
		1,
		5,
		2
	},"O");
	
	this->displayLine(vector<int>{
		2 + 2 * 15 * this->boardStats.at(2),
		(this->boardStats.at(3) * (2*14 - 9)),
		this->boardStats.at(2),
		1,
		5,
		3
	},"V");
	this->displayLine(vector<int>{
		2 + 2 * 15 * this->boardStats.at(2),
		(this->boardStats.at(3) * (2*13 + 1)),
		this->boardStats.at(2),
		1,
		5,
		3
	},"O");
	
	this->displayLine(vector<int>{
		2 + (2*6 + 1) * this->boardStats.at(2) - 1,
		1+(this->boardStats.at(3) * (2 * 15)),
		1,
		this->boardStats.at(3),
		5,
		1
	},"<");
	this->displayLine(vector<int>{
		2 + (2*6 - 8) * this->boardStats.at(2),
		1+(this->boardStats.at(3) * (2*15)),
		1,
		this->boardStats.at(3),
		5,
		1
	},"O");
	
	this->displayLine(vector<int>{
		2 + (2*9) * this->boardStats.at(2),
		1+(this->boardStats.at(3) * (2 *0)),
		1,
		this->boardStats.at(3),
		5,
		4
	},">");
	this->displayLine(vector<int>{
		2 + (2*9 + 9) * this->boardStats.at(2) - 1,
		1+(this->boardStats.at(3) * (2*0)),
		1,
		this->boardStats.at(3),
		5,
		4
	},"O");
	
	wattroff(this->win, A_BOLD);
	//sliders
	/*
	//red sliders
	this->repeatLine(vector<int>{
		2 + (this->boardStats.at(2) * 2 * (2)),
		1 + (this->boardStats.at(3) / 2) + (this->boardStats.at(3) * 2 * 15),
		this->boardStats.at(2) * (2 * 4 + 1),
		1,
		1,
		1
	},"", true);
	this->repeatLine(vector<int>{
		2 + (this->boardStats.at(2) * 2 * (11)),
		1 + (this->boardStats.at(3) / 2) + (this->boardStats.at(3) * 2 * 15),
		this->boardStats.at(2) * (2 * 3 + 1),
		1,
		1,
		1
	},"", true);

	// render the arrow part of the sliders
	wattron(this->win, A_BOLD );
	this->displayLine(vector<int>{
		2 + (this->boardStats.at(2)/2),
		1 + 2 * this->boardStats.at(3) * (6) + (this->boardStats.at(3) - 1),
		1,
		1,
		5,
		6
	}, "^");
	this->displayLine(vector<int>{
		2 + (this->boardStats.at(2)/2),
		1 + 2 * this->boardStats.at(3) * (2),
		1,
		1,
		5,
		6
	}, "O");
	
	this->displayLine(vector<int>{
		2 + (this->boardStats.at(2)/2),
		1 + 2 * this->boardStats.at(3) * (14) + (this->boardStats.at(3) - 1),
		1,
		1,
		5,
		6
	}, "^");
	this->displayLine(vector<int>{
		2 + (this->boardStats.at(2)/2),
		1 + 2 * this->boardStats.at(3) * (11),
		1,
		1,
		5,
		6
	}, "O");
	wattroff(this->win, A_BOLD);
	
	*/
	//blue sliders
	/*
	this->repeatLine(vector<int>{
		2 + (this->boardStats.at(2) / 2),
		1 + 2 * this->boardStats.at(3) * (2),
		1,
		this->boardStats.at(3) * (2 * 4 + 1),
		2,
		2
	},"", false);
	this->repeatLine(vector<int>{
		2 + (this->boardStats.at(2) / 2),
		1 + 2 * this->boardStats.at(3) * (11),
		1,
		this->boardStats.at(3) * (2 * 3 + 1),
		2,
		2
	},"", false);
	

	// render the arrow part of the sliders
	wattron(this->win, A_BOLD );
	this->displayLine(vector<int>{
		2 + (this->boardStats.at(2)/2),
		1 + 2 * this->boardStats.at(3) * (6) + (this->boardStats.at(3) - 1),
		1,
		1,
		5,
		6
	}, "^");
	this->displayLine(vector<int>{
		2 + (this->boardStats.at(2)/2),
		1 + 2 * this->boardStats.at(3) * (2),
		1,
		1,
		5,
		6
	}, "O");
	
	this->displayLine(vector<int>{
		2 + (this->boardStats.at(2)/2),
		1 + 2 * this->boardStats.at(3) * (14) + (this->boardStats.at(3) - 1),
		1,
		1,
		5,
		6
	}, "^");
	this->displayLine(vector<int>{
		2 + (this->boardStats.at(2)/2),
		1 + 2 * this->boardStats.at(3) * (11),
		1,
		1,
		5,
		6
	}, "O");
	wattroff(this->win, A_BOLD);
	*/
	for(int i = 0; i < 5; i++){
		//magenta's lane...
		this->displayLine(vector<int>{
			2 + (2*2) * this->boardStats.at(2),
			1 + (2*(1 + i) )* this->boardStats.at(3),
			this->boardStats.at(2),
			this->boardStats.at(3),
			4,
			(this->board.at(vector<int>{2,1+i})).at(0)
		},this->boardPawnSet.at(this->board.at(vector<int>{2,1+i})));
		
		//red's lane...
		this->displayLine(vector<int>{
			2 + (2*13) * this->boardStats.at(2),
			1 + (2*(14 - i) )* this->boardStats.at(3),
			this->boardStats.at(2),
			this->boardStats.at(3),
			1,
			(this->board.at(vector<int>{13,14-i})).at(0)
		},this->boardPawnSet.at(this->board.at(vector<int>{13,14-i})));
		
		//green's lane...
		this->displayLine(vector<int>{
			2 + (2*(14 - i)) * this->boardStats.at(2),
			1 + (2*2 )* this->boardStats.at(3),
			this->boardStats.at(2),
			this->boardStats.at(3),
			3,
			(this->board.at(vector<int>{14-i,2})).at(0)
		},this->boardPawnSet.at(this->board.at(vector<int>{14-i,2})));
		
		//blue's lane...
		this->displayLine(vector<int>{
			2 + (2*(1+i)) * this->boardStats.at(2),
			1 + (2*13)* this->boardStats.at(3),
			this->boardStats.at(2),
			this->boardStats.at(3),
			2,
			(this->board.at(vector<int>{1+i, 13})).at(0)
		},this->boardPawnSet.at(this->board.at(vector<int>{1+i, 13})));
	}
	
	for(int i = 0; i < 4; i++){
		//green's start...
		this->displayLine(vector<int>{
			2 + (2*(8+(i%2))) * this->boardStats.at(2),
			1 + (2*(2 + (i / 2)))* this->boardStats.at(3),
			this->boardStats.at(2),
			this->boardStats.at(3),
			3,
			(this->board.at(vector<int>{8 + (i% 2),2 + (i/2)})).at(0)
		},this->boardPawnSet.at(this->board.at(vector<int>{8 + (i% 2),2 + (i/2)})));
		//green's home
		this->displayLine(vector<int>{
			2 + (2*(12+(i%2))) * this->boardStats.at(2),
			1 + (2*(4 + (i / 2)))* this->boardStats.at(3),
			this->boardStats.at(2),
			this->boardStats.at(3),
			3,
			(this->board.at(vector<int>{12 + (i% 2),4 + (i/2)})).at(0)
		},this->boardPawnSet.at(this->board.at(vector<int>{12 + (i% 2),4 + (i/2)})));
		
		// red's home
		this->displayLine(vector<int>{
			2 + (2*(12+(i%2))) * this->boardStats.at(2),
			1 + (2*(8 + (i / 2)))* this->boardStats.at(3),
			this->boardStats.at(2),
			this->boardStats.at(3),
			1,
			(this->board.at(vector<int>{12 + (i% 2),8 + (i/2)})).at(0)
		},this->boardPawnSet.at(this->board.at(vector<int>{12 + (i%2),8+(i/2)})));
		// red's start
		this->displayLine(vector<int>{
			2 + (2*(10+(i%2))) * this->boardStats.at(2),
			1 + (2*(12 + (i / 2)))* this->boardStats.at(3),
			this->boardStats.at(2),	
			this->boardStats.at(3),
			1,
			(this->board.at(vector<int>{10+ (i% 2),12 + (i/2)})).at(0)
		},this->boardPawnSet.at(this->board.at(vector<int>{10 + (i% 2),12 + (i/2)})));
		
		// magenta's home
		this->displayLine(vector<int>{
			2 + (2*(2+(i%2))) * this->boardStats.at(2),
			1 + (2*(6 + (i / 2)))* this->boardStats.at(3),
			this->boardStats.at(2),
			this->boardStats.at(3),
			4,
			(this->board.at(vector<int>{2 + (i% 2),6 + (i/2)})).at(0)
		},this->boardPawnSet.at(this->board.at(vector<int>{2 + (i%2),6+(i/2)})));
		// magenta's start
		this->displayLine(vector<int>{
			2 + (2*(4+(i%2))) * this->boardStats.at(2),
			1 + (2*(2 + (i / 2)))* this->boardStats.at(3),
			this->boardStats.at(2),	
			this->boardStats.at(3),
			4,
			(this->board.at(vector<int>{4+ (i% 2),2 + (i/2)})).at(0)
		},this->boardPawnSet.at(this->board.at(vector<int>{4 + (i% 2),2 + (i/2)})));
		
		
		//blue's start...
		this->displayLine(vector<int>{
			2 + (2*(2+(i%2))) * this->boardStats.at(2),
			1 + (2*(10 + (i / 2)))* this->boardStats.at(3),
			this->boardStats.at(2),
			this->boardStats.at(3),
			2,
			(this->board.at(vector<int>{2 + (i% 2),10 + (i/2)})).at(0)
		},this->boardPawnSet.at(this->board.at(vector<int>{2 + (i% 2),10 + (i/2)})));
		//blue's home
		this->displayLine(vector<int>{
			2 + (2*(6+(i%2))) * this->boardStats.at(2),
			1 + (2*(12 + (i / 2)))* this->boardStats.at(3),
			this->boardStats.at(2),
			this->boardStats.at(3),
			2,
			(this->board.at(vector<int>{6 + (i% 2),12 + (i/2)})).at(0)
		},this->boardPawnSet.at(this->board.at(vector<int>{6 + (i% 2),12 + (i/2)})));
		
		//(this->board.at(vector<int>{0,8-i})).at(0)
//		}, this->boardPawnSet.at((this->board.at(vector<int>{0,8-i})))
		
	}

	this->displayLine(vector<int>{
		2 + (2 * (1)) * this->boardStats.at(2),
		1 + (2 * (11))* this->boardStats.at(3),
		this->boardStats.at(2),
		this->boardStats.at(3),
		2,
		2
	}, "<");
	this->displayLine(vector<int>{
		2 + (2 * (4)) * this->boardStats.at(2),
		1 + (2 * (1))* this->boardStats.at(3),
		this->boardStats.at(2),
		this->boardStats.at(3),
		4,
		4
	}, "^");
	this->displayLine(vector<int>{
		2 + (2 * 14) * this->boardStats.at(2),
		1 + (2 * (4))* this->boardStats.at(3),
		this->boardStats.at(2),
		this->boardStats.at(3),
		3,
		3
	}, ">");
	this->displayLine(vector<int>{
		2 + (2 * (11)) * this->boardStats.at(2),
		1 + (2 * (14))* this->boardStats.at(3),
		this->boardStats.at(2),
		this->boardStats.at(3),
		1,
		1
	}, "V");
}

// Retrieves the piece at a given location on the board.
vector<int> SorryBoard::getPieceAt(const vector<int>& pos){
	return this->board.at(pos);
}

// Sets the tile at 'pos' to have the "piece" newVal.
void SorryBoard::setPieceAt(const vector<int>& pos, const vector<int>& newVal){
	auto it = this->board.find(pos);
	if(it != this->board.end()){
		it->second = newVal;
	}else{
		this->board.insert({pos, newVal});
	}
}

// Add a color pair to ncurses to render on the screen. Takes a foreground color, background color, and a pair ID
void SorryBoard::setColorPair(int fg, int bg, int id){
	// Create a new color pair (can hold to 256 of them), by creating a two-way mapping of it to its ID.
	this->cpairMap.insert({vector<int>{fg, bg}, id});
	this->colorMap.insert({id, vector<int>{fg,bg}});
	init_pair(id, fg, bg);
}

// This will register a board "piece", with it's ID, its foreground rendering color, its string to display.
void SorryBoard::setBoardPiece(vector<int> vec, string str, int fg){
	// Set the board pawn, the string to render for the pawn and the color to render with the pawn.
	this->boardPawnSet.insert({vec, str});
	this->boardPawnFGCol.insert({vec, fg});
}

// Swaps the pieces at the locations from and 'to'
void SorryBoard::swapPieces(const vector<int>& from, const vector<int>& to){
	auto temp = this->getPieceAt(from);
	this->setPieceAt(from, this->getPieceAt(to));
	this->setPieceAt(to, temp);
}

// Takes the tile at from, moves it to location 'to', and sets the 'from' to blank (vector<int>{0})
void SorryBoard::movePiece(const vector<int>& from, const vector<int>& to){
	this->setPieceAt(to, this->getPieceAt(from));
	this->setPieceAt(from, vector<int>{0});
}
