#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define LEN 100

int main() {
	printf("Provide a command:");
	char* command = (char*)malloc(sizeof(char)*LEN);
	scanf("%100s", command);
	FILE* p;
	printf("The command is: %s\n", command);
	p = popen(command, "r");
	if(p == NULL) {
		perror("Error on popen");
		exit(1);
	}

	char* result = (char*)malloc(sizeof(char)*(LEN+1));
	int length = fread(result, 1, LEN, p);
	if(length < 0) {
		perror("Error on fread");
		exit(1);
	}

	result[length] = 0;
	printf("The result is: %s\n and length is: %d\n", result, length);
	free(command);
	free(result);
	return 0;
}
