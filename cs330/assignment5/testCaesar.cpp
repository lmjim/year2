#include <iostream>
#include <fstream>
#include <string>
#include "ioutils.hpp"
#include "cipher.hpp"
#include "caesar.hpp"

// Credits: Based off of testRot13Cipher

using namespace std;

int getOffset(){
        int valid = 0;
        int number = 0;
        string input;
        while(!valid){
                cout << "Please enter the Caesar shift parameter (positive integer number): "; // Ask for offset
                getline(cin,  input); // Get input
                if(cin.fail() || input.find_first_not_of("0123456789") != string::npos || input.empty()){
                        cout << "Invalid entry." << endl; // Do not accept input with anything other than a number and handle case when input is just 'enter'
                }
                else{
                        number = stoi(input); // Convert string to int
                        if(number < 0){
                                cout << "Invalid number." << endl; // Must be greater than 0
                        }
                        else{
                                valid = 1;
                        }
                }
        }
        return number;
}

int main(int argc, const char *argv[]){
	// Define variables
	int offset = 2;
	string input = "";
	string encrypted = "";
	string decrypted = "";
	
	// Get input
	offset = getOffset();
	IOUtils io;
	io.openStream(argc,argv);
	input = io.readFromStream();
	cout << endl;
	cout << "Original text:" << endl << input;

	// Run encrypt function
	CaesarCipher caesar(offset);
	encrypted = caesar.encrypt(input);
	cout << "Encrypted text:" << endl << encrypted;
	
	// Run decrypt function
	decrypted = caesar.decrypt(encrypted);
	cout << "Decrypted text:" << endl << decrypted;

	// Check if correct
	if(decrypted == input){
		cout << "Decrypted text matches input!" << endl;
	}
	else{
		cout << "Oops! Decrypted text doesn't match input!" << endl;
		return 1; // Non-zero return for failure
	}
	return 0; // Return zero for success
}

