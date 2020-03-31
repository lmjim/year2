#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include "board.hpp"
using namespace std;

int main(){ 
	//Generation code/prototype code
	int wt = 1;
	WINDOW * win = initscr();
	cerr << can_change_color() << endl;
	noecho();
	curs_set(0);
	if(has_colors() == FALSE){
		delwin(win);
		endwin();
		cout << "No color!!" << endl;
		exit(1);
	}
	start_color();
	//init_pair(1, COLOR_RED, COLOR_RED);
	/*attron(COLOR_PAIR(1));
	wmove(win, 0, 0);
	waddch(win, 'a');
	wrefresh(win);
	attroff(COLOR_PAIR(1));
	sleep(wt);	
	wmove(win,0,0);
	waddch(win, 'b');
	wrefresh(win);
	sleep(wt);*/
	
	board::Board c{vector<int>{3, 3, 7}}; // Chess board with a width of 7 characters, height of 3 characters, gutter width of 7 characters.
	c.setColorPair(COLOR_RED, COLOR_BLACK, 1); // Black tile
	c.setColorPair(COLOR_BLUE,COLOR_WHITE, 2); // White tile
	c.setColorPair(COLOR_RED, COLOR_RED, 3); // Red border
	c.setBoardPiece(vector<int>{0},"", COLOR_BLACK);
	int i = 1;
	//Red is white
	//Blue is black
	c.setBoardPiece(vector<int>{i++}, "K", COLOR_RED); // 1
	c.setBoardPiece(vector<int>{i++}, "K", COLOR_BLUE);//2
	
	c.setBoardPiece(vector<int>{i++}, "Q", COLOR_RED);//3
	c.setBoardPiece(vector<int>{i++}, "Q", COLOR_BLUE);//4
	
	c.setBoardPiece(vector<int>{i++}, "R", COLOR_RED);//5
	c.setBoardPiece(vector<int>{i++}, "R", COLOR_BLUE);//6
	
	c.setBoardPiece(vector<int>{i++}, "B", COLOR_RED);//7
	c.setBoardPiece(vector<int>{i++}, "B", COLOR_BLUE);//8
	
	c.setBoardPiece(vector<int>{i++}, "H", COLOR_RED);//9
	c.setBoardPiece(vector<int>{i++}, "H", COLOR_BLUE);//10
	
	c.setBoardPiece(vector<int>{i++}, "P", COLOR_RED);//11
	c.setBoardPiece(vector<int>{i++}, "P", COLOR_BLUE);//12
	//Sets the non-pawns on the board
	c.setPieceAt(vector<int>{4,7}, vector<int>{1});
	c.setPieceAt(vector<int>{4,0},vector<int>{2});
	c.setPieceAt(vector<int>{3,7}, vector<int>{3});
	c.setPieceAt(vector<int>{3,0}, vector<int>{4});
	c.setPieceAt(vector<int>{0,7}, vector<int>{5});
	c.setPieceAt(vector<int>{0,0}, vector<int>{6});
	c.setPieceAt(vector<int>{7,7}, vector<int>{5});
	c.setPieceAt(vector<int>{7,0}, vector<int>{6});
	c.setPieceAt(vector<int>{2,7}, vector<int>{7});
	c.setPieceAt(vector<int>{2,0}, vector<int>{8});
	c.setPieceAt(vector<int>{5,7}, vector<int>{7});
	c.setPieceAt(vector<int>{5,0}, vector<int>{8});
	c.setPieceAt(vector<int>{1,7}, vector<int>{9});
	c.setPieceAt(vector<int>{1,0}, vector<int>{10});
	c.setPieceAt(vector<int>{6,7}, vector<int>{9});
	c.setPieceAt(vector<int>{6,0}, vector<int>{10});
	// Sets the pawns on the board
	for(int j = 0; j < 8; j++){
		c.setPieceAt(vector<int>{j,6}, vector<int>{11});
		c.setPieceAt(vector<int>{j,1}, vector<int>{12});
	}
	c.displayBoard();
	c.showScreen();
	sleep(3*wt);
	c.clearScreen();//move one pawn to the side
	c.setPieceAt(vector<int>{-1,0},c.getPieceAt(vector<int>{6,0}));
	c.setPieceAt(vector<int>{6,0},vector<int>{0});
	
	c.displayBoard();
	c.showScreen();
	sleep(3*wt);
	delwin(win);
	endwin();
	return 0;
}
