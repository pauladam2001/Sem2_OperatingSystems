#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
int digits = 0;
int letters = 0;
int specials = 0;

void *f(void *a) {
	int i, n;
	
	char * str = (char*)a;

	pthread_mutex_lock(&mtx);

	n = strlen(str);
	for(i=0;i<n;i++) {			// faster with 3 mutexes
		if(isalpha(str[i]))
			letters++;
		else if(isdigit(str[i]))
			digits++;
		else
			specials++;
	}

	pthread_mutex_unlock(&mtx);

	return NULL;
}

int main(int argc, char** argv) {
	if(argc < 2) {
		printf("Introduce at least one argument!\n");
		exit(1);
	}

	//printf("%d\n", argc);
	//int i;
	//for(i=1;i<argc;i++)
	//	printf("%s\n", argv[i]);

	int i;
	pthread_t t[argc-1];
	for(i=1;i<argc;i++) {
		if(pthread_create(&t[i-1], NULL, f, argv[i]) != 0) {
			perror("Cannot create thread");
			exit(1);
		}
	}

	for(i=1;i<argc;i++)
		pthread_join(t[i-1], NULL);
	
	printf("The arguments contain %d letters\n", letters);
	printf("The arguments contain %d digits\n", digits);
	printf("The arguments contain %d special characters\n", specials);

	pthread_mutex_destroy(&mtx);

	return 0;
}
