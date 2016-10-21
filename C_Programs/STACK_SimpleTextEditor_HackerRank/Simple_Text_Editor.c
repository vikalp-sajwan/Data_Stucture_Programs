// Problem -- In this challenge, you must implement a simple text editor.
// Initially, your editor contains an empty string, S .
// You must perform  operations of the following 4 types:

// 1. append(W) - Append string W to the end of S.
// 2. delete(k) - Delete the last k characters of S.
// 3. print(k) - Print the kth character of S.
// 4. undo() - Undo the last (not previously undone) operation of type 1 or 2,
//    reverting S to the state it was in prior to that operation.

// Solution -- this solution makes use of two stack to save information related to last operation.


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// literal values for the query type
#define APPEND 1
#define DELETE 2

// Stack node to store the info about operation
typedef struct node {
	short type; // to store type of the of stack operation - append or delete
	int k;		// length of appended string in 'append' operation
				// no use in case of 'delete' operation
	struct node *next;
	char *subString; // character pointer to store the deleted string in 'delete' operation
					 // no use in case of 'append' operation
} Node;

Node *top = NULL;

void append(char* text, char *w) {
	Node *temp = (Node*) malloc(sizeof(Node));
	temp->type = APPEND;
	temp->k = strlen(w);	// store the length of string to be appended
	temp->next = top;
	temp->subString = NULL;	// no use
	top = temp;
	// Concatenate the new substring to main text
	strcat(text, w);

}

void delete(char* text, int k) {
	Node *temp = (Node*) malloc(sizeof(Node));
	temp->type = DELETE;
	temp->k = 0;	// no use
	temp->next = top;
	// save the deleted substring to node
	temp->subString = (char*) malloc(sizeof(char) * (k + 1));
	strcpy((temp->subString), text + (strlen(text) - k));

	// delete reduce the length of Text.
	text[strlen(text) - k] = '\0';
	top = temp;

}

void printkth(char *text, int k) {
	printf("%c\n", text[k - 1]);
}

void undo(char *text) {
	Node *temp = top;
	// identify the type of operation on top of stack
	// and perform undo operation accordingly
	if (top->type == APPEND) {
		text[strlen(text) - top->k] = '\0';
	} else {
		strcat(text, top->subString);
		free(top->subString);
	}

	top = top->next;
	// free the node
	free(temp);
}

int main() {

	int no_of_queries;
	int opType;
	char *text = (char*) malloc(sizeof(char) * 100000);
	text[0] = '\0';
	char *newText = (char*) malloc(sizeof(char) * 1000);
	int k;

	scanf("%d", &no_of_queries);
	while (no_of_queries--) {
		scanf("%d", &opType);

		if (opType == 1) {
			//append
			scanf(" %[^\n]s", newText);
			append(text, newText);
		}

		else if (opType == 2) {
			//delete last k chars
			scanf("%d", &k);
			delete(text, k);
		}

		else if (opType == 3) {
			//print kth char
			scanf("%d", &k);
			printkth(text, k);
		}

		else {
			//undo last operation
			undo(text);
		}
	}
	return 0;
}

