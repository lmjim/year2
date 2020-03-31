#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>

using namespace std;

int main(){
	srand(time(nullptr));

	// First word
	int num = rand() % 5187;
	string firstWord;
	ifstream first("./words/adjectives/2syllableadjectives.txt");
	for(int i=0; i < num; i++){
		first >> firstWord;
	}
	first.close();

	// Second word
	num = rand() % 6365;
        string secondWord;
        ifstream second("./words/verbs/3syllableverbs.txt");
        for(int i=0; i < num; i++){
                second >> secondWord;
        }
        second.close();

	// Third word
        num = rand() % 6924;
        string thirdWord;
        ifstream third("./words/adjectives/3syllableadjectives.txt");
        for(int i=0; i < num; i++){
                third >> thirdWord;
        }
        third.close();

        // Second word
        num = rand() % 3986;
        string fourthWord;
        ifstream fourth("./words/verbs/4syllableverbs.txt");
        for(int i=0; i < num; i++){
                fourth >> fourthWord;
        }
        fourth.close();
	
	// Fifth word
        num = rand() % 5187;
        string fifthWord;
        ifstream fifth("./words/adjectives/2syllableadjectives.txt");
        for(int i=0; i < num; i++){
                fifth >> fifthWord;
        }
        fifth.close();

        // Sixth word
        num = rand() % 6365;
        string sixthWord;
        ifstream sixth("./words/verbs/3syllableverbs.txt");
        for(int i=0; i < num; i++){
                sixth >> sixthWord;
        }
        sixth.close();

	// Lines of haiku
	string firstLine = firstWord + " " + secondWord;
	string secondLine = thirdWord + " " + fourthWord;
        string thirdLine = fifthWord + " " + sixthWord;
	cout << firstLine << endl << secondLine << endl << thirdLine << endl;

	return 0;
}
