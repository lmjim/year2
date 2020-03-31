#include <iostream>
#include <sstream>
#include <vector>
#include "date.hpp"

using namespace std;

void DateCipher::setVDate(){
        for(int i=0; i < 6; i++){
                this->vDate.push_back(this->sDate[i] - '0');
        }
        return;
}

void DateCipher::setSDate(){
        stringstream dateStream(this->date);
        vector<string> tokens;
        string tokenRemaining;
        while(getline(dateStream, tokenRemaining, '/')){
                tokens.push_back(tokenRemaining);
        }
        string sd = "";
        for(int i=0; i < 3; i++){
                sd += tokens[i];
        }
        this->sDate = sd;
        return;
}

DateCipher::DateCipher() : Cipher(), date("02/14/59"){
        // Default date is Oregon's birthday
        setSDate();
        setVDate();
}

DateCipher::DateCipher(string s) : Cipher(), date(s){
        setSDate();
        setVDate();
}

string DateCipher::encrypt(string &text){
	// Define some variables
	int size = 26; // Number of letters in alphabet
	string t = text;
	string::size_type len = t.length();
	vector<int> d = this->vDate; // Vector of shifts based on the given date
	int j = 0;
	int shift = d[j]; // First shift

	// Encrypt:
	for(int i=0; i < len; i++){
		if(t[i] >= 'a' && t[i] <= 'z' - shift){
			t[i] = t[i] + shift; // lowercase letters
		}
		else if(t[i] > 'z' - shift && t[i] <= 'z'){
			t[i] = t[i] + shift - size; // roll back around to lowercase a
		}
		else if(t[i] >= 'A' && t[i] <= 'Z' - shift){
			t[i] = t[i] + shift; // uppercase letters
		}
		else if(t[i] > 'Z' - shift && t[i] <= 'Z'){
			t[i] = t[i] + shift - size; // roll back around to uppercase A
		}

		// Switch to next shift
		j++;
		if(j >= 6){
			j = 0; // Reset to beginning once you hit the end
		}
		shift = d[j]; // Go to next digit of date for the next shift
	}
	return t;
}

string DateCipher::decrypt(string &text){
	// Define some variables
	string t = text;
	int size = 26; // number of letters in alphabet
	string::size_type len = t.length();
        vector<int> d = this->vDate; // Vector of shifts based on the given date
        int j = 0;
        int shift = d[j]; // First shift
	
	// Decrypt:
	for(int i=0; i< len; i++){
		if(t[i] >= 'a' + shift && t[i] <= 'z'){
                        t[i] = t[i] - shift; // lowercase letters
                }
                else if(t[i] < 'a' + shift && t[i] >= 'a'){
                        t[i] = t[i] - shift + size; // roll back around to lowercase a
                }
                else if(t[i] >= 'A' + shift && t[i] <= 'Z'){
                        t[i] = t[i] - shift; // uppercase letters
                }
                else if(t[i] < 'A' + shift && t[i] >= 'A'){
                        t[i] = t[i] - shift + size; // roll back around to uppercase A
                }

		// Switch to next shift
		j++;
                if(j >= 6){
                        j = 0; // Reset to beginning once you hit the end
                }
                shift = d[j]; // Go to next digit of date for the next shift
	}
	return t;
}
