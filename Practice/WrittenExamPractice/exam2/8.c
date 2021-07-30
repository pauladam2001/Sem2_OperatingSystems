#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	char* s[3] = {"A", "B", "C"};
	int i;
	for(i=0;i<3;i++)
		execl("/bin/echo", "/bin/echo", s[i], NULL);
	return 0;
}
