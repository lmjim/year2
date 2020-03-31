#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int main(){
	string sDate = "02/14/59";
	stringstream dateStream(sDate);
        vector<string> tokens;
        string tokenRemaining;
        while(getline(dateStream, tokenRemaining, '/')){
                tokens.push_back(tokenRemaining);
        }
	string sd = "";
	for(int i=0; i<3; i++){
		sd += tokens[i];
	}
	int date = stoi(sd);
	cout << date << endl;
	return 0;
}
