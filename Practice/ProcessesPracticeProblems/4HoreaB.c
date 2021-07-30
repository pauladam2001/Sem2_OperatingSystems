#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

int main(int argc, char** argv) {
        int i, a2b, b2a;

        a2b = open("a2b", O_RDONLY);
        b2a = open("b2a", O_WRONLY);

        if(a2b<0 || b2a<0) {
                perror("Error on FIFO B");
                exit(1);
        }

        while(1) {
                int length = 0;
                if(read(a2b, &length, sizeof(int)) < 0) {
                        perror("Error on read len B");
                        exit(1);
                }
		if(length > 0) {
			char* buffer = (char*)malloc(sizeof(char)*(length+1));
                	if(read(a2b, buffer, length*sizeof(char)) < 0) {
                        	perror("Error on read arg B");
                        	exit(1);
                	}
			buffer[length] = 0;
			for(i=0;i<strlen(buffer);i++) {
				if(buffer[i] >= 'a' && buffer[i] <= 'z')
					buffer[i] = toupper(buffer[i]);
			}
			if(write(b2a, &length, sizeof(int)) < 0) {
				perror("Error on send len B");
				exit(1);
			}
			if(write(b2a, buffer, length*sizeof(char)) < 0) {
				perror("Error on send arg B");
				exit(1);
			}
			free(buffer);				
		}
		else
		    break;
        }

        close(a2b);
        close(b2a);

        return 0;
}


