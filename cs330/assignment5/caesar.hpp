#ifndef __CAESAR_HPP
#define __CAESAR_HPP

#include "cipher.hpp"

// Credits: Based off of Rot13Cipher

using namespace std;

class CaesarCipher : public Cipher{
	public:
	CaesarCipher(); // Default Constructor
	CaesarCipher(int offset); // Sets key
	~CaesarCipher() {} // Deconstructor
	virtual string encrypt(string &text); // Encrypt the text argument and return the encrypted text
	virtual string decrypt(string &text); // Decrypt the text argument and return the decrypted text
	private:
	int key;
};

#endif /* __CAESAR_HPP */
