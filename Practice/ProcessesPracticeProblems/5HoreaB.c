#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define SIZE 300

int main() {
	int a2b, k, dim, i;
	char *buf = (char*)malloc(SIZE*sizeof(char));
	memset(buf, 0, SIZE*sizeof(char));
	
	a2b = open("a2b", O_RDONLY);

	if(a2b < 0) {
		perror("Error opening fifo");
		exit(1);
	}

	while(1) {
		//read length of incoming string
		if(read(a2b, &dim, sizeof(int)) < 0) {
			perror("Error on read size from fifo");
		}
		//stop condition
		if(dim < 0)
			break;
		i = 0;
		//keep reading until we read exactly dim bytes
		while(i < dim) {
			int size = (dim - i > SIZE - 1) ? SIZE - 1 : dim - i;
			if((k = read(a2b, buf, size)) < 0) {
				perror("Error on read message from fifo");
			} else {
				i += k;
				printf("%s", buf);
				memset(buf, 0, SIZE*sizeof(char));
			}
		}
		fflush(stdout);
	}
	free(buf);
	close(a2b);
	return 0;
}
