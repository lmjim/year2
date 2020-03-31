#include <iostream>
#include "caesar.hpp"

// Credits: referenced rot13cipher
// 		and https://www.w3schools.com/charsets/ref_html_ascii.asp
		/* ASCII
		Space = 32
		A = 65
		Z = 90
		a = 97
		z = 122
		{ = 123
		*/


using namespace std;

CaesarCipher::CaesarCipher() : Cipher(), key(2) {
	// Nothing else to do
}

CaesarCipher::CaesarCipher(int offset) : Cipher(), key(offset){
	// Nothing else to do
}

string CaesarCipher::encrypt(string &text){
	string t = text;
	string::size_type len = t.length();
	int uKey = this->key % 26;
	int lKey = this->key % 27;
	int space = 123; // Want to treat space as if it is the character after 'z'
	int uSize = 26; // Uppercase size is 26 because that's the number of characters in the alphabet
	int lSize = 27; // Lowercase size is 27 because it includes the space character
	for(int i=0; i < len; i++){
		if(t[i] >= 'a' && t[i] <= space - lKey){
			t[i] = t[i] + lKey; // lowercase letters
			if(t[i] == space){
				t[i] = ' '; // the character after 'z' should be ' ' not '{'
			}
		}
		else if(t[i] > space - lKey && t[i] < space){
			t[i] = t[i] + lKey - lSize; // roll back around to lowercase a
		}
		else if(t[i] == ' '){
			if(lKey != 0){
				t[i] = space + lKey - lSize; // treat space as the character after 'z'
			}
		}
		else if(t[i] >= 'A' && t[i] <= 'Z' - uKey){
			t[i] = t[i] + uKey; // uppercase letters
		}
		else if(t[i] > 'Z' - uKey && t[i] <= 'Z'){
			t[i] = t[i] + uKey - uSize; // roll back around to uppercase A
		}
	}
	return t;
}

string CaesarCipher::decrypt(string &text){
	string t = text;
	string::size_type len = t.length();
	int uKey = this->key % 26;
        int lKey = this->key % 27;
	int space = 123; // space acts like the character after 'z'
	int uSize = 26; // 26 uppercase letters
	int lSize=27; // 27 lowercase letters including space
	for(int i=0; i < len; i++){
		if(t[i] >= 'a' + lKey && t[i] <= space){
			t[i] = t[i] - lKey; // lowercase letters
		}
		else if(t[i] < 'a' + lKey && t[i] >= 'a'){
			t[i] = t[i] - lKey + lSize; // roll back around to space (letter after 'z')
			if(t[i] == space){
				t[i] = ' '; // letter after 'z' is really a space
			}
		}
		else if(t[i] == ' '){
			if(lKey != 0){
				t[i] = space - lKey; // treat space as the character after 'z'
			}
		}
		else if(t[i] >= 'A' + uKey && t[i] <= 'Z'){
			t[i] = t[i] - uKey; // uppercase letters
		}
		else if(t[i] < 'A' + uKey && t[i] >= 'A'){
			t[i] = t[i] - uKey + uSize; // roll back around to uppercase 'Z'
		}
	}
	return t;
}
