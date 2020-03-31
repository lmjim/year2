// Author: Lily Jim
// Credits: some starter code provided by class, recurrence provided as well
// UO CIS315 Winter 2019

import java.util.*;
import java.io.*;

public class dynProg{
	public static Set<String> dictionary = new HashSet<String>(); // dictionary words
	public static List<Integer> words = new ArrayList<Integer>(); // places to split phrase into words
	public static int[] wordsIT;

	public static void loadDictionary(String fileName){
		// Provided code
		File inFile = new File(fileName);
		try{
			Scanner scanner = new Scanner(inFile);
			String line;
			while(scanner.hasNext()){
				line = scanner.next();
				dictionary.add(line.trim());
			}
			scanner.close();
		}catch(FileNotFoundException e){
			e.printStackTrace();
		}
		return;
	}

	public static boolean dict(String w){
		return dictionary.contains(w); // T/F w is a valid word in the provided dictionary
	}

	// ITERATIVE SOLUTION
	public static boolean splitIT(String input, int z){
		int len = input.length();
		boolean[] found = new boolean[len + 1]; // array to record if phrase starting at i through n can be split
		found[len] = true; // base case
		wordsIT[len] = len; // base case
		for(int i=(len-1); i >= z; i--){
			for(int j=i; j < len; j++){
				if(!(found[i])){
					found[i] = (dict(input.substring(i,j+1))) && (found[j+1]); // given recurrence
					if(found[i]){
						wordsIT[i] = j; // record split location
					}
				}
			}
		}
		return found[z];
	}

	// MEMOIZED SOLUTION, this was done first
	public static boolean split(String input, int i){
		int len = input.length(); // phrase length
		if(i == len){
			return true; // if i is the character after the end of the phrase
		}
		boolean found = false;
		for(int j=i; j < len; j++){
			if(!found){
				found = (dict(input.substring(i,j+1))) && (split(input, j+1)); // given recurrence
				if(found){
					words.add(j); // record split location
				}
			}
		}
		return found;
	}

	// Split phrase for iterative solution
	public static String printWordsIT(String input, int s){
		String phrase = "";
		int i = s; // start of word
		int j = wordsIT[i]; // end of word
		int limit = wordsIT.length - 1; // where words end
		while(j < limit){
			phrase = phrase + input.substring(i, j+1); // add next word to phrase
			i = j + 1; // set start of next word
			j = wordsIT[i]; // set end of next word
			if(j < limit){
				phrase = phrase + " "; // split words with spaces
			}
		}
		return phrase; // return split phrase
	}

	// Split phrase for memoized solution
	public static String printWords(String input, int s){
		int numWords = words.size(); // number of words in phrase
		int i = s; // start of word
		int j = numWords - 1; // end of word
		String phrase = ""; // phrase with spaces
		for(int z=0; z < numWords; z++){
			phrase = phrase + input.substring(i, (words.get(j) + 1)); // add next word to phrase
			i = words.get(j--) + 1;
			if(z < numWords - 1){
				phrase = phrase + " "; // split words with spaces
			}
		}
		return phrase; // return split phrase
	}

	public static void main(String[] args) {
		loadDictionary("diction10k.txt");
		Scanner scanner = new Scanner(System.in); // start scanner
		int lines = scanner.nextInt(); // retrieve the number of lines
		scanner.nextLine(); // move to next line
		for(int i=0; i < lines; i++){
			String input = scanner.nextLine(); // get phrase
			words.clear(); // clear word list for next phrase
			wordsIT = new int[(input.length() + 1)]; // new array for iterative solution
			System.out.println("phrase number: " + (i+1));
			System.out.println(input);
			System.out.println();
			System.out.println("iterative attempt:"); // test iterative solution
			if(splitIT(input, 0)){ // see if phrase can be split
				System.out.println("YES, can be split");
				System.out.println(printWordsIT(input, 0)); // print split phrase
			}
			else{
				System.out.println("NO, cannot be split");
			}
			System.out.println();
			System.out.println("memoized attempt:"); // test memoized solution
			if(split(input, 0)){ // see if phrase can be split
				System.out.println("YES, can be split");
				System.out.println(printWords(input, 0)); // print split phrase
			}
			else{
				System.out.println("NO, cannot be split");
			}
			System.out.println("\n");
		}
		scanner.close(); // close scanner
		return;
        }
}
