#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SIZE 500//sau puteam sa mergem intr-un for prin toate argumentele sa calculam size-ul

int main(int argc, char** argv) {
	int i, a2b, b2a;
	
	if(argc < 2) {
		printf("Introduce at least one argument!");
		exit(1);
	}
	
	a2b = open("a2b", O_WRONLY);
	b2a = open("b2a", O_RDONLY);

	if(a2b<0 || b2a<0) {
		perror("Error on FIFO A");
		exit(1);
	}	
	
	//if(write(a2b, &argc, sizeof(int)) < 0) {
	//	perror("Error on send argc A");		//We use a while(1) in B instead
	//	exit(1);
	//} 

	for(i=1;i<argc;i++) {
		int length = strlen(argv[i]);
		if(write(a2b, &length, sizeof(int)) < 0) {
			perror("Error on send len A");
			exit(1);
		}
		if(write(a2b, argv[i], length*sizeof(char)) < 0) {
			perror("Error on send arg A");
			exit(1);
		}
	}
	
	char concat[SIZE] = "";	
	
	for(i=1;i<argc;i++) {
		int length = 0;
		if(read(b2a, &length, sizeof(int)) < 0) {
			perror("Error on read len A");
			exit(1);
		}
		char* buffer = (char*)malloc(sizeof(char)*(length+1));
		if(read(b2a, buffer, length*sizeof(char)) < 0) {
			perror("Error on read arg A");
			exit(1);
		}
		buffer[length] = 0;
		strcat(concat, buffer);
		free(buffer);				
	}	
	
	printf("%s\n", concat);
	
	close(a2b);
	close(b2a);
	
	return 0;		
}
