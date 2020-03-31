#include <iostream>
#include "class.hpp"

int main(){
        Student s1;
        s1.initStudent();
        s1.printStudent();
	Student s2(s1);
	s2.printStudent();
	Student s3 = move(s2);
	s3.printStudent();
	Student s4("Lily", "Jim", 20, 100, 100, 100);
	s4.printStudent();
	Student s5;
	cout << "Enter First, Last, Age, Grades" << endl;
	cin >> s5;
	cout << s5 << endl;
        return 0;
}
