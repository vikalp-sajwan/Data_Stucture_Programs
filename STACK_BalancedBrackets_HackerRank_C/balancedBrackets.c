#include <stdio.h>


char stack[500];
int top = -1;

void push(char d){
    stack[++top]=d;    
}

char pop(){
    if(top==-1)
        return 0;
    char temp = stack[top];
    top--;
    return temp;
}

int main(){
    int t;
    int flag;
    scanf("%d",&t);
    for(int a0 = 0; a0 < t; a0++){
        char* s = (char *)malloc(10240 * sizeof(char));
        scanf("%s",s);
        flag=1;
        top = -1;
        for(int i = 0; s[i]!='\0'; i++){
            if(s[i]=='{' || s[i]=='[' || s[i]=='(')
                push(s[i]);
            else{
                char get = pop();
                
                switch(s[i]){
                    case '}':if(get != '{')
                            flag = 0;
                            break;
                    case ']':if(get != '[')
                            flag = 0;
                            break;
                    case ')':if(get != '(')
                            flag = 0;
                            break;
                    default:flag = 0;
                            break;
                }
                
            }
        }
        if(top == -1 && flag)
            printf("YES\n");
        else 
            printf("NO\n");
        
    }
    
    return 0;
}

