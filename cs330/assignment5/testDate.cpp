#include <iostream>
#include <fstream>
#include "ioutils.hpp"
#include "cipher.hpp"
#include "date.hpp"

using namespace std;

int main(int argc, const char *argv[]){
	// Define variables
        string input = "";
        string encrypted = "";
        string decrypted = "";

	// Get input
        IOUtils io;
        io.openStream(argc,argv);
        input = io.readFromStream();
        cout << endl;
        cout << "Original text:" << endl << input;

	// Run ecryption function
	DateCipher dc;
	encrypted = dc.encrypt(input);
	cout << "Encrypted text:" << endl << encrypted;
	
	// Run decryption function
	decrypted = dc.decrypt(encrypted);
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
