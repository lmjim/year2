//Author: Lily Jim
//Credits: Starter code provided by Hu
//UO CIS 313 Fall 2018

import java.util.Scanner;

public class lab2 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in); // Start scanner
        int numLines = input.nextInt(); // Get number of lines to read
        input.nextLine(); // Be ready at next line
        BST<Integer> tree = new BST<Integer>(); // Initialize tree
        int number = 0;
        for(int i=0; i < numLines; i++){
            String[] s = (input.nextLine()).split(" "); // Read line and split on space (if space exists)
            String task = s[0]; // Task is the first entry
            if(s.length > 1){ // If there is more than just a task
                number = Integer.parseInt(s[1]); // Set the number that is also given
            }
            // Depending on what the input task was, preform the corresponding function
            switch(task){
                case "insert":
                    tree.insert(number);
                    break;
                case "delete":
                    tree.delete(number);
                    break;
                case "find":
                    tree.find(number);
                    break;
                case "inorder":
                    tree.traverse(task, tree.getRoot());
                    System.out.println();
                    break;
                case "preorder":
                    tree.traverse(task, tree.getRoot());
                    System.out.println();
                    break;
                case "postorder":
                    tree.traverse(task, tree.getRoot());
                    System.out.println();
                    break;
            }
        }
        
        // Close scanner
        input.close();

    }
}
