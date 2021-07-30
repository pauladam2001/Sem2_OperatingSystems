#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define N 3

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void* f(void* a) {
	int idx = (int)pthread_self();
	printf("Fast thread %d started\n", idx);
	int r = rand() % 2 + 1;

	sleep(r);

	printf("Thread %d phase 1 s done\n", idx);

	pthread_mutex_lock(&m);		//m is locked
	pthread_cond_wait(&c, &m);	//the wait call is unlocking the mutex and it is registering the thread in the queue and then it is unlocking the mutex again

	printf("Thread %d starting phase 2\n", idx);

	pthread_mutex_unlock(&m);

	return NULL;
}

void* s(void* a) {
        int idx = (int)pthread_self();
        printf("Slower thread %d started\n", idx);
        int r = rand() % 2 + 3;

        sleep(r);

        printf("Thread %d phase 1 s done\n", idx);

	pthread_cond_broadcast(&c);  //we use broadcast because we have multiple fast threads

        printf("Thread %d starting phase 2\n", idx);

        return NULL;
}


int main() {
	pthread_t t[N];

	int i;
	for(i=0;i<N-1;i++) {	//the first 2 threads will be the fast ones
		if(pthread_create(&t[i], NULL, f, NULL) != 0) {
			perror("Cannot create thread");
			exit(1);
		}
	}
	
	if(pthread_create(&t[i], NULL, s, NULL) != 0) {
		perror("Cannot create thread");
		exit(1);
	}

	for(i=0;i<N;i++)
		pthread_join(t[i], NULL);

	return 0;
}
