#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *s(void *a) {
	printf("Slow thread started\n");
	sleep(rand() % 6 + 5);

	printf("Slow phase 1 done\n");	
	pthread_cond_signal(&cond);
	printf("Slow phase 2 done\n");
	
	return NULL;
}

void *f(void *a) {
	printf("Fast thread started\n");
        sleep(rand() % 2 + 2);

        printf("Fast phase 1 done\n");

	pthread_mutex_lock(&mutex);
	printf("Fast thread is waiting\n");
	pthread_cond_wait(&cond, &mutex);
	printf("Fast phase 2 done\n");
	pthread_mutex_unlock(&mutex);
	printf("Fast thread is done\n");

	return NULL;
}

int main() {
	pthread_t slow, fast;
	if(pthread_create(&slow, NULL, s, NULL) != 0) {
		perror("Cannot create thread");
		exit(1);
	}
	if(pthread_create(&fast, NULL, f, NULL) != 0) {
                perror("Cannot create thread");
                exit(1);
        }
	
	pthread_join(slow, NULL);
	pthread_join(fast, NULL);

	return 0;
}
