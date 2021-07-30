#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

pthread_barrier_t b;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *s(void *a) {
	int i = *(int*)a;
	printf("Slow thread %d started\n", i);
	sleep(rand() % 6 + 5);

	printf("Slow thread %d waiting\n", i);	
	pthread_barrier_wait(&b);
	pthread_mutex_unlock(&mutex);
	printf("Slow phase 2 of %d done\n", i);
	
	free(a);
	return NULL;
}

void *f(void *a) {
	printf("Fast thread started\n");
        sleep(rand() % 2 + 2);

        printf("Fast phase 1 done\n");

	printf("Fast thread is waiting\n");
	pthread_mutex_lock(&mutex);
	printf("Fast phase 2 done\n");
	pthread_mutex_unlock(&mutex);
	printf("Fast thread is done\n");

	return NULL;
}

int main() {
	pthread_t slow[5], fast;
	int i;

	if(pthread_barrier_init(&b, NULL, 5) != 0) {
		perror("Cannot create barrier");
		exit(1);
	}
	pthread_mutex_lock(&mutex);	

	for(i=0;i<5;i++) {
		int* v = (int*)malloc(sizeof(int));
		*v = i;
		if(pthread_create(&slow[i], NULL, s, v) != 0) {
			perror("Cannot create thread");
			exit(1);
		}
	}
	if(pthread_create(&fast, NULL, f, NULL) != 0) {
                perror("Cannot create thread");
                exit(1);
        }
	
	for(i=0;i<5;i++)
		pthread_join(slow[i], NULL);
	pthread_join(fast, NULL);

	return 0;
}
