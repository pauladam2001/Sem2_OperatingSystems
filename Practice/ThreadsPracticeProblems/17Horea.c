#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int N;
sem_t *sems;
pthread_barrier_t bar;

void *f(void *a) {
	int id = *(int*)a;
	printf("%d is waiting...\n", id);
	pthread_barrier_wait(&bar);
	int i;
	for(i=0;i<N;i++) {
		sem_wait(&sems[i]);
		printf("%d passed through checkpoint %d\n", id, i);
		int time = rand()%100000 + 100000;
		usleep(time);
		sem_post(&sems[i]);
	}
	printf("%d finised\n", id);
	
	free(a);

	return NULL;
}

int main(int argc, char** argv) {
	if(argc != 2) {
		printf("Please provide only 1 argument!\n");
		exit(1);
	}
	
	N = atoi(argv[1]);
	
	int i, newN = 1;

	for(i=0;i<N;i++)
		newN *= 2;	

	pthread_t t[newN];

	pthread_barrier_init(&bar, NULL, newN);

	sems = malloc(sizeof(sem_t) * N);

	int cp = newN/2;
	for(i=0;i<N;i++) {
		if(sem_init(&sems[i], 0, cp) != 0) {
			perror("Cannot init sem");
			exit(1);
		}
		cp /= 2;
	}
	
	for(i=0;i<newN;i++) {
		int *v = (int*)malloc(sizeof(int));
		*v = i;
		if(pthread_create(&t[i], NULL, f, v) != 0) {
			perror("Cannot create thread");
			exit(1);
		}
	}

	for(i=0;i<newN;i++)
		pthread_join(t[i], NULL);

	pthread_barrier_destroy(&bar);

	for(i=0;i<N;i++)
		sem_destroy(&sems[i]);

	free(sems);

	return 0;
}
