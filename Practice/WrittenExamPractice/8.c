#include <stdio.h>
#include <unistd.h>

int main() {
	int i;
	char* s[3] = {"A", "B", "C"};
	for(i=0;i<3;i++) {
		if(fork() != 0)
			execl("/bin/echo", "/bin/echo", s[i], NULL);
	}
	return 0;
}
