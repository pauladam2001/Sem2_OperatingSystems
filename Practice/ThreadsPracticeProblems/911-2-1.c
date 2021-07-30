#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char** argv) {
	srandom(time(NULL));
	int pa;
	int p2c[2], c2p[2];
	int N = rand() % 20 + 10;
	//char* string = (char*)malloc(N * sizeof(char));
	char string1[N];
	int i;
	for(i=0;i<N;i++) {
		string1[i] = 'a';
		printf("%c", string1[i]);
	}
	printf("\n");		

	if(pipe(p2c) < 0) {
		perror("Error on pipe");
		exit(1);
	}
	if(pipe(c2p) < 0) {
                perror("Error on pipe");
                exit(1);
        }

	if(write(p2c[1], &N, sizeof(int)) < 0) {
		perror("Error on write N");
		close(p2c[1]);
		exit(1);
	}
	if(write(p2c[1], string1, N*sizeof(char)) < 0) {
		perror("Error on write string");
		close(p2c[1]);
		exit(1);
	}

	pa = fork();
	if(pa < 0) {
		perror("Error on fork");
		exit(1);
	}
	if(pa == 0) {
		int N;
		close(p2c[1]);
		close(c2p[0]);
		if(read(p2c[0], &N, sizeof(int)) < 0) {
			perror("Error on read N");
			close(p2c[0]);
			close(c2p[1]);
			exit(1);
		}
		char* string = (char*)malloc(sizeof(char) * (N+1));
		if(read(p2c[0], string, N* sizeof(char)) < 0) {
                        perror("Error on read string");
                        close(p2c[0]);
			close(c2p[1]);
                        exit(1);
                }
		close(p2c[0]);		
		int i;
		for(i=0;i<N;i++) {
			int nr = rand() % 25;
			printf("Random nr %d\n", nr);
			string[i] += nr;			
		}	
	
        	if(write(c2p[1], string, N*sizeof(char)) < 0) {
                	perror("Error on write string child");
                	close(p2c[1]);
                	exit(1);
        	}
		close(c2p[1]);
		free(string);
		exit(0);
	}

	close(p2c[1]);
	close(p2c[0]);
	close(c2p[1]);
	wait(0);

	char* string2 = (char*)malloc(N*sizeof(char));
	if(read(c2p[0], string2, N* sizeof(char)) < 0) {
                perror("Error on read string");
                close(p2c[0]);
        	exit(1);
	}	

	printf("The generated number is %d\n", N);
	printf("The string is %s\n", string2);
	
	free(string2);
	close(c2p[0]);

	return 0;
}
