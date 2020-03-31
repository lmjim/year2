#ifndef __DATE_HPP
#define __DATE_HPP

#include <vector>
#include "cipher.hpp"

// Credits: Based off of Rot13Cipher

using namespace std;

class DateCipher : public Cipher{
	public:
	DateCipher(); // Default Constructor
	DateCipher(string s); // Sets date
	~DateCipher() {} // Deconstructor
	virtual string encrypt(string &text); // Encrypt the text argument and return the encrypted text
        virtual string decrypt(string &text); // Decrypt the text argument and return the decrypted text
	private:
	string date; // Date with slashes
	string sDate; // Date without slashes
	vector<int> vDate; // Vector of individual digits from date
	void setSDate();
	void setVDate();
};

#endif /* __DATE_HPP */
