#ifndef __CLASS_HPP
#define __CLASS_HPP

#include <string>

// Credits: https://www.tutorialspoint.com/cplusplus/input_output_operators_overloading.htm

using namespace std;

class Student{
	public:
	Student() {firstName = "UNKOWN"; lastName = "UNKOWN"; age = 0; grades = new int[3]; grades[0] = 0; grades[1] = 0; grades[2] = 0; cout << "Student object default constructor" << endl;} // Default Constructor
	Student(Student& existing){ // Copy
		cout << "Making copy of student" << endl;
		firstName = existing.firstName;
		lastName = existing.lastName;
		age = existing.age;
		grades = new int[3];
		for (int i=0; i<3; i++)
			this->grades[i] = existing.grades[i];
	}
	Student(Student&& existing){ // Move
		cout << "Moving student" << endl;
		firstName = existing.firstName;
		lastName = existing.lastName;
		age = existing.age;
		grades = existing.grades;
	}
	Student(string fn, string ln, int a, int zero, int one, int two) {firstName = fn; lastName = ln; age = a; grades = new int[3]; grades[0] = zero; grades[1] = one; grades[2] = two;} // Custom Constructor
	friend ostream &operator<<(ostream &output, Student &S){
		output << "Student Name: " << S.firstName << " " << S.lastName << "    Age: " << S.age << "    Grades: " << S.grades[0] << " " << S.grades[1] << " " << S.grades[2];
		return output;
	}
	friend istream &operator>>(istream &input, Student &S){
		input >> S.firstName >> S.lastName >> S.age >> S.grades[0] >> S.grades[1] >> S.grades[2];
		return input;
	}
	~Student() {delete [] this->grades; cout << "Student object destructor" << endl;} // Destructor
	void initStudent();
	void printStudent();
	protected:
	bool setFirstName();
	bool setLastName();
	bool setAge();
	bool setGrades();
	string getFirstName();
	string getLastName();
	int getAge();
	string getGrades();
	private:
	string firstName;
	string lastName;
	int age;
	int *grades;
};

#endif /* __CLASS_HPP */
