#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>


int main(int argc, char** argv) {
	if(argc != 2) {
		printf("Please provide exactly one argument!\n");
		exit(1);
	}

	int p_to_c[2], c_to_p[2];
	
	pipe(p_to_c);
	pipe(c_to_p);
	
	int f=fork();
	if(f < 0) {
		perror("Error on fork");
		exit(1);
	}
	else if(f == 0) {
		close(p_to_c[1]);
		close(c_to_p[0]);
		
		int n, i ,nr;
		float rez=0;
		
		if(read(p_to_c[0], &n, sizeof(int)) < 0) {
			perror("Error on read n from parent");
			close(p_to_c[0]);
			close(c_to_p[1]);
			exit(1);
		}
		for(i = 0; i < n; i++) {
			if(read(p_to_c[0], &nr, sizeof(int)) < 0) {
				perror("Error on read number from parent");
				close(p_to_c[0]);
				close(c_to_p[1]);
				exit(1);
			}
			rez += nr;
		}
		rez /= n;
		if(write(c_to_p[1], &rez, sizeof(float)) < 0) {
			perror("Error on write result to parent");
			close(p_to_c[0]);
			close(c_to_p[1]);
			exit(1);
		}	
		close(p_to_c[0]);
		close(c_to_p[1]);
		exit(0);
	}
	else {
		close(p_to_c[0]);
		close(c_to_p[1]);

		int n = atoi(argv[1]);
		int i, nr;
		float rez = -1;
			
		srandom(time(0));
		
		if(write(p_to_c[1], &n, sizeof(int)) < 0) {
			perror("Error on write n to child");
			close(p_to_c[1]);
			close(c_to_p[0]);
		}
		for(i = 0 ; i < n; i++) {
			nr = random() % 100;
			printf("Parent generated %d\n", nr);
			if(write(p_to_c[1], &nr, sizeof(int)) < 0) {
				perror("Error on write number to child");
				close(p_to_c[1]);
				close(c_to_p[0]);
			}
		}
		wait(0);
		if(read(c_to_p[0], &rez, sizeof(float)) < 0) {
			perror("Error on read result from child");
		}
		printf("Average is %f\n", rez);
		close(p_to_c[1]);
		close(c_to_p[0]);
	}
	return 0;
}
