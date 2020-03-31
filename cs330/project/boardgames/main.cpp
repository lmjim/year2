#include <iostream>
#include <vector>
#include "input.hpp"
#include "chess.hpp"
#include "checkers.hpp"
#include "sorry.hpp"
#include "aggravation.hpp"

using namespace std;

int main(){
        // Create vector of game choices
        vector<string> choices;
        choices.push_back("Chess");
        choices.push_back("Checkers");
	choices.push_back("Sorry");
	choices.push_back("Aggravation");
        input::Input i;
        // Ask user which game they would like play
        int game = i.gameChoice(choices);
        // Enter curses mode
        cout << "Hit enter to continue";
        string enter;
        getline(cin, enter);
        // Call the game's main
	chess::Chess chessGame;
	checkers::Checkers checkersGame;
	sorry::Sorry sorryGame;
	aggravation::Aggravation aggravationGame;
	switch(game){
		case 1: 
			chessGame.runChess();
			break;
		case 2: 
			checkersGame.runCheckers();
			break;
		case 3:
			sorryGame.runSorry();
			break;
		case 4:
			aggravationGame.runAggravation();
			break;
		default:
			cout << "Something went wrong" << endl;
	}
        // Final message to user
        cout << "Thanks for playing!" << endl;
        return 0;
}
