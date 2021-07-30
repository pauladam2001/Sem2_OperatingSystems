#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

char vowels_global[1000] = {0};
int digits_global = 0;

pthread_mutex_t mtxa = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtxb = PTHREAD_MUTEX_INITIALIZER;

void *fa(void *a) {
	char *array = (char*)a;
	int i;

	for(i=0;i<strlen(array);i++) {
		if(array[i] == 'a' || array[i] == 'e' || array[i] == 'i' || array[i] == 'o' || array[i] == 'u') {
			pthread_mutex_lock(&mtxa);
			strncat(vowels_global, &array[i], 1);
			pthread_mutex_unlock(&mtxa);
		}
	}

	return NULL;
}

void *fb(void *b) {
	char *array = (char*)b;
	int i;

	for(i=0;i<strlen(array);i++) {
		if(isdigit(array[i])) {
			int nr = atoi(&array[i]);
			pthread_mutex_lock(&mtxb);
			digits_global += nr;
			pthread_mutex_unlock(&mtxb);
		}
	}

	return NULL;
}

int main(int argc, char** argv) {
	int pa, pb, a2p[2], b2p[2];

	if(argc == 1) {
		printf("Introduce some arguments!\n");
		exit(1);
	}

	if(pipe(a2p) < 0) {
		perror("Error on pipe");
		exit(1);
	}
	if(pipe(b2p) < 0) {
		perror("Error on pipe");
		exit(1);
	}

	pa = fork();

	if(pa < 0) {
		perror("Error on pa");
		exit(1);
	}
	if(pa == 0) {
		close(b2p[0]);
		close(b2p[1]);
		close(a2p[0]);

		pthread_t ta[argc-1];
		int i;
		for(i=1;i<argc;i++) {		
			if(pthread_create(&ta[i-1], NULL, fa, argv[i]) != 0) {
				perror("Cannot create ta");
				exit(1);
			}
		}
		for(i=1;i<argc;i++)
			pthread_join(ta[i-1], NULL);		
		
		int length = strlen(vowels_global);
		if(write(a2p[1], &length, sizeof(int)) < 0) {
			perror("Error on sending length a");
			close(a2p[1]);
			exit(1);
		}
		if(write(a2p[1], vowels_global, length*sizeof(char)) < 0) {
                        perror("Error on sending vowels");
                        close(a2p[1]);
                        exit(1);
                }
		
		pthread_mutex_destroy(&mtxa);
		close(a2p[1]);
		exit(0);
	}

	pb = fork();
	
	if(pb < 0) {
		perror("Error on pb");
		exit(1);
	}
	if(pb == 0) {
		close(a2p[0]);
		close(a2p[1]);
		close(b2p[0]);

		pthread_t tb[argc-1];
		int i;

		for(i=1;i<argc;i++) {
			if(pthread_create(&tb[i-1], NULL, fb, argv[i]) != 0) {
				perror("Cannot create tb");
				exit(1);
			}
		}
		for(i=1;i<argc;i++)
			pthread_join(tb[i-1], NULL);

		if(write(b2p[1], &digits_global, sizeof(int)) < 0) {
			perror("Error on sending digits");
			close(b2p[1]);
			exit(1);
		}

		pthread_mutex_destroy(&mtxb);
		close(b2p[1]);
		exit(0);
	}

	close(a2p[1]);
	close(b2p[1]);

	int length = 0;
	if(read(a2p[0], &length, sizeof(int)) < 0) {
		perror("Error on reading length a");
		close(a2p[0]);
		close(b2p[0]);
		exit(1);
	}
	char* buffer = (char*)malloc(sizeof(char)*(length+1));
	if(read(a2p[0], buffer, length*sizeof(char)) < 0) {
                perror("Error on reading vowels");
                close(a2p[0]);
                close(b2p[0]);
                exit(1);
        }

	printf("The vowels are: %s\n", buffer);
	
	free(buffer);

	int sum = 0;
	if(read(b2p[0], &sum, sizeof(int)) < 0) {
		perror("Error on reading digits");
		close(a2p[0]);
		close(b2p[0]);
		exit(1);
	}

	printf("The sum of the digits is: %d\n", sum);

	close(a2p[0]);
	close(b2p[0]);

	wait(0);
	wait(0);
	
	return 0;
}
