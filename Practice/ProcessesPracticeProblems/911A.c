#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <ctype.h>
#include <sys/wait.h>

int main() {
	int i, N, a2b, b2a, array[1000];

	a2b = open("a2b", O_WRONLY);
	b2a = open("b2a", O_RDONLY);

	if(a2b<0 || b2a<0) {
		perror("Error on fifo");
		exit(1);
	}
	
	printf("N:\n");
	scanf("%d", &N);
	int nr;

	if(write(a2b, &N, sizeof(int))<0) {
		perror("Error");
		exit(1);
	}

	for(i=0;i<N;i++){
		printf("Number:\n");
		scanf("%d", &nr);
		array[i] = nr;
	}
	//for(i=0;i<N;i++) {
	//	int nr = array[i];
	//	if(write(a2b, &nr, sizeof(int)) < 0) {
	//		perror("Error");
	//		exit(1);
	//	}
	//}
	
	if(write(a2b, array, N*sizeof(int)) < 0) {
		perror("Error");
		exit(1);
	}	

	int res;
	if(read(b2a, &res, sizeof(int)) < 0) {
		perror("Error");
		exit(1);
	}
	printf("The count is %d\n", res);

	close(a2b); close(b2a);

	return 0;
}
