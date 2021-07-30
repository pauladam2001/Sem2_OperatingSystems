#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
	int pb, a2b[2];

	pipe(a2b);

	if(a2b < 0) {
		perror("Error on pipe");
		exit(1);
	}
	
	pb = fork();

	if(pb < 0) {
		perror("Error on fork");
		exit(1);
	}
	if(pb == 0) {
		close(a2b[1]);
		int nr = rand()%901 + 100;
		printf("Process B has generated %d\n", nr);
		while(1) {
			int diff = 0;
			int received;
			if(read(a2b[0], &received, sizeof(int)) < 0) {
				perror("Error on read number from A");
				close(a2b[0]);
				exit(1);
			}
			if(received >= nr)
				diff = received - nr;
			else
				diff = nr - received;
			printf("B received %d; difference: %d\n", received, diff);
			if(diff < 50)
				break;
		}
		
		close(a2b[0]);
		exit(0);	
	}

	close(a2b[0]);
	int random = rand()%1000 + 50;
	int ct = 1;
	while(1) {
		if(write(a2b[1], &random, sizeof(int)) < 0) {
			perror("Error on send number to B");
			close(a2b[1]);
			exit(1);
		}
		random = rand()%1001 + 50;
		ct++;
	}
	printf("Process A has generated %d numbers\n", ct);
	
	close(a2b[1]);
	
	wait(0);

	return 0;
}
