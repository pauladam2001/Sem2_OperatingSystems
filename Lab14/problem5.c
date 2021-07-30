#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

#define N 10
#define M 5

sem_t semaphore;

void *routine(void *a) {
	int id = *(int*)a;
	printf("Thread %d started \n", id);
	sem_wait(&semaphore);
	printf("Thread %d waiting \n", id);
	sleep(5);
	printf("Thread %d done \n", id);
	sem_post(&semaphore);

	return NULL;
}

int main(int argc, char** argv) {
	pthread_t thread[N];
	int i;
	sem_init(&semaphore, 0, M);

	for(i=0;i<N;i++) {
		int *v = (int*)malloc(sizeof(int));
		*v = i;
		if(pthread_create(&thread[i], NULL, routine, v) != 0) {
			perror("Error on creating thread");
			exit(1);
		}
	}
	for(i=0;i<N;i++)
		pthread_join(thread[i], NULL);
	sem_destroy(&semaphore);

	return 0;
}
