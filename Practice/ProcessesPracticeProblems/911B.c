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
        int i, N, a2b, b2a;

        a2b = open("a2b", O_RDONLY);
        b2a = open("b2a", O_WRONLY);

        if(a2b<0 || b2a<0) {
                perror("Error on fifo");
                exit(1);
        }

        if(read(a2b, &N, sizeof(int)) < 0) {
		perror("Error");
		exit(1);
	}
        int ct = 0;
        //for(i=0;i<N;i++) {
        //       int nr;
	//	if(read(a2b, &nr, sizeof(int)) < 0) {
        //                perror("Error");
        //                exit(1);
        //        }
	//	if(nr % 3 == 0)
	//		ct++;
        //}
        
	int* array = (int*)malloc(N*sizeof(int));

	if(read(a2b, array, N*sizeof(int)) < 0) {
		perror("Error");
		exit(1);
	}

	for(i=0;i<N;i++) {
		if(array[i] % 3 == 0)
			ct++;	
	}

	if(write(b2a, &ct, sizeof(int)) < 0) {
                perror("Error");
                exit(1);
        }
	
	free(array);
	
        close(a2b); close(b2a);

        return 0;
}

