/* Graham Greving
 * ggreving@ucsc.edu
 * CMPS 101: Introduction to Algorithms
 * Pat Tantalo
 * July 24, 2013
 */
import java.io.*;
import java.util.Scanner;

class Sparse {
	public static void main (String[]args) throws IOException{
		if (args.length < 2) {
			throw new RuntimeException ("Error: args");
		}
		Scanner in = new Scanner(new File(args[0]));
		PrintWriter out = new PrintWriter(args[1]);
		Matrix A;
		Matrix B;
		int n = in.nextInt();
		int a = in.nextInt();
		int b = in.nextInt();
		A = new Matrix (n);
		B = new Matrix (n);
		in.nextLine();
		for (int i = 0; i < a; i++) {
			int row = in.nextInt();
			int col = in.nextInt();
			double val = in.nextDouble();
			A.changeEntry(row,col,val);
		}
		in.nextLine();
		for (int i = 0; i < b; i++) {
			int row = in.nextInt();
			int col = in.nextInt();
			double val = in.nextDouble();
			B.changeEntry(row,col,val);
		}
		out.println("A has "+a+" non-zero entries:");
		out.println(A);
		out.println("B has "+b+" non-zero entries:");
		out.println(B);
		out.println("(1.5)*A =");
		out.println(A.scalarMult(1.5));
		out.println("A+B =");
		out.println(A.add(B));
		out.println("A+A =");
		out.println(A.add(A));
		out.println("B-A =");
		out.println(B.sub(A));
		out.println("A-A =");
		out.println(A.sub(A));
		out.println("Transpose(A) =");
		out.println(A.transpose());
		out.println("A*B = ");
		out.println(A.mult(B));
		out.println("B*B = ");
		out.println(B.mult(B));
		
		in.close();
		out.close();
		return;
	}
}