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


	int fd = open(FIFO, O_RDONLY);
	if(fd < 0) {
		perror("FIFO not opened");
		exit(1);
	}

	int length;	
	if(read(fd, &length, sizeof(int)) < 0) {
		perror("Error on read");
		exit(1);
	}
	
	char* input = (char*)malloc(sizeof(char)*(length+1));
	if(read(fd, input, sizeof(char)*length) < 0) {
		perror("Error on read input");
		exit(1);
	}

	input[length] = 0;
	
	printf("Received %s\n", input);
	
	free(input);

	close(fd);	

	return 0;
}
