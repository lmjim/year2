#include <iostream>
#include <ncurses.h>
#include <ctime>
#include "randMove.hpp"
#include <vector>

using namespace std;

int randMove::RandMove::diceRoll(){
	srand(time(nullptr));
	int num = rand() % 6 + 1; // The range is [1,6]

	/* debugging lines:
	move(3,0);
	clrtoeol();
	printw("rolled %d", num);
	refresh();
	getch();
	move(3,0);
	clrtoeol();
	refresh();
	// end debugging line
	*/

	return num;
}
int randMove::RandMove::cardDraw(int cardsRem, const vector<int>& cards){
	if(cardsRem <= 0){
		return -1; // No valid cards to draw from...reshuffle your own darn deck >:(
	}
	/*
		First picks a number between 0 and cardsRem
	*/
	srand(time(nullptr));
	int cardDrawn = rand() % cardsRem;
	int cardsSeen = 0;
	int pos = 0; // I don't want to use the at keyword...
	for(auto start = cards.begin(); start != cards.end(); start++){
		if(*start + cardsSeen >= cardDrawn){
			// We have drawn this type of card (note, assumes all cards are stacked...but we draw randomly from a stacked deck).
			return pos;
		}
		pos++;
		cardsSeen += *start;
	}
	// Though incorrect, return the card out of bounds.
	return pos;
}


int randMove::RandMove::cardDrawInf(){
	srand(time(nullptr));
	bool valid = false;
	int num = -1;
	while(!valid){
		num = rand() % 13; // The range is [0, 12] excluding 6 and 9
		if(num != 6 && num != 9){
			valid = true;
		}
	}

	/* debugging lines:
        move(3,0);
        clrtoeol();
        printw("drew %d", num);
        refresh();
        getch();
        move(3,0);
        clrtoeol();
        refresh();
        // end debugging lines
	*/

	return num;
}
