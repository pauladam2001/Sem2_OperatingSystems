#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int N;

pthread_mutex_t evenmtx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t oddmtx = PTHREAD_MUTEX_INITIALIZER;

void *even(void *a) {
	int *arr = (int*)a;
	int index = 0;
	while(index < N) {
		pthread_mutex_lock(&evenmtx);
		int nr = rand()%100 + 1;
		if(nr % 2 == 1)
			nr++;
		arr[index] = nr;
		index += 2;	
		pthread_mutex_unlock(&oddmtx);
	}

	return NULL;
}

void *odd(void *a) {
	int *arr = (int*)a;
	int index = 1;
 	while(index < N) {
 		pthread_mutex_lock(&oddmtx);
	       	int nr = rand()%100 + 1;
        	if(nr % 2 == 0)
         	       nr++;
		arr[index] = nr;
		index += 2;
		pthread_mutex_unlock(&evenmtx);
	}

	return NULL;
}

int main(int argc, char** argv) {
	printf("Introduce N:\n");
	scanf("%d", &N);

	int *array = (int*)malloc(N * sizeof(int));

	pthread_t evenThread, oddThread;

	pthread_mutex_lock(&evenmtx);
	
	if(pthread_create(&evenThread, NULL, even, array) !=0 ) {
		perror("Cannot create thread");
		exit(1);
	}
	if(pthread_create(&oddThread, NULL, odd, array) !=0 ) {
                perror("Cannot create thread");
                exit(1);
        }

	pthread_join(evenThread, NULL);
	pthread_join(oddThread, NULL);
	
	int i;
	for(i=0;i<N;i++)
		printf("%d\n", array[i]);

	pthread_mutex_destroy(&evenmtx);
	pthread_mutex_destroy(&oddmtx);

	free(array);

	return 0;
}
