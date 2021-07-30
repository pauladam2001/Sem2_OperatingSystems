#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
int* freq;

void *f( void *a) {
	int nr = *(int*)a;
	pthread_mutex_lock(&mtx);
	while(nr != 0) {
		int digit = nr%10;		// we can move the mutexes only to surround the "freq[digit]++"
		nr /= 10;
		freq[digit]++;
	}
	pthread_mutex_unlock(&mtx);

	free(a);
	return NULL;
}

int main(int argc, char** argv) {
	if(argc < 2) {
		printf("Introduce at least one argument!\n");
		exit(1);
	}

	freq = (int*)malloc(10 * sizeof(int));

	int i;

	for(i=0;i<=9;i++)
		freq[i] = 0;

	pthread_t t[argc-1];
	for(i=1;i<argc;i++) {
		int *nr = (int*)malloc(sizeof(int));
		*nr = atoi(argv[i]);
		if(pthread_create(&t[i-1], NULL, f, nr) != 0) {
			perror("Cannot create thread");
			exit(1);
		}
	}

	for(i=1;i<argc;i++)
		pthread_join(t[i-1], NULL);

	for(i=0;i<=9;i++)
		printf("Digit %d appears %d times\n", i, freq[i]);

	free(freq);

	pthread_mutex_destroy(&mtx);

	return 0;
}
