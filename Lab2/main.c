#include <stdio.h>
#include <stdlib.h>
int main() {
	int n;
	printf("Please enter n:");
	scanf("%d",&n);
	printf("n: %d\n",n);
	char *a=(char*)malloc(n*sizeof(char));
	if (a!=NULL) {
		printf("allocatd properly!\n");
		free(a);
	}
	return 0;
}
