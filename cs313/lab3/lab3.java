//Author: Lily Jim
//Credits: Starter code provided by Hu
//UO CIS 313 Fall 2018

import java.util.Scanner;

public class lab3 {
    public static void main(String[] args) {

        Scanner input = new Scanner(System.in); // Start Scanner
        int numLines = input.nextInt(); // Get number of lines
        input.nextLine(); // Be ready at next line
        int size = numLines; // Initial Max Size
        pQueue<Integer> pq = new pQueue<Integer>(size); // Initialize Priority Queue
        int number = 0;

        // Split each line into the task and the corresponding number (if one exists)
        for(int i=0; i < numLines; i++){
            String[] s = (input.nextLine()).split(" "); // Read line and split on space (if space exists)
            String task = s[0]; // Task is the first entry
            if(s.length > 1){
                number = Integer.parseInt(s[1]); // Set the number that is also given
            }

                // Depending on what the input task was, preform the corresponding function
                switch(task){
                case "insert":
                    pq.insert(number);
                    break;
                case "maximum":
                    Comparable<Integer> max = pq.maximum();
                    System.out.println(max);
                    break;
                case "extractMax":
                    Comparable<Integer> emax = pq.extractMax();
                    System.out.println(emax);
                    break;
                case "isEmpty":
                    boolean empty = pq.isEmpty();
                    if(empty == false){
                        System.out.println("Not Empty");
                    }
                    else{
                        System.out.println("Empty");
                    }
                    break;
                case "print":
                    pq.print();
                    break;
            }
        }

        // Close scanner
        input.close();
    }
}
