// Author: Lily Jim
// Credits: dagAlgorithm.pdf from class website
// UO CIS315 Winter 2019

import java.util.Scanner;

public class assignment2{
	public static void main(String[] args) {

	        Scanner input = new Scanner(System.in); // Start Scanner
	        int n = input.nextInt(); // Get number of nodes
		int m = input.nextInt(); // Get number of edges (aka number of lines)

		int[][] dag = new int[n+1][n+1];
		for(int i=1; i<n+1; i++){
			for(int j=1; j<n+1; j++){
				dag[i][j] = 0; // Initialize adjacency matrix with 0s (aka no edges)
			}
		}

		for(int i=0; i<m; i++){
			// Read each number on the line
			int node1 = input.nextInt();
			int node2 = input.nextInt();
			int weight = input.nextInt();

			dag[node1][node2] = weight; // Add edge (and weight) to adjacency matrix

		}

	        input.close(); // Close Scanner

		int[] lpNum = longestPath(dag, n); // Returns longest path length and number of longest paths in dag

		// Print results
		System.out.printf("longest path: %d\n", lpNum[0]);
		System.out.printf("number of longest paths: %d\n", lpNum[1]);
		return;
	}

	public static int[] longestPath(int[][] dag, int n){
		// Initialize
		int[] lp = new int[n+1]; // Array has indices 0 through n
		for(int i=1; i<n+1; i++){
			lp[i] = 0; // Note: using 0 instead of negative infinity
		}
		int[] paths = new int[n+1]; // Array to track number of longest paths
		for(int i=1; i<n+1; i++){
			paths[i] = 0;
		}
		paths[1] = 1; // The start node has 1 path to it

		// Loop
		for(int i=1; i<n; i++){
			for(int j=i+1; j<n+1; j++){
				if(dag[i][j] != 0){ // if i,j is an edge
					int length = lp[i] + dag[i][j]; // Longest current length from node i to j
					if(lp[j] < length){ // if i to j is longer than j's current longest path length
						lp[j] = length; // Set new longest path length
						paths[j] = paths[i]; // Set new number of longest paths
					}
					else if(lp[j] == length){ // If longest path lengths are the same
						paths[j] += paths[i]; // Combine number of longest paths
					}
					// Otherwise don't do anything
				}
			}
		}

		// Return
		int[] lpNum = new int[2];
		lpNum[0] = lp[n]; // longest path length
		lpNum[1] = paths[n]; // number of longest paths
		return lpNum;
	}

}
