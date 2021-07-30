#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int** a;
int m;
int* sums;

void *sum(void *b) {
	int idx = *(int*)b;
	int j;
	int s = 0;
	for(j=0;j<m;j++) {
		s += a[idx][j];
	}	
	sums[idx] = s;

	free(b);
	return NULL;
}

int main(int argc, char** argv) {
	FILE *f;
	int n, i, j;
	f = fopen("matrix.txt", "r");
	if(f == NULL) {
		printf("Cannot open matrix.txt");
		exit(1);
	}
	
	fscanf(f, "%d", &n);	//rows
	fscanf(f, "%d", &m);	//columns

	sums = (int*)malloc(n*sizeof(int));

	a = (int**)malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
		a[i] = (int*)malloc(m*sizeof(int));

	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			fscanf(f, "%d", &a[i][j]);
	fclose(f);

	for(i=0;i<n;i++) {
		for(j=0;j<m;j++)
			printf("%d ", a[i][j]);
		printf("\n");
	}


	pthread_t t[n];
	for(i=0;i<n;i++) {
		int *v = (int*)malloc(sizeof(int));
		*v = i;
		if(pthread_create(&t[i], NULL, sum, v) != 0) {
			perror("Cannot create thread");
			exit(1);
		}
	}

	for(i=0;i<n;i++)
		pthread_join(t[i], NULL);

	for(i=0;i<n;i++)
		printf("The sum for row %d is %d\n", i, sums[i]);
	
	free(sums);

	for(i=0;i<n;i++)
		free(a[i]);
	free(a);
	
	return 0;
}
