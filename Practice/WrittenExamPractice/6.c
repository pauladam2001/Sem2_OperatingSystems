#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	if(fork() != fork()) 
		fork();
	printf("Da\n");
	int i;
	for(i=0;i<8;i++)
		wait(0);
	return 0;	
}
