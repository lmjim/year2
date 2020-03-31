#include <iostream>
#include <vector>
#include <sstream>

// Credits: https://www.dynamicguru.com/tips/cpp-check-if-input-is-valid-data-type-using-cin-fail/
// 	https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
// 	http://www.cplusplus.com/reference/string/string/find_first_not_of/
//	http://www.cplusplus.com/reference/string/stoi/
//	https://stackoverflow.com/questions/9235296/how-to-detect-empty-lines-while-reading-from-istream-object-in-c
//	https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
//	http://www.cplusplus.com/reference/sstream/stringstream/stringstream/
//	https://www.geeksforgeeks.org/advantages-of-vector-over-array-in-c/
//	https://www.geeksforgeeks.org/initialize-a-vector-in-cpp-different-ways/

int testForExtraInput(){
	int valid = 0;
        int number = 0;
	std::string input;
        while(!valid){
                printf("Please enter the size of the board (4-16): "); // Ask for input
		std::getline(std::cin,  input); // Get input
                if(std::cin.fail() || input.find_first_not_of("0123456789") != std::string::npos || input.empty()){
                        std::cout << "Invalid entry." << std::endl; // Do not accept input with anything other than a number and handle case when input is just 'enter'
                }
		else{
			number = std::stoi(input); // Convert string to int
			if(number > 16 || number < 4){
	                        std::cout << "Invalid size." << std::endl; // Minimum board size is 4 and maximum is 16
			}
			else{
				valid = 1;
			}
                }
        }
        std::cout << "You entered: " << number << std::endl;
	return number;
}

std::vector<int> testForTurnInput(){
	int valid = 0;
        int x = 0;
        int y = 0;
	std::string input;
        while(!valid){
                std::cout << "Player 1\'s turn, choose row and col for new disc. Input 2 numbers: "; // Ask for input
                std::getline(std::cin, input); // Get input
		if(std::cin.fail() || input.find_first_not_of("0123456789 ") != std::string::npos || input.empty()){
                        std::cout << "Invalid entry." << std::endl; // Do not accept input with anything other than a numbers and handle case when input is just 'enter'
                }
		else{
			std::stringstream inputStream(input);
			std::vector<std::string> tokens;
			std::string tokenRemaining;
			while(getline(inputStream, tokenRemaining, ' ')){
				tokens.push_back(tokenRemaining); // Split string into pieces to convert to numbers
			}
			if(tokens.size() != 2){
				std::cout << "Invalid entry." << std::endl; // Only process input with two numbers separated by a single space
			}
			else{
		                x = std::stoi(tokens[0]); // Convert first number from string to int
		                y = std::stoi(tokens[1]); // Convert second number from string to int
		                if(x > 16 || y > 16 || x < 4 || y < 4){
					// Will be if(!isValidPlacement(board, player, x, y) in reversi
		                        std::cout << "Invalid choice." << std::endl; // Check that choice is valid
		                }
		                else{
		                        valid = 1;
		                }
			}
	        }
	}
	std::vector<int> xy{x, y};
//        std::cout << "You chose " << xy[0] << " " << xy[1] << "." << std::endl <<std::endl;
        return xy;
}

int main(){
	/* This was first attempt, does not check user input fully
	int valid = 0;
        int number = 0;
        while(!valid){
                printf("Please enter the size of the board (4-16): "); // Ask for input
                if(!(std::cin >> number)){
                        std::cout << "Invalid entry." << std::endl; // currently will accept input if first portion is a number
                }
                else if(number > 16 || number <4){
                        std::cout << "Invalid size." << std::endl; // Minimum board size is 4 and maximum is 16
                }
                else{
                        valid = 1;
                }
		std::cin.clear(); // Clears any error flags
		std::cin.ignore(999, '\n'); // Ignore any other input on the line
        }
	std::cout << "You entered: " << number << std::endl;
	std::cout << "Starting other test:" << std::endl;
	*/
	int number = testForExtraInput();
	std::vector<int> xy = testForTurnInput();
	std::cout << "You chose " << xy[0] << " " << xy[1] << "." << std::endl;
	return number;
}
