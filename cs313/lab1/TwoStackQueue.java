//Author: Lily Jim
//UO CIS 313 Fall 2018

public class TwoStackQueue<E> {
	private Stack<E> one;
	private Stack<E> two;
	
	public TwoStackQueue(){

		// Initialize two empty stacks
		one = new Stack<E>();
		two = new Stack<E>();	

	}
	
	public void enqueue(E newData){

		// Put newData into stack1
		one.push(newData);

	}

	public Node<E> dequeue(){

		// Reverse stack1 by putting the elements into stack2
		while(!one.isEmpty()){
			Node<E> node = one.pop();
			two.push(node.getData());
		}
		// Remove  and record the top element in the reversed stack (ie take the first element off of the queue)
		Node<E> temp = two.pop();
		// Put stack2 back into stack1 so it is ready for new elements
		while(!two.isEmpty()){
			Node<E> node = two.pop();
			one.push(node.getData());
		}
		// Return the removed element
		return temp;

	}

	public boolean isEmpty(){

		// Elements are stored in stack1, so check the emptiness of stack1
		if(one.isEmpty()){
			return true;
		}
		else{
			return false;
		}

	}

	public void printQueue(){

		// Reverse stack1 by putting the elements into stack2
		while(!one.isEmpty()){
                        Node<E> node = one.pop();
                        two.push(node.getData());
                }
		// Print stack2 (which is the order of a queue)
		two.printStack();
		// Put stack2 back into stack1 so it is ready for new elements
		while(!two.isEmpty()){
                        Node<E> node = two.pop();
                        one.push(node.getData());
                }

	}

}
