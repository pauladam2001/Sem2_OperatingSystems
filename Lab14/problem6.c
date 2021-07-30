#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int ct = 0;

int main(int argc, char** argv) {
	int i;
	for(i=0;i<3;i++) {
		if(i%2==1) {
			//ct += 1;
			fork();
			ct += 1;
		}
		//ct += 1;
		fork();   //OR exec
		ct += 1;
	}
	for(i=0;i<3;i++) {
		if(i%2==1)
			wait(0);
		wait(0);
	}
	printf("The ct is %d\n", ct);
	return 0;
}
