//Author: Lily Jim
//Credits: Starter code provided by Hu
//UO CIS 313 Fall 2018

import java.util.Comparator;
import java.lang.Math;

public class MaxHeap<E extends Comparable> {
    private E[] myArray;
    private int maxSize;
    private int length;

    public MaxHeap(int s){
	myArray = (E[]) new Comparable[s+1]; // Initialize an empty array with maximum size, since root is at the 1st index the last element would be at s+1
	maxSize = s;	// Set maximum size
	length = 0;	// Initialize length at 0 (array/heap is empty)
    }

    public E[] getArray(){
        return myArray;
    }

    public void setArray(E[] newArray){
    	if (newArray.length > maxSize){
    		return;
    	}
        myArray = newArray;
        length = newArray.length-1;
    }

    public int getMaxSize(){
        return maxSize;
    }

    public void setMaxSize(int ms){
        maxSize = ms;
    }

    public int getLength(){
        return length;
    }

    public void setLength(int l){
        length = l;
    }

    public void insert(E data){
    	length++; // Inserting a new element increases the length by one
        myArray[length] = data; // Initially insert new value at the end
        if(length == 1){
            // Inserted value is root, no fixing needed
            return;
        }
        heapify(length); // Child's value may be greater than its parent, fix order
    }

    public Comparable<E> maximum(){
        // The root of the heap is the maximum value
        // The root is located at the 1st index
        return myArray[1];
    }

    public Comparable<E> extractMax(){
        E max = myArray[1]; // The root of the heap is the maximum value located at the 1st index
        myArray[1] = myArray[length]; // The last element becomes root
        length--; // The number of elements is one less now
        heapify(1); // The root may no longer be the maximum, fix order
        return max;
    }
    
    public void heapify(int i){
    	// Fix the order of the elements in the heap (parent value is greater than children values)
        E parent = null;
        int p = 0;
        E self = myArray[i]; // Current location's value
        E childL = null;
        int l = i*2; // Left child location
        E childR = null;
        int r = (i*2)+1; // Right child location
        
        if(i != 1){ // If element isn't root
            if(i%2 == 0){ // If element is a left child
                p = i/2; // Parent location
                parent = myArray[p]; // Parent value
            }
            else{ // If element is a right child
                p = (i-1)/2; // Parent location
                parent = myArray[p]; // Parent value
            }
        }
        
        if(l <= length){ // If the element has a left child
            childL = myArray[l]; // Left child value
        }
        if(r <= length){ // If the element has a right child
            childR = myArray[r]; // Right child value
        }
        
        if(parent != null && parent.compareTo(self) < 0){ // If the element has a parent that has a smaller value
            swap(i, p); // Swap values
            heapify(p); // Continue up the tree, evaluate if grandparent is smaller than parent, etc.
        }
        else{ // If the element is smaller than its parent
            E max;
            int m;
            if(childL != null && childR != null){ // If the element has two children
                if(childL.compareTo(childR) > 0){ // If the left child's value is greater than the right child's
                    max = childL; // Max value (of the children) is the left child
                    m = l; // Position of max is the left child location
                }
                else{ // If the right child's value is greater than the left child's
                    max = childR; // Max value (of the children) is the right child
                    m = r; // Position of max is the right child location
                }
                if(max.compareTo(self) > 0){ // If the max of the children's value is greater than the current value
                    swap(i, m); // Swap values
                    heapify(m); // Continue down the tree, evalute if grandchild is smaller than child, etc.
                }
            }
            else{ // If the element has one child, it will be a left child (with no grandchildren to check)
                if(childL != null && childL.compareTo(self) > 0){ // If it has a left child and the value is greater than itself
                    swap(i, l); // Swap values
                }
            }
            // If no children, do nothing
        }
    }

    private void swap(int i, int j){
        // Swap two values in the array
        E temp = myArray[i];
        myArray[i] = myArray[j];
        myArray[j] = temp;
    }
    
    public void buildHeap(E[] newArr){
	   // Extra Credit not implemented
    }
}
