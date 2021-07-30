#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 3

int main(int argc, char** argv) {
	int a2b[2], b2c[2], c2a[2];

	pipe(a2b);
	pipe(b2c);
	pipe(c2a);

	if(a2b < 0 || b2c < 0 || c2a < 0) {
		perror("Error on pipe");
		exit(1);
	}

	int ca = fork();

	if(ca < 0) {
		perror("Error on ca");
		exit(1);
	}
	if(ca == 0) {
		close(c2a[1]);
		close(a2b[0]);
		close(b2c[1]);
		close(b2c[0]);
		int i;
		for(i=1;i<=N;i++) {
			int number;
			printf("Enter a number\n");
			scanf("%d", &number);
			if(write(a2b[1], &number, sizeof(int)) < 0) {
                                        perror("Error on send nr to B");
                                        close(a2b[1]);
                                        close(c2a[0]);
                                        exit(1);
			}
			printf("Sent %d to B\n", number);
		}	
		int result;
		if(read(c2a[0], &result, sizeof(int)) < 0) {
			perror("Error on read from C");
			close(a2b[1]);
			close(c2a[0]);
			exit(1);
		}
		printf("The result is: %d\n", result);
		
		close(a2b[1]);
		close(c2a[0]);
		exit(0);
	}

	int cb = fork();
	
	if(cb < 0) {
                perror("Error on cb");
                exit(1);
        }
	if(cb == 0) {
		close(a2b[1]);
		close(b2c[0]);
		close(c2a[0]);
		close(c2a[1]);
		int i;
		int randomNr;
		//int receivedNr;
		for(i=1;i<=N;i++) {
			int receivedNr;
			randomNr = random()%4 + 2;
			if(read(a2b[0], &receivedNr, sizeof(int)) < 0) {
				perror("Error on read nr from A");
				close(a2b[0]);
				close(b2c[1]);
				exit(1);
			}
			printf("Received %d from A\n", receivedNr);
			receivedNr += randomNr;
			if(write(b2c[1], &receivedNr, sizeof(int)) < 0) {
                                        perror("Error on send nr to C");
                                        close(a2b[0]);
                                        close(b2c[1]);
                                        exit(1);
			}
			printf("Sent %d to C\n", receivedNr); 
		}
		
		close(a2b[0]);
		close(b2c[1]);
		exit(0);
	}
	
	int cc = fork();

	if(cc < 0) {
		perror("Error on cc");
		exit(1);
	}
	if(cc == 0) {
		close(a2b[0]);
		close(a2b[1]);
		close(b2c[1]);
		close(c2a[0]);
		int i;
		int total;
		for(i=1;i<=N;i++) {
			int received;
			if(read(b2c[0], &received, sizeof(int)) < 0) {
				perror("Error on read nr from B");
				close(b2c[0]);
				close(c2a[1]);
				exit(1);
			}
			printf("Received %d from B\n", received);
			total += received;
		}
		if(write(c2a[1], &total, sizeof(int)) < 0) {
			perror("Error on send nr to A");
			close(b2c[0]);
			close(c2a[1]);
			exit(1);
		}
		printf("Sent the final result (%d) to A\n", total);
	
		close(b2c[0]);
		close(c2a[1]);
		exit(0);
	}

	//parent
	close(a2b[0]);
	close(a2b[1]);
	close(b2c[0]);
	close(b2c[1]);
	close(c2a[0]);
	close(c2a[1]);

	wait(0);
	wait(0);
	wait(0);
	
	return 0;
}

