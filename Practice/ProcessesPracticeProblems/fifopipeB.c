#include <sys/types.h>
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

//Scrieti 2 programe C, A si B. Programul A va citi numere intregi de la tastatura si le va scrie intr-un fifo. Programul B va creea 2 procese P1 si P2, P1 va citi numerele din fifo si va calcula suma acestora. Suma va fi transmisa printr-un pipe procesului P2 care va afisa pe ecran divizorii acesteia.

int main(int argc, char** arv) {
        int a2b;

        a2b = open("a2b", O_RDONLY);

        if(a2b < 0) {
                perror("Error on fifo");
                exit(1);
        }

   	int p1, p2, p1top2[2];

	pipe(p1top2);

	if(p1top2 < 0) {
		perror("Error on pipe");
		exit(1);
	}

	p1 = fork();
	if(p1 < 0) {
		perror("Error on fork");
		exit(1);
	}
	if(p1 == 0) {
		close(p1top2[0]);
		int N, i, sum = 0;
		if(read(a2b, &N, sizeof(int)) < 0) {
			perror("Error on read from fifo");
			close(p1top2[1]);
			exit(1);		
		}
		for(i=0;i<N;i++) {
			int nr;
			if(read(a2b, &nr, sizeof(int)) < 0) {
				perror("Error on read from fifo");
				close(p1top2[1]);
				exit(1);
			}
			sum += nr;
		}
		if(write(p1top2[1], &sum, sizeof(int)) < 0) {
			perror("Error on write to pipe");
			close(p1top2[1]);
			exit(1);
		}
		close(p1top2[1]);
		exit(0);
	}

    	p2 = fork();
	if(p2 < 0) {
		perror("Error on fork");
		exit(1);
	}
	if(p2 == 0) {
		close(p1top2[1]);
		int sum, d;
		if(read(p1top2[0], &sum, sizeof(int)) < 0) {
			perror("Error on read from pipe");
			close(p1top2[0]);
			exit(1);
		}
		printf("The sum is: %d\n", sum);
		for(d=1;d<=sum/2;d++) {
			if(sum % d == 0)
				printf("%d\n", d);
		}
		close(p1top2[0]);
		exit(0);
	}
	
	close(p1top2[0]);
	close(p1top2[1]);
	wait(0);
	wait(0);
	close(a2b);

        return 0;
}

