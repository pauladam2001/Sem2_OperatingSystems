#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int N, M;
pthread_mutex_t *mutexes;
pthread_barrier_t barrier;


void *f(void *a) {
    int j = *((int*)a);
    int i;
    printf("Thread %d is waiting...\n", j);
    pthread_barrier_wait(&barrier);
    for (i = 0; i < M; i++) {
        pthread_mutex_lock(&mutexes[i]);
        printf("Thread %d has entered checkpoint %d\n", j, i);
        int n = (random() % 101 + 100) * 1000;
        usleep(n);
        pthread_mutex_unlock(&mutexes[i]);
    }
    printf("Thread %d finished\n", j);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Please provide 2 arguments!\n");
        exit(1);
    }

    int *a = malloc(sizeof(int) * N);

    N = atoi(argv[1]);
    M = atoi(argv[2]);
    pthread_t *t = malloc(sizeof(pthread_t) * N);
    mutexes = malloc(sizeof(pthread_mutex_t) * M);
    if (0 > pthread_barrier_init(&barrier, NULL, N)) {
        free(t);
	free(mutexes);
        exit(1);
    }
    int i;
    for (i = 0; i < M; i++) {
        if(0 > pthread_mutex_init(&mutexes[i], NULL)) {
            int j;
	    for(j=0;j<i;j++)
		pthread_mutex_destroy(&mutexes[j]);
            pthread_barrier_destroy(&barrier);
            free(t);
	    free(mutexes);
            exit(1);
        }
    }
    srandom(time(NULL));
    for (i = 0; i < N; i++) {
     	a[i] = i;
        if(0 > pthread_create(&t[i], NULL, f, (void *)&a[i])) {
            perror("Error on create thread");
            //wait_threads(T, i);
            //pthread_barrier_destroy(&barrier);
            //destroy_mutexes(mutexes, M);
            //cleanup(T, args, mutexes);
            exit(1);
        }
    }
    
    for(i=0;i<N;i++)
	pthread_join(t[i], NULL);	

    pthread_barrier_destroy(&barrier);
    
    for(i=0;i<M;i++)
	pthread_mutex_destroy(&mutexes[i]);

    free(t);
    free(mutexes);   
    
    return 0;
}
