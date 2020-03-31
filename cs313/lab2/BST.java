//Author: Lily Jim
//Credits: Starter code provided by Hu
//UO CIS 313 Fall 2018

public class BST<E extends Comparable<E>> {
    private Node<E> root;

    public BST(){
        root = null; // Initialize a new BST with a null root
    }

    public Node<E> getRoot(){
        return root; // Get the root node
    }

    public void insert(E data){ // Run time of O(n)
        if(root == null){
            root = new Node<E>(data); // If the tree is empty, the new node is the root
        }
        else{
            boolean set = false;
            Node<E> temp = new Node<E>(data);
            Node<E> current = root;
            // Find where the new node goes and set it:
            // Worst case this loop runs n times because it will look at each node in the tree, O(n)
            while(!set){
                if(data.compareTo(current.getData()) < 0 ){ // If data < current.getData(), the new node goes to the left
                    if(current.getLeftChild() == null){ // If there is no left child to the current node
                        current.setLeftChild(temp); // Set the new node as the left child
                        temp.setParent(current); // Set the new node's parent
                        set = true;
                    }
                    else{ // If there is a left child to the current node
                        current = current.getLeftChild(); // Make the left child the new current node
                    }
                }
                else{ // If data > current.getData(), the new node goes to the right
                    if(current.getRightChild() == null){ // If there is no right child to the current node
                        current.setRightChild(temp); // Set the new node as the right child
                        temp.setParent(current); // Set the new node's parent
                        set = true;
                    }
                    else{ // If there is a right child to the current node
                        current = current.getRightChild(); // Make the right child the new current node
                    }
                }
            }
        }
    }

    public Node<E> find(E data){ // Run time of O(n)
        if(root == null){
            return null; // If the tree is empty, there is no match, return null
        }
        boolean found = false;
        Node<E> current = root; // Start at the root of the tree
        // Find the node that has the data value we want
        // Worst case this loop runs n times because it will look at each node in the tree, O(n)
        while(!found){
            if(data.compareTo(current.getData()) == 0){ // If the data in the node is what we want
                found = true; // End the loop and return the node
            }else
            if(data.compareTo(current.getData()) < 0){ // If the data in the node is greater than what we want
                if(current.getLeftChild() == null){ // And there is a not a left child
                    return null;    // There is no match, return null
                }
                current = current.getLeftChild(); // Otherwise, set current to the left child and keep looking
            }else 
            if(current.getRightChild() == null){ // If the data in the node is less than what we want and there is not a right child
                return null; // There is not match, return null
            }else{
                current = current.getRightChild(); // Otherwise, set current to the right child and keep looking
            }
        }
        return current;
    }

    public void delete(E data){ // Run time of O(n)
        // Worst case two calls are made to O(n) functions, n + n = 2n => O(n), delete has a run time of O(n)
        Node<E> toDelete = find(data); // Find the node to be deleted, which has a run time of O(n)
        if(toDelete == null){
            return; // If the node we want to delete does not exist, do nothing
        }
        Node<E> leftChild = toDelete.getLeftChild(); // Record the left child of the node being deleted
        Node<E> rightChild = toDelete.getRightChild(); // Record the right child of the node being deleted
        if(toDelete == root){ // If the root is being deleted:
            if((leftChild == null) && (rightChild == null)){
                root = null; // And has no children, set root to null
            }
            else if((leftChild != null) && (rightChild == null)){ // And has only a left child
                leftChild.setParent(null); // The left child has no parent now
                root = leftChild; // And is the new root
            }
            else if((leftChild == null) && (rightChild != null)){ // Has only a right child
                rightChild.setParent(null); // The right child has no parent now
                root = rightChild; // And is the new root
            }
            else if((leftChild != null) && (rightChild != null)){ // Has both a left and right child
                Node<E> min = getMin(rightChild); // Find the min node on the right subtree, which has a run time of O(n)
                if(min == rightChild){ // If the min is the right child
                    min.setParent(null); // The min has no parent now
                    min.setLeftChild(leftChild); // The min now points to the original left child
                    root = min; // And the min is the new root
                }
                else{ // If the min is not the right child
                    min.getParent().setLeftChild(null); // The min's parent does not have a left child anymore
                    if(min.getRightChild() != null){ // But if the min had a right child
                        min.getRightChild().setParent(min.getParent());
                        min.getParent().setLeftChild(min.getRightChild()); // The min's right child becomes its parents new left child
                    }
                    min.setParent(null); // The min has no parent now
                    min.setLeftChild(leftChild); // The min now points to the original left child
                    leftChild.setParent(min); // The original left child now sees min as its parent
                    min.setRightChild(rightChild); // The min now points to the original right child
                    rightChild.setParent(min); // The original right child now sees min as its parent
                    root = min; // And min is the new root
                }
            }
            return; // If the root was deleted, stop here, return
        }
        Node<E> parent = toDelete.getParent(); // Record the parent of the node being deleted
        Node<E> pleft = parent.getLeftChild(); // Record the parent's left child
        if((leftChild == null) && (rightChild == null)){ // If the node has no children
            if(toDelete == pleft){ // And is the parent's left child
                parent.setLeftChild(null); // Set the parent's left child to null
            }
            else{
                parent.setRightChild(null); // Otherwise, it is the right child and set that to null
            }
        }
        else if((leftChild != null) && (rightChild == null)){ // If the node has only a left child
            if(toDelete == pleft){ // And the node is the parent's left child
                parent.setLeftChild(leftChild); // Set the parent's left child to the node's left child
            }
            else{
                parent.setRightChild(leftChild); // Otherwise, it is the right child and set that to the node's left child
            }
            leftChild.setParent(parent); // Set the parent of the node's left child
        }
        else if((leftChild == null) && (rightChild != null)){ // If the node has only a right child
            if(toDelete == pleft){ // And the node is the parent's left child
                parent.setLeftChild(rightChild); // Set the parent's left child to the node's right child
            }
            else{
                parent.setRightChild(rightChild); // Otherwise, it is the right child and set that to the node's right child
            }
            rightChild.setParent(parent); // Set the parent of the node's right child
        }
        else if((leftChild != null) && (rightChild != null)){ // If the node has both a left and right child
            Node<E> min = getMin(rightChild); // Find the min node on the right subtree, which has a run time of O(n)
            if(min == rightChild){ // If the min is the right child
                min.setParent(parent); // The min has a new parent
                min.setLeftChild(leftChild); // And now points to the node's original left child
                if(toDelete == pleft){ // If the node is the parent's left child
                    parent.setLeftChild(min); // Set the parent's left child to the min
                }else{
                    parent.setRightChild(min); // Otherwise, it is the parent's right child and set that to the node's right child
                }
            }
            else{ // If the min is not the node's right child
                min.getParent().setLeftChild(null); // The min's parent does not have a left child anymore
                if(min.getRightChild() != null){ // But if the min had a right child
                    min.getRightChild().setParent(min.getParent());
                    min.getParent().setLeftChild(min.getRightChild()); // The min's right child becomes its parents new left child
                }
                if(toDelete == pleft){ // If the node is the parent's left child
                    parent.setLeftChild(min); // Set the parent's left child to min
                }
                else{
                    parent.setRightChild(min); // Otherwise, it is the parent's right child and set that to the nodes's right child
                }
                min.setParent(parent); // The min's parent is now the deleted node's parent
                min.setLeftChild(leftChild); // The min's left child is now the node's original left child
                leftChild.setParent(min); // The original left child now sees min as its parent
                min.setRightChild(rightChild); // The min's right child is now the node's original right child
                rightChild.setParent(min); // The original right child now sees min as its parent
            }
        }
    }

    public void traverse(String order, Node<E> top) {
        if (top != null){ // If the node is not null, keep going
            switch (order) {
                case "preorder": // Parent, Left, Right
                    System.out.printf("%d ", top.getData()); // Parent first
                    traverse("preorder", top.getLeftChild()); // Left next
                    traverse("preorder", top.getRightChild()); // Right last
                    break;
                case "inorder": // Left, Parent, Right
                    traverse("inorder", top.getLeftChild()); // Left first
                    System.out.printf("%d ", top.getData()); // Parent next
                    traverse("inorder", top.getRightChild()); // Right last
                    break;
                case "postorder": // Left, Right, Parent
                    traverse("postorder", top.getLeftChild()); // Left first
                    traverse("postorder", top.getRightChild()); // Right next
                    System.out.printf("%d ", top.getData()); // Parent Last
                    break;
            }
        }
    }

    public Node<E> getMin(Node<E> top){ // Run time of O(n)
        if(top.getLeftChild() == null){
            return top; // If there is no left child, then top is the min
        }
        boolean found = false;
        Node<E> current = top.getLeftChild();
        // Find the node that is the min (left most node)
        // Worst case this loop runs n times because it will look at each node in the tree, O(n)
        while(!found){
            if(current.getLeftChild() != null){
                current = current.getLeftChild(); // If there is a left child, make it the new current node, keep going
            }
            else{
                found = true; // If there is not another left child, exit loop and return the current node
            }
        }
        return current;
    }

}
