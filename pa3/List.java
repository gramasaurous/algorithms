/* Graham Greving
 * ggreving@ucsc.edu
 * CMPS 101: Introduction to Algorithms
 * Pat Tantalo
 * July 20, 2013
 */
//import java.lang.Math;

class List {
//Private Node Class
	private class Node {
		Object data;
		Node previous;
		Node next;
		Node (Object data) {
			this.data = data;
			previous = null;
			next = null;
		}
		public String toString () {
			return (String.valueOf(data));
		}
	}
//Privata List Fields
	private Node front;
	private Node back;
	private Node cursor;
	private int cursorIndex;
	private int length;

//Creates a new empy list 
	List () {
		front 		= null;
		back 		= null;
		cursor 		= null;
		cursorIndex = -1;
		length 		= 0;
	}
//Returns the number of elements in the list
	int length () {
		return length;
	}
//Returns the index of the cursor element in this list,
// or -1 if the cursor is undefined.
	int getIndex () {
		return cursorIndex;
	}
//Returns front element in the list. Pre: length()>0
	Object front () {
		if (length() != 0) {
			return front.data;
		} else {
			throw new RuntimeException("Error: front() " + 
				"called on an empty list.");
		}
	}
//Returns back element in the list. Pre: length()>0
	Object back () {
		if (length() != 0) {
			return back.data;
		} else {
			throw new RuntimeException("Error: back() " +
				"called on an empty list.");
		}
	}
//Returns cursor element. Pre: length()>=0, getIndex()>=
	Object getElement () {
		if (length() == 0) {
			throw new RuntimeException("Error: getElement() " +
				"called on an empty list.");
		} else if (getIndex() == -1) {
			throw new RuntimeException("Error: getElement():  cursor undefined.");
		} else {
			return cursor.data;
		}
	}
//Returns true if the list and L are the same integer sequence
	public boolean equals (Object x) {
		List L = null;
		if (x instanceof List) {
			L = (List)x;
			if (this.length == L.length) {
				Node temp1 = this.front;
				Node temp2 = L.front;
				while (temp1 != null && temp2 != null) {
					if (temp1.data.equals(temp2.data)) {
						temp1 = temp1.next;
						temp2 = temp2.next;
					} else return false;
				} return true;
			} else {
				return false;
			}
		} else return false;
	}

//Manipulative Methods
//Returns the list to an empty state	
	void clear () {
		for (Node N=front; N!=null; N=N.next) {
			Node temp = N;
			temp = null;
		}
		length = 0;
		cursor = null;
		front = null;
		back = null;
		cursorIndex = -1;
	}
//**If 0<=i<=length()-1, moves the cursor to the element
// at index i, otherwise the cursor becomes undefined.
// now optimized for best time traversal!
	void moveTo (int i) {
		if (i == cursorIndex) return;
		if (i >= length() || i < 0) {
			cursor = null;
			cursorIndex = -1;
			return;
		}
		if (i == 0) cursor = front;
		if (i == length()-1) cursor = back;
		else {
			// Direction value, 0 = left, 1 = right
			int direction = 0;
			// Determine three possible distances
			// d1, from back
			int d1 = length()-i;
			// d2, from front
			int d2 = i;
			// d3, from cursor
			int d3 = Math.abs(cursorIndex - i);
			// Find the shortest distance
			int min = d1;
			if (min > d2) min = d2;
			if (min > d3) min = d3;
			//Set up traversal from the back
			if (min == d1) {
				cursor = back;
				cursorIndex = length() -1;
				direction = 0;
			// Set up traversal from the front
			} else if (min == d2) {
				cursor = front;
				cursorIndex = 0;
				direction = 1;
			// Set up traversal from cursor
			} else if (min == d3) {
				if (i > cursorIndex) direction = 1;
			}
			// Traverse the list
			for (int j = 0; j < i; j++) {
				if (direction == 1) moveNext();
				else movePrev();
			}
		}
		cursorIndex = i;
	}
//Moves the cursor to the previous element
	void movePrev () {
		if (cursor == front || cursorIndex == -1) {
			cursorIndex = -1;
			cursor = null;
		} else {
			cursor = cursor.previous;
			cursorIndex--;
		}
	}
//Moves the cursor to the next element
	void moveNext () {
		if (cursor == back || cursorIndex == -1) {
			cursor = null;
			cursorIndex = -1;
		} else {
			cursor = cursor.next;
			cursorIndex++;
		}
	}
//Inserts data to the end of the list
	void append (Object data) {
		Node newNode = new Node (data);
		if (length == 0) {
			newNode.previous = null;
			newNode.next = null;
			front = newNode;
			back = newNode;
		} else {
			newNode.previous = back;
			newNode.next = null;
			back.next = newNode;
			back = newNode;
		}
		length++;
	}
//Inserts data to the front of the list
	void prepend (Object data) {
		Node newNode = new Node (data);
		if (length == 0) {
			newNode.previous = null;
			newNode.next = null;
			front = newNode;
			back = newNode;
		} else {
			newNode.previous = null;
			newNode.next = front;
			front.previous = newNode;
			front = newNode;
		}
		//If defined, increment the cursor
		if (getIndex() != -1)cursorIndex++;
		length++;
	}


//Inserts new element before the cursor
	void insertBefore (Object data) {
		if (length() <= 0) {
			throw new RuntimeException ("Error: insertBefore() " + 
				"called on an Empty List.");
		} else if (getIndex() < 0) {
			throw new RuntimeException ("Error: Cursor Undefined");
		}
		Node newNode = new Node (data);
		if (getIndex() == 0) {
			prepend(data);
		} else {
			// Link the new node
			newNode.next = cursor;
			newNode.previous = cursor.previous;
			// Link the previous node
			cursor.previous.next = newNode;
			// Link the next node
			cursor.previous = newNode;
			// Update the fields
			cursorIndex++;
			length++;
		}
	}
//Inserts new element after the cursor
	void insertAfter (Object data) {
		if (length() <= 0) {
			throw new RuntimeException ("Error: Empty List.");
		} else if (getIndex() < 0) {
			throw new RuntimeException ("Error: Cursor Undefined.");
		}
		Node newNode = new Node (data);
		if (getIndex() == length()-1) {
			append(data);
		} else {
			// Link the new node
			newNode.previous = cursor;
			newNode.next = cursor.next;
			// Link the previous node
			cursor.next.previous = newNode;
			// Link the next node
			cursor.next = newNode;
			// Update the length
			length++;
		}
		
	}

	//**Removes the back element of the list
	void deleteBack () {
		if (length <= 0) {
			throw new RuntimeException ("Error: deleteBack() called on empty list");
		} if (length == 1) {
			back = front = null;
			moveTo(-1);
		} else {
			Node temp = back;
			Node a = back.previous;
			a.next = null;
			back = a;
			if (cursor == temp) moveTo(-1);
		} length--;
	}
	//**removes the front element of the list
	void deleteFront () {
		if (length <= 0) {
			throw new RuntimeException ("Error: deleteFront() called on empty list");
		} if (length == 1) {
			front = back = null;
			moveTo(-1);
		} else {
			Node temp = front;
			Node a = front.next;
			a.previous = null;
			front = a;
			if (cursorIndex != -1) cursorIndex--;
			if (cursor == temp) moveTo(-1);
		} length--;
	}
	//Deletes the cursor element of the list
	void delete () {
		if (length <= 0) {
			throw new RuntimeException("Error: Delete() called on empty list");
		}
		if (getIndex() == -1) {
			throw new RuntimeException ("Error: delete()" +
				"called on list with an undefined cursor.");
		} else if (cursor == back) {
			deleteBack();
		} else if (cursor == front) {
			deleteFront();
		} else {
			Node temp = cursor;
			Node a = cursor.previous;
			Node b = cursor.next;
			a.next = b;
			b.previous = a;
			length--;
			moveTo(-1);
		}
	}
//Public toString method converts the list to a string
	public String toString () {
		String str = "";
    	for(Node N=front; N!=null; N=N.next){
    		str += N.toString() + " ";
      	}
    	return str;
	}

}
