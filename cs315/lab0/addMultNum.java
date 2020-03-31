//Author: Lily Jim
//Credits: Based off of my lab0 from CIS313
//UO CIS315 Winter 2019

import java.util.Scanner;

public class addMultNum{
	public static void main(String[] args){
		Scanner scanner = new Scanner(System.in); // start scanner
		int lines = scanner.nextInt(); // retrieve the number of lines
		for(int i=0; i < lines; i++){
			int a = scanner.nextInt(); // get first int
			int b = scanner.nextInt(); // get second int
			int added = add(a, b); // do the addition
			int multiplied = mult(a, b); // do the multiplication
			System.out.println(added + " " + multiplied); // print results
		}
		scanner.close(); // close scanner
		return;
	}

	public static int add(int a, int b){
		return a+b; // add
	}

	public static int mult(int a, int b){
		return a*b; // multiply
	}

}
