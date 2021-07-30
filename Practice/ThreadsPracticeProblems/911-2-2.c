#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t bar;

int sum = 0;

void *f(void *a) {
	int i = *(int*)a;

	int A = rand() % 10 + 1;
	
	pthread_mutex_lock(&mtx);
	sum += A;
	pthread_mutex_unlock(&mtx);
	
	pthread_barrier_wait(&bar);
		
	int B = rand() % 15 + 1;
	
	if(sum >= B) {
		sum -= B;
		printf("Thread %d generated A %d and B %d and was able to substract B %d from sum %d\n", i, A, B, B, sum + B); 
	}
	else {
		printf("Thread %d generated A %d and B %d and was NOT able to substract B %d from sum %d\n", i, A, B, B, sum);
	}

	return NULL;
}

int main(int argc, char** argv) {
	srandom(time(NULL));

	if(argc != 2) {
		printf("Introduce exactly one argument!\n");
		exit(1);
	}
	int N = atoi(argv[1]);
	int i;

	if(pthread_barrier_init(&bar, NULL, N) != 0) {
		perror("Cannot init barrier");
		exit(1);
	}

	pthread_t t[N];
	for(i=0;i<N;i++) {
		int *v = (int*)malloc(sizeof(int));
		*v = i;
		if(pthread_create(&t[i], NULL, f, v) != 0) {
			perror("Cannot create thread");
			exit(1);
		}
	}
	for(i=0;i<N;i++)
		pthread_join(t[i], NULL);

	printf("The sum is %d\n", sum);

	pthread_mutex_destroy(&mtx);
	pthread_barrier_destroy(&bar);

	return 0;
}
