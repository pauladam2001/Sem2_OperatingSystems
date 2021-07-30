#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mtx1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx2 = PTHREAD_MUTEX_INITIALIZER;

int vowel = 0;
int cons = 0;

void *f(void *a) {
	char i = *(char*)a;
	if(i == 'a' || i == 'e' || i == 'i' || i == 'o' || i == 'u') {
		pthread_mutex_lock(&mtx1);
		vowel++;
		pthread_mutex_unlock(&mtx1);
	}
	else {
		pthread_mutex_lock(&mtx2);
		cons++;
		pthread_mutex_unlock(&mtx2);
	}

	return NULL;
}

int main(int argc, char** arg) {
	int N = 5, i;
	char* array = (char*)malloc(sizeof(char) * N);
	for(i=0;i<N;i++) {
		printf("Character:\n");
		char ch, empty;
		scanf("%c", &ch);
		scanf("%c", &empty);
		array[i] = ch; 
	}	

	pthread_t t[N];
	for(i=0;i<N;i++) {
		char *v = (char*)malloc(sizeof(char));
		*v = array[i];
		if(pthread_create(&t[i], NULL, f, v) != 0) {
			perror("Cannot create thread");
			exit(1);
		}
	}

	for(i=0;i<N;i++)
		pthread_join(t[i], NULL);

	pthread_mutex_destroy(&mtx1);
	pthread_mutex_destroy(&mtx2);

	printf("%d vowels\n", vowel);
	printf("%d cons\n", cons);

	free(array);

	return 0;
}
