#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int* array;
int idx = 0;
int counter = 0;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx2 = PTHREAD_MUTEX_INITIALIZER;

void *f(void *a) {
	int i = *(int*)a;
	//pthread_mutex_lock(&mtx);
	
	if(i%2 == 0) {
		pthread_mutex_lock(&mtx);
		array[idx] = i;
		idx++;
		pthread_mutex_unlock(&mtx);
	}
	else {
		pthread_mutex_lock(&mtx2);
		counter++;
		pthread_mutex_unlock(&mtx2);
	}

	//pthread_mutex_unlock(&mtx);

	free(a);
	return NULL;
}

int main(int argc, char** argv) {
	if(argc == 1) {
		printf("Introduce some arguments\n");
		exit(1);
	}

	array = (int*)malloc((argc - 1) * sizeof(int));

	pthread_t t[argc-1];
	int i;
	for(i=1;i<argc;i++) {
		int nr = atoi(argv[i]);
		int *v = (int*)malloc(sizeof(int));
		*v = nr;
		if(pthread_create(&t[i-1], NULL, f, v) != 0) {
			perror("Cannot create thread");
			exit(1);
		}
	}

	for(i=1;i<argc;i++)
		pthread_join(t[i-1], NULL);

	for(i=0;i<idx;i++)
		printf("%d ", array[i]);

	printf("\n");
	printf("The counter is %d\n", counter);

	pthread_mutex_destroy(&mtx);
	pthread_mutex_destroy(&mtx2);

	free(array);

	return 0;
}
