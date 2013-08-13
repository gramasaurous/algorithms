//Graham Greving
//CMPS 101: Intro to Algorithms
//Patrick  Tantalo
//July 5, 2013
import java.util.Scanner;
import java.io.*;

class Lex {
	public static void main (String [] args) throws IOException{
		if (args.length < 2) {
			throw new RuntimeException ("Error: args");
		}
		Scanner in = new Scanner(new File(args[0]));
		Scanner lineRead = new Scanner(new File(args[0]));
		PrintWriter out = new PrintWriter(args[1]);

		int numLines = 0;
		while(in.hasNextLine()) {
			numLines++;
			in.nextLine();
		}
		String[] lines= new String[numLines];
		for (int i = 0; i < numLines; i++) {
			lines[i] = lineRead.nextLine();
		}
		List lineList = new List();

		//Sort the array
		for (int j=1; j<numLines; j++) {
			String temp = lines[j];
			int i = j-1;
			while (i>=0 && temp.compareTo(lines[i]) < 0) {
				lines[i+1] = lines[i];
				i--;
			}
			lines[i+1] = temp;
		}
		for(int i=0; i<numLines;i++) {
			lineList.append(i);
		}
		//Write the list to the file at args[1]
		for(int i=0; i< numLines; i++) {
			lineList.moveTo(i);
			out.println(lines[lineList.getElement()]);
		}
		in.close();
		lineRead.close();
		out.close();
	}
}