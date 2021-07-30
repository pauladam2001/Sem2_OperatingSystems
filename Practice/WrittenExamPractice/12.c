#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int n = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* f(void* p) {
	pthread_mutex_lock(&mtx);
	n++;
	pthread_mutex_unlock(&mtx);
	return NULL;
}

int main() {
	int i;
	pthread_t T[10];
	for(i=0;i<10;i++)
		pthread_create(&T[i], NULL, f, NULL);
	for(i=0;i<10;i++)
		pthread_join(T[i], NULL);
	printf("n=%d\n", n);
	pthread_mutex_destroy(&mtx);
	return 0;
}
