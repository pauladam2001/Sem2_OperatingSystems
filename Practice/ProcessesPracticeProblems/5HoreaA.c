#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#define SIZE 300

void write_to_fifo(int a2b, char*buf) {
	int nr = strlen(buf);
	if(write(a2b, &nr, sizeof(int)) < 0)
		perror("Error on write size to fifo");
	if(write(a2b, buf, nr*sizeof(char)) < 0) 
		perror("Error on write message to fifo");
}

int main(int argc, char** argv) {
	int a2b, k;
	char *cmd = (char*)malloc(SIZE*sizeof(char));
	FILE *f;
	char *buf = (char*)malloc(SIZE*sizeof(char));
	memset(buf, 0, SIZE*sizeof(char));

	a2b = open("a2b", O_WRONLY);

	if(a2b < 0) {
		perror("Error on opening fifo");
		exit(1);
	} 	
	
	while(1) {
		//read commands from stdin (alias 0), this way we get whitespaces too
		if((k = read(0, cmd, SIZE*sizeof(char))) < 0) {
			perror("Error reading command");
		}	
		cmd[k-1] = 0;
		if(strcmp(cmd, "stop") == 0) {
			printf("Exiting...\n");
			break;
		}
		//execute the command
		if((f = popen(cmd, "r")) == NULL) {
			perror("Error on popen");
		} else {
			//keep reading the output of the command until done
			while(fread(buf, 1, SIZE-1, f) > 0) {
				write_to_fifo(a2b, buf);
				memset(buf, 0, SIZE*sizeof(char));
			}
		}
		pclose(f);
		memset(cmd, 0, SIZE*sizeof(char));
	}
	int stop = -1;
	//send message to stop
	if(write(a2b, &stop, sizeof(int)) < 0) {
		perror("Error on write size to fifo");
	}
	close(a2b);
	free(cmd);
	free(buf);
	return 0;
}
