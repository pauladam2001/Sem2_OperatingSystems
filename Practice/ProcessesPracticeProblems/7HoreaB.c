#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int shmid;
char* p;

int main(){
        char v[] = "aeiouAEIOU";

        shmid = shmget(2854, 0, 0);
        p = shmat(shmid, 0, 0);

        char* d = malloc(1000);

        while(p[0] != 'x'){
                if(strcmp(d, p+1)!=0){
                        strcpy(d, p+1);
                        int i, j, sum=0;
                        for(i=0 ;i<strlen(d); i++){
                                for(j=0; j<10; j++){
                                        if(d[i] == v[j])
                                                sum++;
                                }
                        }
                        printf("B: %s contains %d vowels.\n", d, sum);
                }
        }
        shmdt(p);
        free(d);
        return 0;
}
