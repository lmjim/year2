#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROW 3
#define COL 4

bool arrayEqual(int a[ROW][COL], int b[ROW][COL], int m, int n){
	bool equal = true;
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			if(a[i][j] != b[i][j]){
				equal = false;
				return equal;
			}
		}
	}
	return equal;
}

bool arrayEqual2(int ***a, int ***b, int m, int n){
        bool equal = true;
        for(int i=0; i<m; i++){
                for(int j=0; j<n; j++){
                        if((*a)[i][j] != (*b)[i][j]){
                                equal = false;
                                return equal;
                        }
                }
        }
        return equal;
}

int main(){
	int m = ROW;
	int n = COL;
	int a[m][n];
	int b[m][n];;
	for(int i=0; i<m; i++){
                for(int j=0; j<n; j++){
                        a[i][j] = i;
			b[i][j] = i;
                }
        }
	bool equal = arrayEqual(a, b, m, n);
	printf("The arrays are %s\n", equal ? "equal" : "not equal");

	// Create arrays a2 and b2:
	m = 2;
	n = 3;
	int **a2 = NULL;
	a2 = (int **)malloc(m * sizeof(int*));
	int **b2 = NULL;
        b2 = (int **)malloc(m * sizeof(int*));
	for (int i = 0; i < m; i++){
        	(a2)[i] = (int *) malloc(n * sizeof(int));
		(b2)[i] = (int *) malloc(n * sizeof(int));
	}
	// Add values to arrays a2 and b2:
	for (int i = 0; i < m; i++){
        	for (int j = 0; j < n; j++){
	            (a2)[i][j] = j;
		    (b2)[i][j] = j;
        	}
	}
	// Run comparison
	bool equal2 = arrayEqual2(&a2, &b2, m, n);
	printf("The dynamic arrays are %s\n", equal2 ? "equal" : "not equal");
	// Free arrays
	for(int i = 0; i < 2; i++){
        	free((a2)[i]);
		free((b2)[i]);
	}
	free(a2);
	free(b2);

}

