import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

// Node of the Trie data structure
class TrieNode {
	// ArrayList for 26 alphabets in english
	ArrayList<TrieNode> letters;
	// boolean data type to mark the end of a word
	boolean end;

	// Constructor to initialize the Arraylist with size 26 and value null
	public TrieNode() {
		letters = new ArrayList<TrieNode>(Collections.nCopies(26, null));
		end = false;
	}
}

// class for the Trie data structure
public class Trie {

	// a static node head because the static main method is the driver method
	static TrieNode head;

	// add method to add a word in the data structure
	static void add(String word) {
		int i = 0;
		TrieNode tempHead = head; // temp head for traversal purpose

		// traversing till the alphabets of the the word are already present in
		// the Trie
		while (i < word.length() && tempHead.letters.get(word.charAt(i) - 'a') != null) {
			tempHead = tempHead.letters.get(word.charAt(i) - 'a');
			i++;
		}

		// Two Cases:

		/* Case 1: the word to in input is a initial substring of a bigger word
		 example: "hello" was already in the trie and now we input "hell"
		 in this case just set the 'end' variable true*/
		if (i > word.length()) {
			tempHead.end = true;
			return;
		}
		/* Case 2: either some part of word was already in the trie and already
		 available part is traversed in while loop above
		 so just add the remaining part. example: "-tre-es" and "-tre-spass"
		 OR no part of word was in the trie*/
		else {
			// for the remaining alphabets create and attach new nodes
			while (i < word.length()) {
				TrieNode tempNode = new TrieNode();

				// IMPORTANT LEARNING #####********* take care of the difference between set() and add() in ArrayList **********#########
				tempHead.letters.set(word.charAt(i) - 'a', tempNode);

				i++;
				tempHead = tempNode;
			}
			// and set 'end' variable true at the last node
			tempHead.end = true;
		}
	}

	/* recursive method to count the number of words once the find method
	 traverses upto the prefix string and calls this method
	 traverse through the tree recursively counting word ends(nodes with true
	 value) and returning value to the parent call*/
	static int countWords(TrieNode tempHead) {
		int i = 0;
		int words = 0;

		// count words in non null child trees
		for (i = 0; i < 26; i++) {
			if (tempHead.letters.get(i) != null) {
				words += countWords(tempHead.letters.get(i));
			}
		}

		// add 1 to the number of words if the present head itself has a value
		// true of 'end' variable
		if (tempHead.end == true)
			return words + 1;
		else
			return words;

	}

	/* method to traverse upto the point of prefix string in the Trie
	 after traversing till the prefix string, it calls the countWords method
	 to
	 count the number of words with that prefix*/
	static void find(String word) {
		TrieNode tempHead = head;
		int i = 0;
		// if the first alphabet of prefix string string is not found in the
		// trie -- print zero and return
		if (tempHead.letters.get(word.charAt(i) - 'a') == null) {
			System.out.println("0");
			return;
		} else {
			// traverse till the prefix string
			while (i < word.length() && tempHead.letters.get(word.charAt(i) - 'a') != null) {
				tempHead = tempHead.letters.get(word.charAt(i) - 'a');
				i++;
			}
			// if the complete prefix string is not found, then -- print zero
			// and return
			if (i < word.length()) {
				System.out.println("0");
				return;
			}
			// else if the complete prefix string is found, call the count words
			// method supplying the address of current node
			else {
				System.out.println(countWords(tempHead));
				return;
			}

		}

	}

	// main driver method
	public static void main(String[] args) {
		int n;
		String word;
		head = new TrieNode();
		Scanner sc = new Scanner(System.in);
		n = sc.nextInt(); // to read a integer
		sc.nextLine(); // IMPORTANT LEARNING #####********* to read the newline after the integer **********#########
		while (n > 0) {

			word = sc.nextLine(); // to read a line including space characters
									// till it see a line seperator(newLine)

			/* the two type of queries are
			 add _________ OR find __________
			 following if condition identifies the type of query by checking
			 first character of query
			 and then calls appropriate method and supplies the the substring
			 of query i.e. the actual word in the method*/

			if (word.charAt(0) == 'a') {
				add(word.substring(4));
			} else {
				find(word.substring(5));
			}

			n--;
		}
		sc.close();
	}
}
