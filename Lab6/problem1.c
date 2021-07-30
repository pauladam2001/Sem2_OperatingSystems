#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	int f=fork();
	if(f<0){
	   perror("Unable to create the first copy");
	   exit(1);
	}
	if (f==0){ // C1
	    int f1=fork();
       	     if(f1<0){
          	 perror("Unable to create the second copy");
          	 exit(2);
             }
	     if(f1==0){  // C3
		  printf("C3 only pid: %d parent: %d\n", getpid(), getppid());
		  exit(0);
		}
	     wait(0);
	     printf("Only in C1 pid: %d parent: %d\n", getpid(), getppid());
	     exit(0);
	}
	wait(0);
	printf("process id is: %d parent: %d f: %d\n", getpid(), getppid(), f);
	return 0;
}
