// Program for implementing 6 way BTree
// This implementation is a TOP-DOWN approach

#include<stdio.h>
#include<stdlib.h>
// INT_MIN is used in this program to identify empty keys in a NODE
#include<limits.h>

// for 6 way top down   2-3-4-5 tree
#define MAX_KEYS 5
#define MIN_KEYS 2
#define CHILDREN 6

// Node structure
typedef struct node{
	int data[MAX_KEYS];
	struct node *ptr[CHILDREN];
}Node;

// function to initialize all the pointers in a node with NULL
// and all the data in a Node with INT_MIN
void initializeNode( Node * nodePtr){
	int i;
	for(i=0; i<CHILDREN; i++){
		nodePtr->ptr[i] = NULL;
	}
	for(i=0; i< MAX_KEYS; i++){
		nodePtr->data[i] = INT_MIN;
	}
}


// function to print in order traversal of the tree
void printInOrder(Node *root){
	
	if(root == NULL){
		return;
	}
	
	int i=0;
	
	// case of a leaf node if first ptr is NULL and first data is NOT empty(INT_MIN)
	// then just print all the keys in the node
	if(root->ptr[0]==NULL && root->data[0]!= INT_MIN){
		while(root->data[i] != INT_MIN && i < MAX_KEYS){
			printf("%d ", root->data[i]);
			i++;
		}
	}
	
	// for other cases call recursion on first pointer and then in pairs of (data and pointer) 
	// till data equals INT_MIN or all the data and pointers are processed.
	// when processing in pairs the pointer index will be 1 more than data index
	else{
		printInOrder( root->ptr[i] );
		while( i < MAX_KEYS && root->data[i]!= INT_MIN ){
			printf("%d ", root->data[i]);
			printInOrder( root->ptr[i+1] );
			i++;
		}
	}
}


// function to Search a key in the BTree
// returns 1 if found else returns 0
int searchKey(Node *root, int item){
	
	if(root == NULL){
		return 0;
	}
	
	int i=0;
	
	// case of a leaf node if first ptr is NULL and first data is NOT empty(INT_MIN)
	// then just search with all the keys in the node
	if(root->ptr[0]==NULL){
		while((root->data[i] != INT_MIN) && (i < MAX_KEYS)){
			if(root->data[i] == item){
				return 1;
			}
			i++;
		}
	}
	
	// for other cases search key int the node or call recursion on appropriate pointer
	else{
		while( (i < MAX_KEYS && root->data[i]!=INT_MIN) && (item > root->data[i]) ){
			i++;
		}
		if(root->data[i] == item){
			return 1;
		}
		else{
			return searchKey(root->ptr[i], item);
		}
	}
	
	return 0;
}

// function to delete tree completely and set root to NULL
void deleteTree(Node** ptrToRoot ){
	// check for ERRONEOUS parameter -- when address to root of tree itself is null
	// or if the root is NULL, return
	if(ptrToRoot==NULL || *ptrToRoot == NULL){
		return;
	}
	
	Node *root = *ptrToRoot;
	int i=0;

	// for all cases call recursion on all the non NULL pointers of the node
	// and then free the node pointed by root and update *ptrToRoot to NULL
	while(root->ptr[i] != NULL && i < CHILDREN){
		deleteTree(&(root->ptr[i]));
		i++;
	}
	free(root);
	*ptrToRoot = NULL;
	
}

// this fuction splits the ith child of the root and add the middle key of the child to the root at appropriate position
void splitNode( Node *root ,int i){
	Node *leftNode = root->ptr[i];
	Node *tempNode = (Node*)malloc(sizeof(Node));
	initializeNode(tempNode);
	
	// shifting all the pointer fields one position right till the appropriate index i
	// **** loop till j is greater than i
	int j = CHILDREN-2;
	while(j>i){
		root->ptr[j+1] = root->ptr[j];
		j--;
	}
	
	// shifting all data fields one position right till the appropriate index i
	// loop till j is greter than or equal to i
	j = MAX_KEYS -2;
	while(j>=i){
		root->data[j+1] = root->data[j];
		j--;
	}
	
	root->data[i] = leftNode->data[2];
	root->ptr[i+1] = tempNode;
	
	// preparing new node on right
	// copy 4th and 5th element of current root to new node on right
	tempNode->data[0] = leftNode->data[3];
	tempNode->data[1] = leftNode->data[4];
	// copy 4th 5th and 6th pointer of current root to new node on right
	tempNode->ptr[0] = leftNode->ptr[3];
	tempNode->ptr[1] = leftNode->ptr[4];
	tempNode->ptr[2] = leftNode->ptr[5];
	
	// now free the half data and pointer fields in the current root
	leftNode->data[2] = leftNode->data[3] = leftNode->data[4] = INT_MIN;
	leftNode->ptr[3] = leftNode->ptr[4] = leftNode->ptr[5] = NULL;
	
}

				
// function to insert a key into tree by top down insertion method
Node* insertTopDown(Node *root, int num){
	// The address of root will change in two cases --
	// 		CASE 1 > when the tree is empty and first node is to be created
	//		CASE 2 > when the actual root node of tree is full and it needs to be split in two nodes 
	//				 and also one new root node is created and root is updated
	
	// for all other cases either no split is required or splitting creates only one node without the need to create new root node 
	// for these cases recursive call will be made in subtree whose root pointer is accepted in currRoot parameter of function
	 
	
	
	// case 1: inserting in an empty tree
	if(root == NULL){
		Node *tempNode = (Node*)malloc(sizeof(Node));
		initializeNode(tempNode);
		tempNode->data[0] = num;
		return tempNode;
	}	
	
	// case 2: the root node is full -- split the node into two nodes having equal no. of keys
	//		   if the last data node is not empty -- means node is already full with max number of keys 
	else if(root->data[MAX_KEYS-1] != INT_MIN ){
		Node *tempNode = (Node*)malloc(sizeof(Node));
		initializeNode(tempNode);
		
		Node *tempRoot = (Node*)malloc(sizeof(Node));
		initializeNode(tempRoot);
		
		// preparing new root node
		tempRoot->ptr[0] = root;	// add pointer to old root in tempRoot
		tempRoot->ptr[1] = tempNode;	// add pointer to new split node on right to tempRoot
		tempRoot->data[0] = root->data[2];	// copy middle element of current root to new tempRoot
		
		// preparing new node on right
		// copy 4th and 5th element of current root to new node on right
		tempNode->data[0] = root->data[3];
		tempNode->data[1] = root->data[4];
		// copy 4th 5th and 6th pointer of current root to new node on right
		tempNode->ptr[0] = root->ptr[3];
		tempNode->ptr[1] = root->ptr[4];
		tempNode->ptr[2] = root->ptr[5];
		
		// now free the half data and pointer fields in the current root
		root->data[2] = root->data[3] = root->data[4] = INT_MIN;
		root->ptr[3] = root->ptr[4] = root->ptr[5] = NULL;
		
		// now make a recursive call to insert data in the left or right subtree based on the value at newRoot i.e. tempRoot
		
		if(num < tempRoot->data[0]){
			tempRoot->ptr[0] = insertTopDown( tempRoot->ptr[0], num);
		}
		else{
			tempRoot->ptr[1] = insertTopDown( tempRoot->ptr[1], num);
		}
		
		return tempRoot;
	}
	// case 3: current root node has space, so either its a leaf node or some intermediate node
	//		>>> two subcases ----- 1> its a leaf node, just enter the data in node
    //					     ------2> its an intermediate node, find the appropriate path to enter node and call insert function recursively
	else{
		if(root->ptr[0] == NULL){   	// LEAF NODE
			// find appropriate index of new data
			int i;
			for (i = 0; i<MAX_KEYS; i++){
				if(root->data[i] > num || root->data[i]==INT_MIN){
					break;
				}
			}
			// shift all the data nodes 1 place to right from ith index
			int j = 3; // second last index;
			while(j>=i){
				root->data[j+1] = root->data[j];
				j--;
			}
			
			// put the num in the ith place
			root->data[i] = num;
			return root;
		}
		else{	// 	NON LEAF NODE
			// find approprite path and call recursively
			
			int i = 0;
			for(i=0; i<5; i++){
				if(num < root->data[i] || root->data[i] == INT_MIN)
					break;
			}
			// check if the node selected is full or not
			if(root->ptr[i]->data[MAX_KEYS -1] == INT_MIN){
				// the node is not full, call insert recursively
				root->ptr[i] = insertTopDown(root->ptr[i] ,num);
			}
			else{
				// split the children node and then re-calculate right path and call insert function recursively
				splitNode(root, i);
				for(i=0; i<5; i++){
					if(num < root->data[i] || root->data[i] == INT_MIN)
						break;
					
				}
				// this time we definitely know that that the path selected will be one of the two split nodes
				// so no need to check if child node is full or not and call the insert fuction recursively
				root->ptr[i] = insertTopDown(root->ptr[i] ,num);
				
			}
			
			return root;
		}
	}
		
}

void borrowFromLeft(Node *root, int i){
	// this function does the right rotation
	
	Node *minimalNode = root->ptr[i];
	Node *rightNeighbour = root->ptr[i-1];
	// first shift all the keys and pointers of the minimal node one place right to make space at first index
	// as this is a minimal node the index of the last filled node is MIN_KEYS-1
	int j = MIN_KEYS-1;
	while(j>=0){
		minimalNode->data[j+1] = minimalNode->data[j];
		minimalNode->ptr[j+2] = minimalNode->ptr[j+1];
		j--;
	}
	minimalNode->ptr[1] = minimalNode->ptr[0];
	
	// copy data from root to minimal node
	minimalNode->data[0] = root->data[i-1];
	
	// find the index of last key in neighbourNode
	int k=0;
	while(k+1!= MAX_KEYS && rightNeighbour->data[k+1]!= INT_MIN){
		k++;
	}
	
	//copy the last data of neighbourNode to root and last child to minimalNode
	root->data[i-1] = rightNeighbour->data[k];
	minimalNode->ptr[0] = rightNeighbour->ptr[k+1];
	
	// then make them INT_MIN and NULL 
	rightNeighbour->data[k] = INT_MIN;
	rightNeighbour->ptr[k+1] = NULL;
	
	return;
}

void borrowFromRight(Node *root, int i){
	// this function does the left rotation
	
	Node *minimalNode = root->ptr[i];
	Node *rightNeighbour = root->ptr[i+1];
	// first copy the data from root to minimal node 
	// and one children from neighbour
	minimalNode->data[MIN_KEYS] = root->data[i];
	minimalNode->ptr[MIN_KEYS +1] = rightNeighbour->ptr[0];
	
	// now copy data from rightNeighbour to root
	root->data[i] = rightNeighbour->data[0];
	
	// now shift the keys and pointers of the rightNeighbour one place left
	int j=1;
	while(j<MAX_KEYS && rightNeighbour->data[j]!=INT_MIN){
		rightNeighbour->data[j-1] = rightNeighbour->data[j];
		j++;
	}
	rightNeighbour->data[j-1] = INT_MIN;
	
	j=1;
	while(j<CHILDREN && rightNeighbour->ptr[j]!=NULL){
		rightNeighbour->ptr[j-1] = rightNeighbour->ptr[j];
		j++;
	}
	rightNeighbour->ptr[j-1] = NULL;
	
	return;
	
}

void merge(Node *root, int i){
	Node *leftNode = root->ptr[i];
	Node *rightNode = root->ptr[i+1];
	
	// copy data from root to left node
	leftNode->data[MIN_KEYS] = root->data[i];
	
	// copy data from the rightNode to leftNode
	leftNode->data[MIN_KEYS+1] = rightNode->data[0];
	leftNode->data[MIN_KEYS+2] = rightNode->data[1];
	
	//copy pointers from the rightNode to leftNode
	leftNode->ptr[MIN_KEYS+1] = rightNode->ptr[0];
	leftNode->ptr[MIN_KEYS+2] = rightNode->ptr[1];
	leftNode->ptr[MIN_KEYS+3] = rightNode->ptr[2];
	
	// shift the data and pointer in the root one place left
	while(i<MAX_KEYS-1 && root->data[i+1]!=INT_MIN){
		root->data[i]=root->data[i+1];
		root->ptr[i+1] = root->ptr[i+2];
		i++;
		
	}
	root->data[i] = INT_MIN; 
	root->ptr[i]= root->ptr[i+1];
	root->ptr[i+1] = NULL;
	
	// free the rightNode
	free(rightNode);
}

int getSuccessor(Node *root){
	// In this case successor will always be in the leaf Node
	// so find and return the first successor found in the first leaf node encountered
	// similar to IN ORDER TRAVERSAL
	if(root->ptr[0]==NULL)
		return root->data[0];
	else
		return getSuccessor(root->ptr[0]);
}

Node* deleteNode( Node *root, int item){
	// there is a special case: the root supplied to this function can be minimal only when the main supplies minimal root
	// because other then that we are never descending into a minimal node
	// but both the sub cases : root being a minimal leaf node and root being a minimal non leaf node 
	// are handled in the normal logic applied in CASE 2 and CASE 3 respectively
	
	// if item is not found in the tree return
	if(!searchKey(root, item)){
		return root;
	}
	
	int i=0, j;
	
	// CASE 2: leaf node - if first ptr is NULL and first data is NOT empty(INT_MIN)
	// then just search with all the keys in the node and delete the key by shifting all the keys to its right by 1 place left
	if(root->ptr[0]==NULL){
		while((root->data[i] != INT_MIN) && (i < MAX_KEYS)){
			if(root->data[i] == item){
				break;
			}
			i++;
		}
		// now shift the keys after ith place to 1 place left
		j=i+1;
		while(j < MAX_KEYS && root->data[j] != INT_MIN){
			root->data[j-1] = root->data[j];
			j++;
		}
		root->data[j-1] = INT_MIN;
		
		// SPECIAL CASE -- WHEN THIS LEAF NODE IS ROOT OF TREE AND IT HAS ONLY ONE ELEMENT
		// SO AFTER DELETION THE ROOT NODE BECOMES EMPTY 
		// HENCE, DELETE THE ROOT NODE AND RETURN NULL
		
		if(root->data[0] == INT_MIN){
			free(root);
			return NULL;
		}
		else{
			return root;
		}
	}
	
	// CASE 3: if it is non leaf node search the appropriate path to descend in the node.
	else{
		while( (i < MAX_KEYS && root->data[i]!=INT_MIN) && (item > root->data[i]) ){
			i++;
		}
		
		if(item == root->data[i]){
			// if the item is found in current node
			// find and overwrite its value with its successor and then call deleteNode recursively to delete the successor
			
			int successor = getSuccessor(root->ptr[i+1]);
			root->ptr[i+1] = deleteNode(root->ptr[i+1], successor);
			return root;
		}
		// check if the path selected is a minimal node or not
		else if(root->ptr[i] -> data[MIN_KEYS] == INT_MIN){
			// the node is minimal so check if any neighbour (right or left if exists) of that node can borrow a key
			if(i-1 >=0 && root->ptr[i-1] -> data[MIN_KEYS] != INT_MIN){
				// left nieghbour is not minimal -->>  call borrow key method and then call deleteNode recursively 
				borrowFromLeft(root, i);
				root->ptr[i] = deleteNode(root->ptr[i], item);
				return root;
			}else if(i+1 <= MAX_KEYS-1 && root->ptr[i+1] -> data[MIN_KEYS] != INT_MIN){
				// right nieghbour is not minimal -->>  call borrow key method and then call deleteNode recursively
				borrowFromRight(root, i);
				root->ptr[i] = deleteNode(root->ptr[i], item);
				return root;
			}
			else{
				// if the neighbours are also minimal nodes then, combine any of them with current node
				if(i-1 >= 0){
					// merge with left neighbour
					merge(root, i-1);
					root->ptr[i-1] = deleteNode(root->ptr[i-1], item);
				}
				else{
					// merge with right neighbour
					merge(root,i);
					root->ptr[i] = deleteNode(root->ptr[i], item);
				}
				return root;
			}
		}
		else{
			// if the node is not minimal -->> call the delete function recursively
			root->ptr[i] = deleteNode(root->ptr[i], item);
			return root;
		}
	}
	
}


int main(){
	
	Node *root = NULL;

	int choice, num;
	printf("\n B-Tree Menu:");
	printf("\n1. insert value");
	printf("\n2. delete value");
	printf("\n3. print IN ORDER traversal of tree");
	printf("\n4. search value in the tree");
	printf("\n5. delete whole tree");
	printf("\n6. exit");
	printf("\n ENTER CHOICE:");
    scanf("%d", &choice);
    
    while(choice!=6){
    	switch(choice){
    		case 1: printf("\n enter the number to insert:");
    				scanf("%d", &num);
    				root = insertTopDown(root, num);
    				printf("In order traversal of tree: ");
					printInOrder(root);
    				break;
    		case 2: printf("\n enter the number to delete:");
    				scanf("%d", &num);
    				root = deleteNode(root, num);
    				printf("In order traversal of tree: ");
					printInOrder(root);
    				break;
    		case 3: printf("In order traversal of tree: ");
					printInOrder(root);
    				break;
    		case 4: printf("\n enter the number to search:");
    				scanf("%d", &num);
    				if(searchKey(root, num)){
						printf("\nItem FOUND in tree");
					}
					else{
						printf("\nItem NOT found in tree");
					}
					break;
			case 5: deleteTree(&root);
					if (root == NULL)
						printf("\nTREE DELETED");
					else 
						printf("\nERROR in deleting tree");
    				break;
    		default: printf("\nWrong choice");
    				 break;
    	}
    	
    	printf("\n ENTER CHOICE:");
    	scanf("%d", &choice);
    }

	return 0;
}
