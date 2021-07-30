#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv){
	int a2b[2], b2a[2];
	pipe(a2b);
	pipe(b2a);
	int c1 = fork();
	if(c1 < 0) {
		perror("Error on c1 fork");
		exit(1);
	}
	if(c1 == 0) {		//A
		close(a2b[0]);
		close(b2a[1]);
	   while(1) {
		int nr;
		nr=rand()%10+1;
		if(write(a2b[1], &nr, sizeof(int))<0) {
			perror("Error on sending from A to B");
			close(a2b[1]);
			close(b2a[0]);
			exit(1);
		}
		printf("Send %d to B\n", nr);
		//else {
			if(read(b2a[0], &nr, sizeof(int))<0) {
				perror("Error on reading in A");
				close(a2b[1]);
				close(b2a[0]);
				exit(1);
			}
			if(nr == 10) {
				printf("Found number 10\n");
				break;
			}
		//}
	    }
		close(a2b[1]);
		close(b2a[0]);
		exit(0);
	}
	int c2 = fork();
	if(c2 < 0) {
		perror("Error on c2 fork");
		exit(1);
	}
	if(c2 == 0) {		//B
		close(b2a[0]);
		close(a2b[1]);
	  while(1) {
		int nr;
	        if(read(a2b[0], &nr, sizeof(int))<0) {
                        perror("Error on reading in B");
                        close(b2a[1]);
                        close(a2b[0]);
                        exit(1);
                }
                if(nr == 10) {
                        printf("Found number 10\n");
                        break;
                }
                else {
                        nr=rand()%10+1;
                        if(write(b2a[1], &nr, sizeof(int))<0) {
                                perror("Error on sending from B to A");
                                close(b2a[1]);
                                close(a2b[0]);
                                exit(1);
                        }
                        printf("Send %d to A\n", nr);
                }
	  }
                close(b2a[1]);
                close(a2b[0]);
                exit(0);	
	}
	//parent
	close(a2b[0]);
	close(a2b[1]);
	close(b2a[0]);
	close(b2a[1]);
	wait(0);
	wait(0);
	return 0;		
}
