#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char** argv) {
	int pa, pb, pa2pb[2], pb2pa[2];

	pipe(pa2pb);
	pipe(pb2pa);

	if(pa2pb < 0 || pb2pa < 0) {
		perror("Error on pipe");
		exit(1);
	}

	pa = fork();
	
	if(pa < 0) {
		perror("Error on pa");
		exit(1);
	}	
	if(pa == 0) {
		close(pa2pb[0]);
		close(pb2pa[1]);
		srand(time(0));
	        int n = random()%151 + 50;	
		while(1) {
			if(n%2 == 0) {
				if(write(pa2pb[1], &n, sizeof(int)) < 0) {
					perror("Error on send n to B");
					close(pa2pb[1]);
					close(pb2pa[0]);
					exit(1);
				}	
			}
			if(n%2 == 1) {
				n = n+1;
				if(write(pa2pb[1], &n, sizeof(int)) < 0) {
                                        perror("Error on send n to B");
                                        close(pa2pb[1]);
                                        close(pb2pa[0]);
                                        exit(1);
                                }
			}
			printf("Sent %d to B\n", n);
			
			if(read(pb2pa[0], &n, sizeof(int)) < 0) {
				perror("Error on read n from B");
                                close(pa2pb[1]);
                                close(pb2pa[0]);
                                exit(1);
			}
	
			//if(n < 5) {
			//	printf("%d is smaller than 5\n", n);
			//	break;
			//}	
		}	
		
		close(pa2pb[1]);
		close(pb2pa[0]);
		exit(0);
	}

	pb = fork();
	
	if(pb < 0) {
		perror("Error on pb");
		exit(1);
	}
	
	if(pb == 0) {
		close(pb2pa[0]);
		close(pa2pb[1]);
		int n;		
		while(1) {		
			if(read(pa2pb[0], &n, sizeof(int)) < 0) {
				perror("Error on read n from A");
                                close(pa2pb[0]);
                                close(pb2pa[1]);
                                exit(1);
			}
			if(n < 5) {
				printf("%d is smaller than 5\n", n);
				break;
			}
			else {
				n = n/2;
				if(write(pb2pa[1], &n, sizeof(int)) < 0) {
					perror("Error on write n to A");
					close(pa2pb[0]);
					close(pb2pa[1]);
					exit(1);
				}
				printf("Sent %d to A\n", n);
			}
		}
		
		close(pa2pb[0]);
		close(pb2pa[1]);
		exit(0);	
	}
	
	//parent
	close(pa2pb[0]);
	close(pa2pb[1]);
	close(pb2pa[0]);
	close(pb2pa[1]);
	
	wait(0);
	wait(0);
	
	return 0;
}
