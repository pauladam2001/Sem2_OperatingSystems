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
	int a2b, N;

	a2b = open("a2b", O_WRONLY);

	if(a2b < 0) {
		perror("Error on fifo");
		exit(1);
	}	

	printf("N:\n");
	scanf("%d", &N);
	if(write(a2b, &N, sizeof(int)) < 0) {
		perror("Error on write in fifo");
		exit(1);
	}

	int i;
	for(i=0;i<N;i++) {
		int nr;
		printf("Number:\n");
		scanf("%d", &nr);
		
		if(write(a2b, &nr, sizeof(int)) < 0) {
			perror("Error on write in fifo");
			exit(1);
		}
	}

	close(a2b);

	return 0;
}
