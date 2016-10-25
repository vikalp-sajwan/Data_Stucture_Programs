
/**
 * PROBLEM -
 * Write a program that merges N sorted arrays into one sorted array.
 * 
 * 
 *  LOGIC -
 *  > make a heap of size equal to number of Arrays
 *  > make initial heap from one element from each array
 *  > till all the arrays are not exhausted
 *  	> extract min element i.e. the root, add to final sorted array
 *  	> add an elements from the same array to which the extracted element belonged
 *  	> of that array has been exhausted, find another array 
 *  		which has min element at 0th index, and add it to heap
 *  > when above loop ends, there are no more elements to put in heap,
 *  	so extract remaining elements of heap, and add in the final array
 *  	 
 */


import java.util.ArrayList;
import java.util.Scanner;

/**
 * custom heap node
 * data--> to store the data
 * parentArrIndex --> to store the index of the Array from which this data is taken
 * 			this is required when min element is extracted from the heap,
 * 			because the next element to inserted in the heap should be from the same array to which this element belonged earlier.
 * 						
 * @author Vikalp
 *
 */
class MinHeapNode{
	int data;
	int parentArrIndex;
	
	public MinHeapNode(int data, int parentArrIndex){
		this.data = data;
		this.parentArrIndex = parentArrIndex;
	}
}

/**
 * MinHeap Class --> An instance of this class maintains a MinHeap as an ArrayList of type MinHeapNode
 * 		instance variable --> heap
 * 		Accessible methods -->	add(), extractMin() and isEmpty()
 * 		private methods --> addHeapify(), removeHeapify()
 * @author Vikalp
 *
 */
class MinHeap{
	ArrayList<MinHeapNode> heap = new ArrayList<MinHeapNode>();
	
	/*
	 *  method to add and element in the heap at the last leaf node
	 *  and then calls private method addHeapify() to maintain Heap property
	 */
	void add(int data, int parentArrIndex){
		heap.add(new MinHeapNode(data, parentArrIndex));
		addHeapify();
	}
	
	/*
	 * LEAF TO ROOT HEAPIFY
	 * this method heapifies the tree from the parent of last leaf node towards the root
	 */
	private void addHeapify(){
		// the index of child node
		int child = heap.size()-1;
		// calculating index of parent of last leaf node
		int parent = (child-1)/2;
		
		// if the value at leaf node is less than the parent then swap values 
		// and perform heapify operation iteratively towards the root till no swap occurs or root is reached. 
		while(parent>=0 && heap.get(child).data < heap.get(parent).data){
			
			// swap
			MinHeapNode temp = heap.get(parent);
			heap.set(parent, heap.get(child));
			heap.set(child, temp);
		
			child = parent;
			parent = (parent-1)/2;
		}
	}
	
	/*
	 * this method extracts(removes) the Min node i.e. the root node and heapifies the tree for maintaining heap property 
	 */
	MinHeapNode extractMin(){
		// copy root node
		MinHeapNode min = heap.get(0);
		// copy last node to root
		heap.set(0, heap.get(heap.size()-1));
		// remove last node
		heap.remove(heap.size()-1);
		// heapify at root node
		removeHeapify(0); // 0 is the index of root node 
		return min;
	}
	
	/*
	 * ROOT TO LEAF HEAPIFY
	 * this is the usual RECURSIVE heapify method
	 * this method heapifies the tree from the root to the leaf nodes
	 * 
	 */
	private void removeHeapify(int root){
		// if root is a leaf node --> return
		// heap.size()-1  is the index of last leaf node
		// and (index of last leaf - 1)/2 gives the index of last parent node in tree
		if(root > (heap.size()-1-1)/2)
			return;
		int min = root;
		int l = root*2+1;
		int r = root*2+2;
		
		if(l<heap.size() && heap.get(l).data < heap.get(min).data)
			min = l;
		if(r<heap.size() && heap.get(r).data < heap.get(min).data)
			min = r;
		
		if(min!=root){
			MinHeapNode temp = heap.get(root);
			heap.set(root, heap.get(min));
			heap.set(min, temp);
			
			removeHeapify(min);
		}
	}
	
	/*
	 * method to check if tree is empty or not
	 */
	boolean isEmpty(){
		if(heap.size()==0)
			return true;
		else 
			return false;
	}
	
	
}

/**
 * this is the class that a user uses to give input and get output
 * 		accessible methods --> MergeArrays constructor, mergeAll(), printFinalArray()
 * @author Vikalp
 *
 */
class MergeArrays{
	// instance of MinHeap class
	MinHeap minHeap = new MinHeap();
	// reference variable to store the reference of array of arrays given as input by user
	ArrayList<ArrayList<Integer>> arrOfArr = null;
	// arrayList to store the final sorted array
	ArrayList<Integer> finalArray = new ArrayList<Integer>();
	
	// constructor
	MergeArrays(ArrayList<ArrayList<Integer>> arrOfArr){
		this.arrOfArr = arrOfArr;
	}
	
	
	/*
	 * >this method performs the actual function of Program i.e. merging all the sorted arrays into one sorted array
	 * >it uses a minHeap of size equal to no of sorted arrays
	 * 
	 */
	void mergeAll(){
		
		// to keep track of all the non empty arrays in the arrOfArr
		// when this variable will become zero, it will mean that no more elements to insert in heap
		int nonEmptyArr = arrOfArr.size();
		
		
		// initial heap building by adding one element from each array
		for(int i = 0; i< arrOfArr.size(); i++){
			minHeap.add(arrOfArr.get(i).remove(0), i);
			if(arrOfArr.get(i).isEmpty()){
				nonEmptyArr--;
			}
		}
		
		// till all the sorted arrays are not exhausted
		while(nonEmptyArr > 0){
			// get minimum node from heap
			MinHeapNode minNode = minHeap.extractMin();
			// add the data of minimum node in finalArray
			finalArray.add(minNode.data);
			
			// get the index of the parent array of extracted node
			int parentArr = minNode.parentArrIndex;
			
			// if the parent array of that node has no more elements, find index of array which has the minimum element at 0th index
			// and make it the parentArr
			// and if the parent array is not empty --> do nothing because we have to supply next element to heap from that array only.
			if(arrOfArr.get(parentArr).isEmpty()){
				parentArr = findMinFirstArr();
			}
			
			// add new node to heap with data and index of parent array
			// HERE WE ARE REMOVING THE ELEMENT FROM THE SORTED ARRAY SO THAT EVENTUALLY IT WILL BECOME EMPTY
			minHeap.add(arrOfArr.get(parentArr).remove(0), parentArr);
			
			// if after the operation array became empty, then decrement the nonEmptyArr counter
			if(arrOfArr.get(parentArr).isEmpty()){
				nonEmptyArr--;
			}
			
		}
		
		// after all the arrays are exhausted, just extract remaining elements from minHeap and add to finalArray
		while(!minHeap.isEmpty()){
			MinHeapNode minNode = minHeap.extractMin();
			finalArray.add(minNode.data);
		}

	}
	
	// this method returns the index of sorted array having the minimum element at 0th index
	private int findMinFirstArr(){
		int min=0, arrIndex = -1;	//array index -1 to indicate that no non empty array has been seen so far
		
		for(int i = 0; i<arrOfArr.size(); i++){
			if(arrOfArr.get(i).isEmpty())
				continue;
			if(arrIndex == -1  ||  arrOfArr.get(i).get(0) < min){
				min = arrOfArr.get(i).get(0);
				arrIndex = i;
			}
			
		}
		return arrIndex;
	}
	
	// function to print the final sorted array
	void printFinalArray(){
		System.out.println("final array is : "+finalArray);
	}
	
}

/**
 * the test class to run the program.
 * @author Vikalp
 *
 */
public class MergeArraysTest {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		// take input from user and save it as "ArrayList of 'ArrayList of type Integer'"
		System.out.println("Enter number of arrays:");
		int noOfArr = sc.nextInt();
		
		ArrayList<ArrayList<Integer>> arrOfArr = new ArrayList<ArrayList<Integer>>();
		
		for(int i= 0;i<noOfArr; i++){
			System.out.println("enter the size of array "+(i+1)+":");
			int noOfElements = sc.nextInt();
			System.out.println("enter "+noOfElements+" elements of array in sorted order:");
			ArrayList<Integer> arr = new ArrayList<Integer>();
			
			for(int j = 0; j<noOfElements; j++){
				arr.add(sc.nextInt());
			}
			arrOfArr.add(arr);
		}
		
		// create an instance of MergeArray class supplying arrOfArr to constructor
		MergeArrays mergeArrays = new MergeArrays(arrOfArr);
		// call the mergeAll method to perform the merging operation
		mergeArrays.mergeAll();
		// print the final array
		mergeArrays.printFinalArray();
		
		sc.close();
	}
}
