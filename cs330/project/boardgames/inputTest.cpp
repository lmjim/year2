#include <iostream>
#include <ncurses.h>
#include <vector>
#include "input.hpp"

using namespace std;

int main(){
	// Create vector of game choices
	vector<string> choices;
	choices.push_back("Chess");
	choices.push_back("Checkers");
	input::Input i;
	// Ask user which game they would like play
	int game = i.gameChoice(choices);
	// Enter curses mode
	cout << "Hit enter to continue";
	string enter;
	getline(cin, enter);
	initscr(); 
	i.setWin();
	// Test user input for moving piece(s)
	i.moveLocationChoice(game, 1); // Test as player 1
	i.pieceChoice(1, 1); // Test Sorry as player 1
	i.pieceChoice(2, 1); // Test Aggravation as player 1
	// Exit curses mode
	endwin();
	// Final message to user
	cout << "Thanks for playing!" << endl;
	return 0;
}
