#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

int t2c[2];
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *f(void *a) {
	int i = *(int*)a;

	int nr1, nr2;
	nr1 = random() % 100 + 1;
	nr2 = random() % 100 + 1;

	printf("Thread %d generated %d and %d\n", i, nr1, nr2);

	pthread_mutex_lock(&mtx);
	if(write(t2c[1], &i, sizeof(int)) < 0) {
		perror("Error on write i");
		exit(1);
	}
	if(write(t2c[1], &nr1, sizeof(int)) < 0) {
                perror("Error on write nr1");
                exit(1);
        }
	if(write(t2c[1], &nr2, sizeof(int)) < 0) {
                perror("Error on write nr2");
                exit(1);
        }
	pthread_mutex_unlock(&mtx);

	free(a);

	return NULL;
}

int main(int argc, char** argv) {
	srandom(time(NULL));

	int child;

	if(argc != 2) {
		printf("Introduce exactly one argument!\n");
		exit(1);
	}

	if(pipe(t2c) != 0) {
		perror("Error on pipe");
		exit(1);
	}

	int N = atoi(argv[1]);

	pthread_t t[N];
	int i;
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

	child = fork();

	if(child < 0) {
		perror("Error on fork");
		exit(1);
	}
	if(child == 0) {
		close(t2c[1]);

		for(i=0;i<N;i++) {
			int id, nr1, nr2;
			if(read(t2c[0], &id, sizeof(int)) < 0) {
				perror("Error on read id");
				exit(1);
			}
			if(read(t2c[0], &nr1, sizeof(int)) < 0) {
                                perror("Error on read nr1");
                                exit(1);
                        }
			if(read(t2c[0], &nr2, sizeof(int)) < 0) {
                                perror("Error on read nr2");
                                exit(1);
                        }
			float avg = (float)(nr1+nr2) / 2;
			printf("Child received from thread %d and the average is %f\n", id, avg);		
		}
		
		close(t2c[0]);
		exit(0);
	}

	pthread_mutex_destroy(&mtx);
	close(t2c[0]);
	close(t2c[1]);
	
	wait(0);

	return 0;
}
