#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t *mtx;
pthread_barrier_t bar;
int N, M;

void *race(void *a) {
	int i = *(int*)a;
	printf("Thread %d waiting...\n", i);
	pthread_barrier_wait(&bar);
	int j;
	for(j=0;j<M;j++) {
		pthread_mutex_lock(&mtx[i]);
		printf("Thread %d entered checkpoint %d\n", i, j);
		int n = (rand() % 101 +100) * 1000;
		usleep(n);
		pthread_mutex_unlock(&mtx[i]);
	}

	printf("Thread %d finished\n", i);

	free(a);
	
	return NULL;
}

int main(int argc, char** argv) {
	if(argc != 3) {
		printf("Introduce 2 arguments!\n");
		exit(1);
	}

        N = atoi(argv[1]);
        M = atoi(argv[2]);

	if(pthread_barrier_init(&bar, NULL, N) != 0) {
		perror("Cannot init barrier");
		exit(1);
	}

	mtx = malloc(sizeof(pthread_mutex_t) * M);

	int i;

	for(i=0;i<M;i++)
		if(pthread_mutex_init(&mtx[i], NULL) != 0) {
			perror("Cannot init mutex");
			exit(1);
		}

	int *a = malloc(sizeof(int) * N);

	pthread_t t[N];
	for(i=0;i<N;i++) {
		//int *v = (int*)malloc(sizeof(int));
		//*v = i;
		a[i] = i;
		if(pthread_create(&t[i], NULL, race, &a[i]) != 0) {
			perror("Cannot create thread");
			exit(1);
		}
	}
	for(i=0;i<N;i++)
		pthread_join(t[i], NULL);
	
	pthread_barrier_destroy(&bar);

	for(i=0;i<M;i++)
		pthread_mutex_destroy(&mtx[i]);

	free(mtx);	

	return 0;
}
