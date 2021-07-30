//Write a C program that receives a number N as a command line argument. The program creates N threads. Each thread generates 2 random integers between 0 and 999. The thread will displayits index number and the generated numbers. If both generated numbers have different paritiesthe thread will add the numbers to a global array. Once all the threads finish, the main process prints the contents of the array. Use efficient synchroniaztion mechanisms.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int* array;
int idx;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *f(void *a) {
	int i = *(int*)a;
	int rand1, rand2;
	rand1 = rand() % 1000;
	rand2 = rand() % 1000;

	printf("Thread %d generated %d and %d\n", i, rand1, rand2);

	if(rand1 % 2 != rand2 % 2) {
		pthread_mutex_lock(&mtx);
		array[idx] = rand1;
		idx++;
		array[idx] = rand2;
		idx++;
		pthread_mutex_unlock(&mtx);
	}
	free(a);
	return NULL;
}

int main(int argc, char** argv) {
	srandom(time(NULL));	

	if(argc != 2) {
		printf("Enter exactly one argument!\n");
		exit(1);
	}

	int N;
	N = atoi(argv[1]);

	idx = 0;
	array = (int*)malloc(2 * N * sizeof(int));

	int i;
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

	for(i=0;i<idx;i++)
		printf("%d ", array[i]);
	printf("\n");

	pthread_mutex_destroy(&mtx);

	free(array);

	return 0;
}
