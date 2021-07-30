#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int N;
int idx = 0;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *even(void *a) {
	int *arr = (int*)a;
	pthread_mutex_lock(&mtx);
	if(idx % 2 != 0)
		pthread_cond_wait(&cond, &mtx);
	while(idx < N) {
		int nr = rand()%100 + 1;
		if(nr % 2 == 1)
			nr++;
		arr[idx] = nr;
		idx += 1;	
		pthread_cond_signal(&cond);
		if(idx % 2 != 0)
			pthread_cond_wait(&cond, &mtx);
	}
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mtx);

	return NULL;
}

void *odd(void *a) {
	int *arr = (int*)a;
	pthread_mutex_lock(&mtx); 
	if(idx % 2 != 1)
		pthread_cond_wait(&cond, &mtx);
	while(idx < N) {
	       	int nr = rand()%100 + 1;
        	if(nr % 2 == 0)
         	       nr++;
		arr[idx] = nr;
		idx += 1;
		pthread_cond_signal(&cond);
		if(idx % 2 != 1)
			pthread_cond_wait(&cond, &mtx);
	}
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mtx);

	return NULL;
}

int main(int argc, char** argv) {
	printf("Introduce N:\n");
	scanf("%d", &N);

	int *array = (int*)malloc(N * sizeof(int));

	pthread_t evenThread, oddThread;
	
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

	pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&cond);

	free(array);

	return 0;
}
