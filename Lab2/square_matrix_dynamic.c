#include <stdio.h>
#include <stdlib.h>
int main() {
	int i,j,n;
	printf("n=");
	scanf("%d",&n);
	int **m = (int **)malloc(n*sizeof(int *));
	for(i=0; i<n; i++)
		m[i] = (int *)malloc(n*sizeof(int));
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			m[i][j] = rand()%10+1;
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			printf("%d", m[i][j]);
			printf(" ");
		}
		printf("\n");
	}
	for(i=0; i<n; i++)
		free(m[i]);
	free(m);
	return 0;
}
