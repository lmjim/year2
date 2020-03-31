//Author: Lily Jim
//Credits: Starter code provided by class
//UO CIS330 Winter 2019

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int getUserChoice(int current_sticks) {
	int valid = 0;
        long number;
        while(valid != 1){ // Ask for input until valid number of sticks or exit code is entered
                printf("Player 1: How many sticks do you take (1-3)? ");
                int max = 15;
                char input[max];
                fgets(input, max, stdin); // Read input
                char *end;
                number = strtol(input, &end, 10); // Convert input from string to long
                if(strcmp(end, "\n") != 0){
                        printf("Invalid entry.\n"); // Do not accept input with anything other than a number
                }
		else if(number == 0){ // 0 is the exit code
			exit(1); // Quit entire game
		}
		else if(number == 1 || number == 2 || number == 3){
			if(number > current_sticks){ // 1,2,3 are only valid when they do not exceed total number of sticks
                                printf("Invalid number of sticks.\n");
                        }
                        else{
                                valid = 1; // Valid number was enterd
                        }
		}
		else{
			printf("Invalid number of sticks.\n");
		}
        }
	int sticks = (int) number;
	return sticks; // Return user input
}

int getComputerChoice(int current_sticks) {

    /* get a pseudo-random integer between 1 and 3 (inclusive) */
    int rand_choice = rand() % 3 + 1;

    if (rand_choice > current_sticks) return current_sticks;

    /* Optionally replace with additional logic for the computer's strategy */

    return rand_choice;
}


int main(int argc, char** argv) 
{
    int user, computer, number_sticks;


    srand (time(NULL)); /* for reproducible results, you can call srand(1); */

    printf("Welcome to the game of sticks!\n");
    printf("How many sticks are there on the table initially (10-100)? ");
    int max = 15;
    char input[max];
    fgets(input, max, stdin); // Read input
    char *end;
    long number = strtol(input, &end, 10); // Convert input from string to long
    if(strcmp(end, "\n") != 0){
	    printf("Invalid entry.\n"); // Do not accept input with anything other than a number
	    return 10; // Quit
    }

    number_sticks = (int) number;
    if(number_sticks < 10 || number_sticks > 100){ // Check for valid number
	    printf("Invalid number of sticks.\n"); // Print error
	    return 9; // Quit
    }

    printf("Enter 0 to quit\n"); // Notify user of exit code
    while(number_sticks > 0){
	int user = getUserChoice(number_sticks); // User's turn
	number_sticks -= user; // Update number of sticks
	printf("There are %d sticks on the board.\n", number_sticks);
	if(number_sticks <= 0){ // Game over with user being last to pick up sticks
		printf("Computer wins.\n"); // User loses
	}
	else{
		int comp = getComputerChoice(number_sticks); // Computer's turn
		printf("Computer selects %d.\n", comp); // Notify user of computer's choice
		number_sticks -= comp; // Update number of sticks
	        printf("There are %d sticks on the board.\n", number_sticks);
		if(number_sticks <= 0){ // Gamer over with computer being last to pick up sticks
			printf("You Win!\n"); // Computer loses
		}
	}
    }

    return 0;
}
