//Author: Lily Jim
//Credits: Starter code provided by Hu
//UO CIS 313 Fall 2018

// The run time of the following methods (with the exception of printQueue) is O(1)
public class Queue<E> {
	private Node<E> head;
	private Node<E> tail;
	
	public Queue(){
		
		// Initialize an empty queue
		head = null;
		tail = null;
		
	}
	
	public void enqueue(E newData){

		// Create a node whose data is newData and add it to the queue
		if(head == null){
			head = new Node<E>(newData, tail); // When the queue is empty, the new node should be placed at the head of the queue
			tail = head; // When the queue only has one element, the head is also the tail
		}
		else{
			Node<E> temp = new Node<E>(newData, null); // Create a temporary node
			tail.setNext(temp); // Set the current tail's 'next' to the new node being added
			tail = temp; // Set the tail to the new node
		}

	}
	
	public Node<E> dequeue(){

		// Return null if the queue is empty
		if(head == null){
			return null;
		}
		// Record the node at the head of the queue
		Node<E> temp = head;
		// Set the new head of the queue to the next in line
		head = temp.getNext();
		// Return the removed head of the queue
		return temp;

	}
	
	public boolean isEmpty(){
	
		// Check if the Queue is empty
		if(head == null){
			return true;
		}
		else{
			return false;
		}

	}
	
	public void printQueue(){

		// Loop through the queue and print each Node's data on a new line
		Node<E> temp = head; // Start with the head of the queue and go to the tail
                while(temp != null){
                        System.out.println(temp.getData()); // Use getData instead of dequeue because the node should not be removed
			temp = temp.getNext(); // Use getNext to set the node being looked at to the next one as dequeue is not being used
                }

	}

}
