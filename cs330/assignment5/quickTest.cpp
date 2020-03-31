#include <iostream>

using namespace std;

int main(){
	int key = 2;
	int space = 123;
	int lsize = 27; // Lowercase size is 27 because it includes space
	int usize = 26; // Uppercase size is 26 because that's the number of letters in the alphabet
	string t = "abcdefghijklmnopqrstuvwxyz ";
	for(int i=0; i<27; i++){
		if(t[i] >= 'a' && t[i] <= space - key){
			cout << t[i];
			t[i] = t[i] + key;
			if(t[i] == space){
				t[i] = ' ';
			}
			cout << " -> " << t[i] << endl;
		}
		else if(t[i] > space - key){
			cout << t[i];
			t[i] = t[i] + key - lsize;
			cout << " -> " << t[i] << endl;
		}
		else{
			// char is a space
			cout << t[i];
			t[i] = space + key - lsize;
			cout << " -> " << t[i] << endl;
		}
	}
	return 0;
}
