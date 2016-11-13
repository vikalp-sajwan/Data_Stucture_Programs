#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// function to rotate a hollow rectangle recursively
// index will be the index of upper left corner of rectangle which will always be in diagonal of matrix

void rotate(int mat[300][300], int index, int rot, int rows, int cols){
    if(rot==0)
        return;
    int temp = mat[index][index];
    int i,j;
    for(j = 0; j<cols-1; j++)
        mat[index][index+j]=mat[index][index+j+1];
    for(i = 0; i<rows-1; i++)
        mat[index+i][index+j]= mat[index+i+1][index+j];
    for(j; j>0; j--)
        mat[index+i][index+j]= mat[index+i][index+j-1];
    for(i; i>1; i--)
        mat[index+i][index+j]= mat[index+i-1][index+j];
    mat[index+i][index+j]=temp;
    
    rotate(mat, index, rot-1, rows, cols);
}

int main() {

    int n,m,r,i,j,rotations;
    int rows, cols, index, num;
    scanf("%d %d %d", &m, &n, &r);
    int mat[300][300];
    for(i=0; i<m; i++){
        for(j=0; j<n; j++)
            scanf("%d", &mat[i][j]);
    }
    
    // logic : start with the inner most rectangle of size 2*x or x*2, which depends on the input
    // rotate it perticular number of times using modulus
    // then go to the outer rectangle rotate and so on....till the index>=0
    
    //if rows are less and hence definitely even
    if(m<=n){
        // finding index of innermost rectangle
        index = (m-1)/2;
       // if m<n then rows in innermost rectangle will always be 2, because of constraints
        // calculate columns
        rows=2, cols=n-index*2;
        
        num = 0;    // for number of elements in a hollow rectangle
         while(index>=0){
             
             // calculate number of elements
             num = (cols*2)+(rows-2)*2;
             // calsulate appropriate number of rotations
             rotations = r%num;
             
             if(rotations>0)
             rotate(mat, index, rotations, rows, cols);
             
             // then for outer hollow rectangle rows and columns will be 2 more than the current
             
             rows = rows+2;
             cols = cols+2;
             // and the upperleft corner of rectangle will be 1 less than current and on the diagonal
             index-=1;
         }
    }
    // else if columns are less and hence definitely even
    else{
        index = (n-1)/2;
        rows=m-index*2, cols=2;
        num = 0;
        while(index>=0){
             num = (rows*2)+(cols-2)*2;
             rotations = r%num;
             
             if(rotations>0)
             rotate(mat, index, rotations, rows, cols);
             
             
             rows = rows+2;
             cols = cols+2;
             index-=1;
        }
        
    }
    
    
  
    for(i=0; i<m; i++){
    	for(j=0; j<n; j++){
    		printf("%d ",mat[i][j]);
    	}
    	printf("\n");
    }
    return 0;
}

