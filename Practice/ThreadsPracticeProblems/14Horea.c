#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>

void *convert(void *a) {
	char *str = (char*)a;
	int i;
	int n = strlen(str);
	for(i=0;i<n;i++)
		str[i] = toupper(str[i]);

	return NULL;
}

int main(int argc, char** argv) {
	if(argc < 2) {
		printf("Introduce at least one argument!\n");
		exit(1);
	}

	pthread_t t[argc-1];
	int i;
	for(i=1;i<argc;i++)
		if(pthread_create(&t[i-1], NULL, convert, argv[i]) != 0) {
			perror("Cannot create thread");
			exit(1);
		}
	for(i=1;i<argc;i++)
		pthread_join(t[i-1], NULL);

	for(i=1;i<argc;i++)
		printf("%s\n", argv[i]);

	return 0;
}
