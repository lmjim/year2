//Author: Lily Jim
//Credits: Starter code provided by Hu
//UO CIS 313 Fall 2018

public class Node<E> {
	private E data;
	private Node<E> next;
	
	public Node(E c, Node<E> n){
	
		// Set the data and next fields to the corresponding input
		data = c;
		next = n;
		
	}
	
	public void setData(E d){
		
		// Set the "data" data field to the corresponding input
		data = d;

	}
	
	public void setNext(Node<E> n){

		// Set the "next" data field to the corresponding input
		next = n;

	}
	public E getData(){

		// Return the "data" data field
		return data;
		
	}
	
	public Node<E> getNext(){
	
		// return the "next" data field
		return next;
		
	}
	
}
