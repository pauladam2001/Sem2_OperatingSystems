#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t four_lane, two_lane;
pthread_barrier_t b, b3, b8;

#define N 50

void *car(void *a) {
	int id = *(int*)a;
	int lane = id % 2;
	printf("Car %d started on lane %d\n", id, lane);
	pthread_barrier_wait(&b);	
	if(lane == 0) {
		sem_wait(&four_lane);
		printf("Car %d from lane %d passed\n", id, lane);
		//pthread_barrier_wait(&b8);
		sem_post(&two_lane);
	}
	else {
		sem_wait(&two_lane);
		printf("Car %d from lane %d passed\n", id, lane);
		//pthread_barrier_wait(&b3);
		sem_post(&four_lane);
	}

	return NULL;
}

int main() {
	pthread_t p[N];

	sem_init(&four_lane, 0, 8);
	sem_init(&two_lane, 0, 3);

	pthread_barrier_init(&b, NULL, N);
	pthread_barrier_init(&b3, NULL, 3);
	pthread_barrier_init(&b8, NULL, 8);

	int i;
	for(i=0;i<N;i++) {
		int *v = (int*)malloc(sizeof(int));
		*v = i;
		if(pthread_create(&p[i], NULL, car, v) !=0) {
			perror("Error when creating thread");
			exit(1);
		}
	}

	for(i=0;i<N;i++)
		pthread_join(p[i], NULL);

	sem_destroy(&four_lane);
	sem_destroy(&two_lane);
	
	pthread_barrier_destroy(&b);	
	pthread_barrier_destroy(&b3);
	pthread_barrier_destroy(&b8);
	
	return 0;
}
