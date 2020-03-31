//Author: Lily Jim
//Credits: Starter code provided by Hu
//UO CIS 313 Fall 2018

import java.util.Scanner;

public class EC {
	public static void main(String[] args){
	
		// Create a Scanner that reads system input
		Scanner input = new Scanner(System.in);
		int numLines = input.nextInt();  //retrieve the number of lines
		input.nextLine();

		// Loop over the scanner's input
                for(int i = 0; i < numLines; i++){

			// For each line of the input, send it to isPalindrome()
			String s = input.nextLine();

			// If isPalindrome returns true, print "This is a Palindrome." 
			if(isPalindromeEC(s)){
				System.out.println("This is a Palindrome.");
			}

			// Otherwise print "Not a Palindrome."
			else{
				System.out.println("Not a Palindrome.");
			}
		}

		// Close the Scanner		
		input.close();

	}
	
	public static boolean isPalindromeEC(String s){
	// This method has a run time of O(n)
	
		// Create a stack and a TwoStackQueue of chars that represents the passed in string
		TwoStackQueue<Character> queue = new TwoStackQueue<Character>();
		Stack<Character> stack = new Stack<Character>();
		for(int i=0; i < s.length(); i++){
			char next = s.charAt(i);
			queue.enqueue(next);
			stack.push(next);
		}
		
		// Compare the stack and queue to see if the string is a palindrome
		while(!queue.isEmpty() && !stack.isEmpty()){ 
			if(queue.dequeue().getData() != stack.pop().getData()){ // Dequeue and pop compare the first and last chars in the string to each other and removes them from the queue and stack respectively (so the next comparison will be of the second and second to last char, and so on)
				return false; // At the first comparsison that is not the same, the string  cannot be a palindrome
			}
		}
		return true; // If every comparison gets made without returning false, then the string is a palindrome
	}
	
}
