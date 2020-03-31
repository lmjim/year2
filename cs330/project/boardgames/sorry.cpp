#include <iostream>
#include <vector>
#include <ncurses.h>
#include <utility>
#include "sorry.hpp"
#include "input.hpp"
#include "randMove.hpp"
// TODO

using namespace std;
using namespace sorry;

void Sorry::checkColor(){
	// Check if user's terminal supports color
	if(!has_colors()){
		printw("No color! Can't continue :(");
		move(1,0);
		printw("Hit enter to exit");
		refresh();
		getch();
		endwin();
		exit(1);
	}
	start_color();
}

void Sorry::startBoard(board::SorryBoard * b){
	// Pieces are defined in the sorryboard class.
	
	for(int i = 0; i < 4; i++){
		b->setPieceAt(vector<int>{10 + (i%2),12+(i/2)}, vector<int>{1, i+1});
		b->setPieceAt(vector<int>{2 + (i% 2),10 + (i/2)}, vector<int>{2, i+1});
		b->setPieceAt(vector<int>{12 + (i% 2),4 + (i/2)}, vector<int>{3, i+1});
		b->setPieceAt(vector<int>{4 + (i%2),2+(i/2)}, vector<int>{4, i+1});
	}
	
	b->displayBoard();
	b->showScreen();
}



bool Sorry::validMove(board::SorryBoard * b, int player, vector<int> from, vector<int> to){
	
	return false;
}

template <typename T>
static void printDebug(const vector<T>& args){
	for(auto a = args.begin(); a != args.end(); a++){
		std::cout << *a << std::endl;
	}
}

int Sorry::validMovesRemaining(board::SorryBoard * b){
	
	return 0;
}

//'main' function to actually run the game of checkers
void Sorry::runSorry(){
	// Start ncurses
	try{
			
		
		initscr();
		// Hide cursor
		curs_set(0);
		// Check if user's terminal supports color
		checkColor();
		// Start Board
		board::SorryBoard b;
		
		startBoard(&b);
		// Start IO
		input::Input i;
		randMove::RandMove r;
		i.setWin(); // Start IO window
		int cc =0;
		WINDOW * w = i.getWin();
		int turn = 1;
		
		// -1 = start, -2= home
		vector<int> redPos{-1,-1,-1,-1};
		vector<int> bluPos{-1,-1,-1,-1};
		vector<int> grePos{-1,-1,-1,-1};
		vector<int> magPos{-1,-1,-1,-1};
		vector<int> boardStarts{49,34,19,4};
		vector<int> boardEnds{47, 32, 17, 2};
		vector<int> zoneStarts{60, 66, 72, 78};
		vector<int>* curPlay = &redPos;
		vector<vector<int>*> allPos{&redPos, &bluPos, &grePos, &magPos};
		int debugNumberOfShuffles = 0;
		/* TODO game play functions needed
		while(true){
			curPlay = allPos.at(turn-1);
			cc = r.cardDraw(sorryDeckOfCardsAmount, *sorryDeck);
			sorryDeckOfCardsAmount--;
			(*sorryDeck)[cc]--;
			// Note:
				Card->number mapping
				0: Sorry!
				1: 1
				2: 2
				3: 3
				4: 4
				5: 5
				6: 7
				7: 8
				8: 10
				9: 11
				10: 12
			wclear(w);
			mvwprintw(w, 0, 0, ("It is player " + std::to_string(turn) + "'s turn! You draw ").c_str());
			switch(cc){
			case 0:
			{
				wprintw(w,"a 'Sorry!' card! You may take any of your pawns in start and sorry another player's pawn!");
				// picks the first available pawn to ove from this players spot...
				/*int playerPawn = -1;
				for(auto s = curPlay->begin(); s!= curPlay->end(); s++){
					playerPawn++;
					if(*s == -1){
						break;
					}
					if(playerPawn == 3){
						playerPawn = -1; // no pawns in start.
					}
				}
				if(playerPawn == -1){
					mvwprintw(w, 1, 0, "You do not have any pawns in your start. You must forfeit your turn.");
					break;
				}
				vector<int> sorryPos;
				// now check to see if others have pawns that can be sorry'd
				for(auto s = allPos.begin(); s != allPos.end(); s++){
					if(*s == curPlay){
						continue; // We can't sorry our own pawns.
					}
					for(auto t = (*s)->begin(); t != (*s)->end(); t++){
						if(*t >= 0 && *t < 60){
							// This pawn is somewhere on the board in which we can sorry them!
							sorryPos.push_back(*t);
						}
					}
				}
				if(sorryPos.size() == 0){
					mvwprintw(w, 1, 0, "There are no enemy pawns on the board. You must forfeit your turn.");
					break;
				}
				break;
			}
			case 1:
			{
				wprintw(w, "a 1. You may move any pawn 1 space or move 1 pawn from your start.");
				vector<std::pair<int, vector<int>* > > allowedPawns; // It is a vector of pawns that can't move 
				for(auto s = curPlay->begin(); s!= curPlay->end(); s++){
					if(*s == -2){
						// if the pawn is in home, do not allow it to be moved...
						continue;
					}
					vector<int> allowedPos;
					allowedPawns.push_back(std::pair<int, vector<int>*> {*s, &allowedPos});
					// just scan the rest to see if it can move successfully...
					auto t = curPlay->begin();
					for(; t!= curPlay->end(); t++){
						if(*s != -1){
							break;
						}
						if(*s == -1 && *t == boardStarts.at(turn-1)){
							break;
						}
					}
					if(t == curPlay->end()){
						allowedPos.push_back(boardStarts.at(turn-1));
					}
					
					t = curPlay->begin();
					for(; t!= curPlay->end(); t++){
						if(*s == -1 || *s != boardEnds.at(turn-1)){
							break;
						}
						if(*s== boardEnds.at(turn-1) && *t == zoneStarts.at(turn-1)){
							break;
						}
					}
					if(t == curPlay->end()){
						allowedPos.push_back(zoneStarts.at(turn-1));
					}
					t = curPlay->begin();
					for(; t!= curPlay->end(); t++){
						if(*s == -1 || *s == boardEnds.at(turn-1) || *s >= 60){
							break;
						}
						if((*s + 1) % 60 == *t){
							break;
						}
					}
					if(t == curPlay->end()){
						allowedPos.push_back(*s+1);
					}
					t = curPlay->begin();
					for(; t!= curPlay->end(); t++){
						if(*s == -1 || *s == boardEnds.at(turn-1) || *s < 60){
							break;
						}
						if((*s + 1) == *t){
							break;
						}
					}
					if(t == curPlay->end()){
						allowedPos.push_back(*s+1);
					}
				}
				if(allowedPawns.size() == 0){
					mvwprintw(w, 1, 0, "You can not move any of your pawns. You must forfeit your turn.");
					break;
				}
				// Now pick one of the pawns (on input)
				break;
			}
			case 2:
			{
				wprintw(w, "a 2. You may move any pawn 2 spaces or move 1 pawn from your start. (Also, you draw again!)");
				vector<int> allowedPawns;
				for(auto s = curPlay->begin(); s!= curPlay->end(); s++){
					if(*s == -2){
						// if the pawn is in home, do not allow it to be moved...
						continue;
					}
					
					// just scan the rest to see if it can move successfully...
					vector<int> allowedPos;
					allowedPawns.push_back(std::pair<int, vector<int>*> {*s, &allowedPos});
					// just scan the rest to see if it can move successfully...
					auto t = curPlay->begin();
					for(; t!= curPlay->end(); t++){
						if(*s != -1){
							break;
						}
						if(*s == -1 && *t == boardStarts.at(turn-1)){
							break;
						}
					}
					if(t == curPlay->end()){
						allowedPos.push_back(boardStarts.at(turn-1));
					}
					
					t = curPlay->begin();
					for(; t!= curPlay->end(); t++){
						if(*s == -1 || *s != boardEnds.at(turn-1)){
							break;
						}
						if(*s== boardEnds.at(turn-1) && *t == zoneStarts.at(turn-1)+1){
							break;
						}
					}
					if(t == curPlay->end()){
						allowedPos.push_back(zoneStarts.at(turn-1)+1);
					}
					// Don't need to check 2 behind, as it is impossible to do (:D You will slide)
					t = curPlay->begin();
					for(; t!= curPlay->end(); t++){
						if(*s == -1 || *s == boardEnds.at(turn-1) || *s >= 60){
							break;
						}
						if((*s + 1) % 60 == *t){
							break;
						}
					}
					if(t == curPlay->end()){
						allowedPos.push_back(*s+1);
					}
					t = curPlay->begin();
					for(; t!= curPlay->end(); t++){
						if(*s == -1 || *s == boardEnds.at(turn-1) || *s < 60 || (*s + 2 - 60)%6 == 1){
							break;
						}
						if((*s + 2) == *t){
							break;
						}
					}
					if(t == curPlay->end()){
						allowedPos.push_back(*s+2);
					}
				}
				break;
			}
			case 3:
			{
				wprintw(w, "a 3. You may move a pawn 3 steps forward.");
				vector<int> allowedPawns;
				for(auto s = curPlay->begin(); s!= curPlay->end(); s++){
					if(*s == -2){
						// if the pawn is in home, do not allow it to be moved...
						continue;
					}
					
					// just scan the rest to see if it can move successfully...
					vector<int> allowedPos;
					allowedPawns.push_back(std::pair<int, vector<int>*> {*s, &allowedPos});
					// just scan the rest to see if it can move successfully...
					auto t = curPlay->begin();
					for(; t!= curPlay->end(); t++){
						if(*s == -1 || *s >= 60){ // when the pawn is at safety zone or start
							break;
						}
						if((*s + 1) % 60 == *t){
							break;
						}
					}
					if(t == curPlay->end()){
						allowedPos.push_back(*s+1);
					}
					if(((*s + 3 > boardEnds.at(turn -1) && *s <= boardEnds.at(turn-1))) ||(*s + 3 > boardEnds.at(turn-1) + 60 && *s <= boardEnds.at(turn-1) + 60)){
						int deltaRem = 3 - (1 + ((60 + boardEnds.at(turn-1) - *s) % 60));
						//....
						t = curPlay->begin();
						for(; t!= curPlay->end(); t++){
							
						}
					}
				}
				break;
			}
			case 4:
				wprintw(w, "a 4! You may move a pawn 4 steps backwards (no you may not enter your safety zone like this).");
				break;
			case 5:
				wprintw(w,"a 5. You may move a pawn 5 steps forward.");
				break;
			case 6:
				wprintw(w, "a 7! You may move any pawn forward 7, or you may divide up your move between two pawns.");
				break;
			case 7:
				wprintw(w, "a 8. You may move any pawn forward 8 spaces.");
				break;
			case 8:
				wprintw(w, "a 10. You may move any pawn either forward 10 spaces, or you must move 1 pawn back 1 space.");
				break;
			case 9:
				wprintw(w, "a 11. You may move any pawn forward 11 spaces, or you can choose to swap with an enemy pawn.");
				break;
			case 10:
				wprintw(w,"a 12. You may move any pawn forward 12 spaces.");
			default:
				//wat
				break;
			}
			
			//mvwprintw(w, 0, 0, (std::to_string(cc) +" "+ std::to_string(sorryDeckOfCardsAmount)).c_str());
			wrefresh(w);
			
			
			wgetch(w);
			wgetch(w);
			wgetch(w);
			if(sorryDeckOfCardsAmount == 0){
				// Reshuffle the deck..
				sorryDeckOfCardsAmount = 45;
				(*sorryDeck)[0] = 4;
				(*sorryDeck)[1] = 5;
				(*sorryDeck)[2] = 4;
				(*sorryDeck)[3] = 4;
				(*sorryDeck)[4] = 4;
				(*sorryDeck)[5] = 4;
				(*sorryDeck)[6] = 4;
				(*sorryDeck)[7] = 4;
				(*sorryDeck)[8] = 4;
				(*sorryDeck)[9] = 4;
				(*sorryDeck)[10] = 4;
				debugNumberOfShuffles++;
			}
			auto s = curPlay->begin();
			for(; s != curPlay->end(); s++){
				if(*s != -2){
					break;
				}
			}
			if(debugNumberOfShuffles >= 3){
				wclear(w);
				mvwprintw(w,0,0,("Player " + std::to_string(turn) + " wins!").c_str());
				wgetch(w);
				wgetch(w);
				wgetch(w);
				break;
			}
			if(s == curPlay->end()){
				// We have a winner!!!
				wclear(w);
				mvwprintw(w,0,0,("Player " + std::to_string(turn) + " wins!").c_str());
				wgetch(w);
				wgetch(w);
				wgetch(w);
				break;
			}
			
			turn= (turn % 4)+1;
			
		}
		*/
		// TODO the following is debugging
                wclear(w);
                mvwprintw(w, 0, 0, "Sorry you can't play Sorry yet");
                mvwprintw(w, 1, 0, "But check out the board!");
                mvwprintw(w, 2, 0, "Hit enter to exit");
                wrefresh(w);
                wgetch(w);
                // TODO end debugging
		endwin();
	}catch(vector<int> i){
		endwin();
		printDebug<int>(i);
	}catch(...){
		endwin();
		std::cout << "The screen size is too small. Please resize the screen and try again." << std::endl;
		return;
	}
}

