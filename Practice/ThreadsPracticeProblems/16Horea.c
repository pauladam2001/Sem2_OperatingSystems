//Write a C program that takes as command line arguments 2 numbers: N and M. The program will simulate a thread race that have to pass through M checkpoints. Through each checkpoint the threads must pass one at a time (no 2 threads can be inside the same checkpoint). Each thread that enters a checkpoint will wait between 100 and 200 milliseconds (usleep(100000) makes a thread or process wait for 100 milliseconds) and will print a message indicating the thread number and the checkpoint number, then it will exit the checkpoint.

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int n, m;
pthread_mutex_t mutex[100];

void* race(void* a) {
	int count = 0;
	int j = *((int*)a);
	while(count < m) {
		pthread_mutex_lock(&mutex[count]);
		
		printf("%d passes through: %d\n", j, count);

		usleep(100000);

		pthread_mutex_unlock(&mutex[count]);

		count++;
	}
	return NULL;
}

int main(int argc, char** argv) {
	int a[5];
	pthread_t t[100];
	n = atoi(argv[1]); //5
	m = atoi(argv[2]); //6
	int i;

	for(i=0;i<m;i++)
		pthread_mutex_init(&mutex[i], NULL);
	for(i=0;i<n;i++) {
		a[i] = i;
		pthread_create(&t[i], NULL, race, (void*)&a[i]);
	}	
	for(i=0;i<n;i++)
		pthread_join(t[i], NULL);

	for(i=0;i<m;i++);
		pthread_mutex_destroy(&mutex[i]);	

	return 0;
}
