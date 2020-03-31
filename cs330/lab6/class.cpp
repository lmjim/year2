#include <iostream>
#include <string>
#include "class.hpp"

using namespace std;

bool Student::setFirstName(){
	cout << "What is the student's first name? ";
        string input;
        getline(cin, input);
        if(cin.fail() || input.empty()){
                cout << "Not a valid name" << endl;
                return false;
        }
	this->firstName = input;
	return true;
}

bool Student::setLastName(){
	cout << "What is the student's last name? ";
        string input;
        getline(cin, input);
        if(cin.fail() || input.empty()){
                cout << "Not a valid name" << endl;
                return false;
        }
	this->lastName = input;
	return true;
}

bool Student::setAge(){
	cout << "What is the student's age? ";
        string input;
        getline(cin, input);
        if(cin.fail() || input.find_first_not_of("0123456789") != std::string::npos || input.empty()){
		cout << "Not a valid age" << endl;
                return false;
        }
	int num = stoi(input);
	if(num < 0){
		cout << "Not a valid age" << endl;
		return false;
	}
	this->age = num;
	return true;
}

bool Student::setGrades(){
	bool set = true;
	string input1;
	cout << "What is the student's first score? ";
	getline(cin, input1);
	if(cin.fail() || input1.find_first_not_of("0123456789") != std::string::npos || input1.empty()){
		cout << "Not a valid grade" << endl;
		set = false;
	}
	else{
		this->grades[0] = stoi(input1);
	}
	string input2;
	cout << "What is the student's second score? ";
	getline(cin, input2);
	if(cin.fail() || input2.find_first_not_of("0123456789") != std::string::npos || input2.empty()){
                cout << "Not a valid grade" << endl;
                set = false;
        }
	else{
		this->grades[1] = stoi(input2);
	}
	string input3;
	cout << "What is the student's third score? ";
	getline(cin, input3);
	if(cin.fail() || input3.find_first_not_of("0123456789") != std::string::npos || input3.empty()){
                cout << "Not a valid grade" << endl;
                set = false;
        }
	else{
		this->grades[2] = stoi(input3);
	}
	return set;
}

void Student::initStudent(){
	if(!Student::setFirstName()){
		cout << "Setting First Name Failed" << endl;
	}
	if(!Student::setLastName()){
		cout << "Setting Last Name Failed" << endl;
	}
	if(!Student::setAge()){
		cout << "Setting Age Failed" << endl;
	}
	if(!Student::setGrades()){
		cout << "Setting Grades Failed" << endl;
	}
	return;
}

string Student::getFirstName(){
	return this->firstName;
}

string Student::getLastName(){
	return this->lastName;
}

int Student::getAge(){
	return this->age;
}

string Student::getGrades(){
	string grades = to_string(this->grades[0]) + " " + to_string(this->grades[1]) + " " + to_string(this->grades[2]);
	return grades;
}

void Student::printStudent(){
	cout << "Student Name: " << Student::getFirstName() << " " << Student::getLastName() << "    Age: " << Student::getAge() << "    Grades: " << Student::getGrades() << endl;
	return;
}

