//Author: Lily Jim
//Credits: Starter code provided by Hu
//UO CIS 313 Fall 2018

public class pQueue<E extends Comparable> {
	private MaxHeap myHeap;

	public pQueue (int s) {
		myHeap = new MaxHeap(s); // pQueue initializes as a new MaxHeap
	}

	public void insert(E data){
		myHeap.insert(data);
	}

	public Comparable<E> maximum(){
		return myHeap.maximum();
	}

	public Comparable<E> extractMax(){
		return myHeap.extractMax();
	}

	public boolean isEmpty(){
		int length = myHeap.getLength(); // length is the number of elements in the heap
		// if the length is 0, then the heap (and thus the priority queue) is empty
		if(length == 0){
			return true; // Return true when the priority queue is empty
		}
		else{
			return false;
		}
	}

	public void build(E[] arr){
		// Extra Credit not implemented
	}
    
	public void print(){
		int length = myHeap.getLength(); // Get number of elements
		E[] myArray = (E[]) myHeap.getArray(); // Get array
		System.out.printf("Current Queue: ");
		for(int i=1; i <= length; i++){
			System.out.printf("%d", myArray[i]); // Print element
			if(i == length){
				System.out.println(); // When all elements are printed, print a new line
			}
			else{
				System.out.printf(","); // Separate elements by a comma and no space
			}
		}
	}
}

