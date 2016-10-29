#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}Node;

Node *stack1 = NULL, *stack2 = NULL;

    
void enqueue(int x){
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = x;
   
    temp->next = stack1;
    stack1 = temp;
}

void dequeue(){
    Node *temp1 = NULL;
    Node *temp2= NULL;
    if(stack2 == NULL){
        
        while(stack1!=NULL){
            temp2 = stack1;
           stack1 = stack1->next;
            temp2->next = stack2;
            stack2 = temp2;
            
        }
        
    }
    temp1 = stack2;
    if(temp1==NULL)
        return;
    stack2 = stack2->next;
   
    free(temp1);
}

void printnode(){
    Node *temp1 = NULL;
    Node *temp2= NULL;
    if(stack2 == NULL){
        
        while(stack1!=NULL){
            temp2 = stack1;
           stack1 = stack1->next;
            temp2->next = stack2;
            stack2 = temp2;
            
        }
        
    }
   
    printf("%d\n", stack2->data);
}

int main() {

    int q, x, t, stack;
    
    scanf("%d",&q);
    while(q--){
        scanf("%d", &t);
        
        if(t==1){
            scanf("%d", &x);
            enqueue(x);
        }
        else if(t==2){
            dequeue();
        }
        else{
            printnode();
        }
    }
        
    return 0;
}

