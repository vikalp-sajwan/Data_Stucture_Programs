#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    int n;
    long dist[100000], pet[100000];

    scanf("%d", &n);
    for(int i = 0 ;i<n; i++){
        scanf("%ld %ld", &pet[i], &dist[i]);
    }

    int nahimila = 1;
    int startindex=0;
    while(nahimila){
        int count=0;
        long petrol = 0;
        int presentindex = startindex;
        
        while(count!=n){
            petrol+=pet[presentindex];
            petrol-=dist[presentindex];
            
            if(petrol<0)
                break;
            presentindex=(presentindex+1)%n;
            count++;
        }
        
        if(count==n){
            nahimila=0;
            break;
        }
        startindex++;
        
    }
    printf("%d", startindex);
    
    
    
    
    return 0;
}

