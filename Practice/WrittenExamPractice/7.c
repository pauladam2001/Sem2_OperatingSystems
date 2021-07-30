#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
	int i, p = 0;
	for(i=0;i<3;i++) {
		//printf("Da\n");
		if(p == 0) {
			p = fork();
			printf("Da\n");
		}
		else
			wait(0);
	}
	return 0;
}
