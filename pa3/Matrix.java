/* Graham Greving
 * ggreving@ucsc.edu
 * CMPS 101: Introduction to Algorithms
 * Pat Tantalo
 * July 24, 2013
 */

class Matrix {
	// Private inner Cell class defines the nature of an individual
	// cell of a matrix
	private class Cell {
		int column;
		double value;

		Cell (int column, double value) {
			this.column = column;
			this.value = value;
		}
		public boolean equals (Object x) {
			boolean returnVal = false;
			Cell c = null;
			if (x instanceof Cell) {
				c = (Cell)x;
				if (c.value == this.value) returnVal = true;
			}
			return returnVal;
		}
		public String toString() {
			return ( "(" + String.valueOf(column) + ", " + String.valueOf(value) + ")" );
		}
	}
	// Private Matrix Fields
	private int n;
	private int NNZ;
	private List[] rows;

	// Constructor
	// Quits if n is 0 or negative
	Matrix (int n) {
		if (n < 1) {
			throw new RuntimeException ("Error: Cannot init negative Matrix.");
		}
		this.n = n;
		rows = new List[n];
		for (int i=0; i < n; i++) {
			rows[i] = new List();
		}
		NNZ = 0;
	}
	// Accessor Functions
	// Returns the size of the Matrix (n x n)
	int getSize() {
		return n;
	}
	// Returns number of non-zero elements in the Matrix
	int getNNZ() {
		return NNZ;
	}
	// Returns true if Object x is a Matrix and is equal to this Matrix
	// ** Needs functionality **
	public boolean equals (Object x) {
		Matrix M = null;
		boolean returnVal = false;
		if (x instanceof Matrix) {
			M = (Matrix)x;
			if (M.getSize() == n && M.getNNZ() == NNZ) {
				for (int i = 0; i < n; i++) {
					if (!rows[i].equals(M.rows[i])) {
						return false;
					}
				}
				returnVal = true;
			}
		}
		return returnVal;
	}
	// Manipulator Methods
	// Sets the Matrix to the zero state (empty)
	void makeZero() {
		for (int i = 0; i < n; i++) {
			rows[i].clear();
		} NNZ = 0;
	}
	// Returns a new Matrix with the same entries as this Matrix
	Matrix copy() {
		Matrix M = new Matrix(n);
		for (int i = 0; i < n; i++) {
			for (rows[i].moveTo(0); rows[i].getIndex() != -1; rows[i].moveNext()) {
				Cell newCell = (Cell)rows[i].getElement();
				//System.out.println("Append");
				M.rows[i].append(newCell);
				M.NNZ++;
				if (M.NNZ == NNZ) return M;
			}
		}
		return M;
	}
	// Changes the ith row, jth column of this Matrix to x
	// Pre: 1<=i<=getSize(), 1<=j<=getSize()
	void changeEntry (int i, int j, double x) {
		// Quit if i or j is out of bounds
		if ((i>n || i<=0) || (j>n || j<=0)) {
			throw new RuntimeException ("Error: changeEntry called with invalid indices.");
		}
		Cell newCell = new Cell (j, x);
		// This algorithm is better because you only check the Matrix once
		// Case 1: (i,j) dne
		int cellIndex = getCell(i,j);
		List rowI = rows[i-1];
		if (cellIndex == -1) {
			// val != 0: insert val into i'th list (column sorted)
			if (x != 0) {
				//append in sorted order
				//System.out.println("Append in sorted order.");
				// Append the data if the row is empty
				if (rowI.length() == 0) {
					rowI.append(newCell);
					NNZ++;
					return;
				}
				for (int k = 0; k < rowI.length(); k++) {
					rowI.moveTo(k);
					Cell temp = (Cell)rowI.getElement();
					// Insert before if column is less than
					if (j < temp.column) {
						//System.out.println("insertBefore");
						rowI.insertBefore(newCell);
						NNZ++;
						break;
					// If reached the end of the list, append
					} else if (k == rowI.length()-1) {
						rowI.append(newCell);
						//System.out.println("Append");
						NNZ++;
						break;
					}
				}
			} 
			// Case 1b: DNE, x == 0, do nothing
			else {
				//System.out.println("Do nothing.");
			}
		} 
		// Case 2: (i,j) exists:
		else {
			// val == 0: delete (i,j)
			if (x == 0) {
				//System.out.println("Delete.");
				rowI.moveTo(cellIndex);
				rowI.delete();
				NNZ--;
			} else {
				// swap values
				//System.out.println("Swap.");
				rowI.moveTo(cellIndex);
				Cell temp = (Cell)rowI.getElement();
				if (temp.value != x) {
					rowI.insertAfter(newCell);
					rowI.delete();
				} else {
					// Do nothing
				}
			}
		}
	}
	// Returns a new Matrix that is the scalar product of this Matrix with x
	Matrix scalarMult (double x) {
		Matrix M = new Matrix(n);
		for (int i = 0; i < n; i++) {
			for (rows[i].moveTo(0); rows[i].getIndex() != -1; rows[i].moveNext()) {
				Cell c = (Cell)rows[i].getElement();
				int col = c.column;
				double v = c.value*x;
				M.changeEntry(i+1,col,v);
				if (M.NNZ == NNZ) return M;
			}
		}
		return M;
	}
	// Returns a new matrix that is the sum of this Matrix with M.
	Matrix add (Matrix M) {
		if (M.getSize() != this.getSize()) {
			throw new RuntimeException ("Error: add() called on Matrices of different size");
		}
		Matrix N = M.copy();
		for (int i = 0; i < n; i++) {
			for (rows[i].moveTo(0); rows[i].getIndex() != -1; rows[i].moveNext()) {
				Cell one = (Cell)rows[i].getElement();
				int currCol = one.column;
				double sum = one.value;
				if (N.getCell(i+1,currCol) != -1) {
					N.rows[i].moveTo(currCol-1);
					Cell temp = (Cell)N.rows[i].getElement();
					sum += temp.value;
				}
				N.changeEntry(i+1,currCol,sum);
			}
		}
		return N;
	}
	// Returns a new matrix that is the difference of this Matrix with M
	// As in: this.sub(M) = this - M
	Matrix sub (Matrix M) {
		if (M.getSize() != this.getSize()) {
			throw new RuntimeException ("Error: sub() called on Matrices of different size");
		}
		Matrix N = this.copy();
		for (int i = 0; i < n; i++) {
			for (rows[i].moveTo(0); rows[i].getIndex() != -1; rows[i].moveNext()) {
				Cell one = (Cell)rows[i].getElement();
				int currCol = one.column;
				double diff = one.value;
				if (M.getCell(i+1,currCol) != -1) {
					N.rows[i].moveTo(currCol-1);
					Cell temp = (Cell)M.rows[i].getElement();
					diff -= temp.value;
				}
				N.changeEntry(i+1,currCol,diff);
			}
		}
		return N;
	}

	// Returns a new matrix which is the transpose of this matrix
	Matrix transpose () {
		Matrix M = new Matrix(n);
		for (int i = 0; i < n; i++) {
			for (rows[i].moveTo(0); rows[i].getIndex() != -1; rows[i].moveNext()) {
				Cell newCell = (Cell)rows[i].getElement();
				int currCol = newCell.column;
				M.changeEntry(currCol, i+1, newCell.value);
			}
		}
		return M;
	}
	// Returns a new matrix which is the product of this matrix and M
	Matrix mult (Matrix M) {
		if (M.getSize() != this.getSize()) {
			throw new RuntimeException ("Error: mult() called on Matrices of different size.");
		}
		M = M.transpose();
		Matrix product = new Matrix(n);
		for (int i = 1; i <= n; i++) {
			if (rows[i-1].length() != n) {
				continue;
			} else {
				for (int j = 1; j <=n; j++) {
					double dot = dot(this.rows[i-1],M.rows[i-1]);
					product.changeEntry(i,j,dot);
				}
			}
		}
		return product;
	}
	// Returns the dot product of two rows of a matrix.
	private static double dot(List P, List Q) {
		double dot = 0;
		for(P.moveTo(0); P.getIndex() != -1; P.moveNext()) {
			Cell Pcell = (Cell)P.getElement();
			for (Q.moveTo(0); Q.getIndex() != -1; Q.moveNext()) {
				Cell Qcell = (Cell)Q.getElement();
				if (Pcell.column == Qcell.column) {
					dot += Pcell.value * Qcell.value;
					break;
				}
			}
		}
		return dot;
	}
	// Private helper class to determine the position in the ith row List
	// of the (i,j) element.
	private int getCell(int i, int j) {
		// Quit if i or j is out of bounds
		if ((i>n || i<=0) || (j>n || j<=0)) {
			throw new RuntimeException ("Error: getCell() called with invalid indices.");
		}
		int exists = -1;
		if (rows[i-1].length() != 0) {
			rows[i-1].moveTo(0);
			Cell compare;
			while (rows[i-1].getIndex() != -1) {
				compare = (Cell)rows[i-1].getElement();
				//System.out.println("getIndex: " + rows[i-1].	getIndex());
				if (compare.column == j) {
					exists = rows[i-1].getIndex();
					break;
				}
				rows[i-1].moveNext();
			}
		}
		return exists;
	}
	// toString() method overrides the Object's method
	public String toString() {
		String s = "";
		for (int i = 0; i < n; i++) {
			if (rows[i].length() == 0) {
				continue;
			}
			s = s + (i+1)+":"+rows[i].toString()+"\n";
		}
		return s;
	}
}