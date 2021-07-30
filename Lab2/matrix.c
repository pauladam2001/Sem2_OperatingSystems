#include <stdio.h>
#include <stdlib.h>
int main(){
	int j,i, l,c;
	printf("Lines:");
	scanf("%d",&l);
	printf("Columns:");
	scanf("%d",&c);
	int **m = (int **)malloc(l*sizeof(int *));
	for(i=0; i<l; i++) {
		m[i] = (int *)malloc(c*sizeof(int));
	}
	for(i=0; i<l; i++) {
		for(j=0; j<c; j++) {
			m[i][j] = rand()%3+2;
		}
	}
	for(i=0; i<l; i++) {
		for(j=0; j<c; j++) {
			printf("%d", m[i][j]);
		}
		printf("\n");
	}
	for(i=0; i<l; i++) {
		free(m[i]);
	}
	free(m);
	return 0;	
}
