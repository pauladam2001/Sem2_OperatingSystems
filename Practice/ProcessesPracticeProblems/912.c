#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <ctype.h>
#include <sys/wait.h>

//Write a C program that creates a child process. The parent reads strings from keyboard and sends them to the child via pipe. The child prints a message for each string that contains only digits. The parent and the child terminate once the parent reads "stop"

int main(int argc, char** argv) {
	int p2c[2], f;

	pipe(p2c);

	if(p2c < 0) {
		perror("Error on pipe");
		exit(1);
	}

	f = fork();

	if(f < 0) {
		perror("Error on fork");
		exit(1);
	}
	if(f == 0) {
		close(p2c[1]);

		while(1) {
			int length = 0;
			if(read(p2c[0], &length, sizeof(int)) < 0) {
				perror("Error on reading");
				close(p2c[0]);
				exit(1);
			}
			if(length == 0)
				break;
		    else {
			char* buffer = (char*)malloc(sizeof(char)*(length+1));
			if(read(p2c[0], buffer, length*sizeof(char)) < 0) {
				perror("Error on reading");
				close(p2c[0]);
				exit(1);
			}
			buffer[length] = 0;
			//if(strcmp(buffer, "stop") == 0)
			//	break;
			int i, sem = 1;
			for(i=0;i<strlen(buffer);i++) {
				if(!isdigit(buffer[i]))
					sem = 0;
			}
			if(sem == 1)
				printf("%s has only digits\n", buffer);
			free(buffer);			
		   }
		}
		close(p2c[0]);
		exit(0);
	}

	close(p2c[0]);
	
	while(1) {
		char* buffer = (char*)malloc(sizeof(char)*300);
		printf("Introduce a string\n");
		scanf("%s", buffer);
		int length = strlen(buffer);
		if(strcmp(buffer, "stop") == 0) {
			length = 0;
			if(write(p2c[1], &length, sizeof(int)) < 0) {
				perror("Error on sending");
				close(p2c[1]);
				exit(1);
			} 	
			break;
		}
		if(write(p2c[1], &length, sizeof(int)) < 0) {
			perror("Error on sending");
			close(p2c[1]);
			exit(1);
		}
		if(write(p2c[1], buffer, length*sizeof(char)) < 0) {
			perror("Error on sending");
			close(p2c[1]);
			exit(1);
		}
		free(buffer);
	}

	close(p2c[1]);
	wait(0);	

	return 0;
}
