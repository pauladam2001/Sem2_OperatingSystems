#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FIFO "f"
#define MAX_LEN 100

int main(int argc, char** argv) {
	
	if(mkfifo(FIFO, 0600) < 0) {
		perror("Error on create FIFO");
		exit(1);
	}

	printf("input=");
	char* input = (char*)malloc(sizeof(char)*MAX_LEN);
	scanf("%100s", input);

	int fd = open(FIFO, O_WRONLY);
	if(fd < 0) {
		perror("FIFO not opened");
		exit(1);
	}

	int length = strlen(input);	
	if(write(fd, &length, sizeof(int)) < 0) {
		perror("Error on send");
		exit(1);
	}
	if(write(fd, input, sizeof(char)*length) < 0) {
		perror("Error on send");
		exit(1);
	}

	close(fd);
	unlink(FIFO);	

	return 0;
}
