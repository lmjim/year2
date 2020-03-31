//Author: Lily Jim
//Credits: Based off of my lab2.java file which Hu provided starter code for
//UO CIS 313 Fall 2018

import java.util.Scanner;

public class TreeCompare {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in); // Start scanner
        int numLines = input.nextInt(); // Get number of lines for first tree
        input.nextLine(); // Be ready at next line
        BST<Integer> tree = new BST<Integer>(); // Initialize first tree
        int number = 0;
        for(int i=0; i < numLines; i++){
            String[] s = (input.nextLine()).split(" "); // Read line and split into task and number
            // Don't need to check what the task is because it will always be insert
            number = Integer.parseInt(s[1]); // Get number to insert
            tree.insert(number); // Insert number into first tree
        }
        
        numLines = input.nextInt(); // Get number of lines for second tree
        input.nextLine(); // Be ready at next line
        BST<Integer> tree2 = new BST<Integer>(); // Initialize second tree
        number = 0;
        for(int j=0; j < numLines; j++){
            String[] s = (input.nextLine()).split(" "); // Read line and split into task and number
            // Don't need to check what task is because it will always be insert
            number = Integer.parseInt(s[1]); // Get number to insert
            tree2.insert(number); // Insert number into second tree
        }
        
        boolean comparison = false;
        // Run loop to compare trees, if same shape, set comparison to true
        
        if(comparison){ //trees are the same
            System.out.println("The trees have the same shape.");
        }
        else{
            System.out.println("The trees do not have the same shape.");
        }
        
        // Close scanner
        input.close();

    }
}
