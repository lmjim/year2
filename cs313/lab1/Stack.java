//Author: Lily Jim
//Credits: Starter code provided by Hu
//UO CIS 313 Fall 2018

// The run time of the following methods (with the exception of printStack) is O(1)
public class Stack<E> {
	private Node<E> top;
	
	public Stack(){
	
		// Initialize an empty stack
		top = null;
		
	}
	
	public void push(E newData){
	
		// Create a node whose data is newData and becomes the new top
		// Have the new top have the old top as "next"
		// This stacks the elements
		top = new Node<E>(newData, top);

	}
	
	public Node<E> pop(){
	
		// Return null if the stack is empty
		if(top == null){
			return null;
		}
		// Record what the Node on the top of the stack is
		Node<E> temp = top;
		// Update the top of the stack to the next node
		top = temp.getNext();
		// Return the removed top of the stack
		return temp;

	}
	
	public boolean isEmpty(){

		//Check if the Stack is empty
		if(top == null){
			return true;
		}
		else{
			return false;
		}
		
	}
	
	public void printStack(){

		// Loop through the stack and print each Node's data on a new line
		Node<E> temp = top; // Start with the top of the stack and go to the bottom
		while(temp != null){
			System.out.println(temp.getData()); // Use getData instead of pop because the node should not be removed
			temp = (temp.getNext()); // Use getNext to set the node being looked at to the next one as pop is not being used
		}
		
	}

}

