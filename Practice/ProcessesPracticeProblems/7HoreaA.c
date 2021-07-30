#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int shmid;
char* p;

void f(int sgn){
        p[0]='x';

        sleep(1);

        shmdt(p);
        shmctl(shmid, IPC_RMID, NULL);
        exit(0);
}

int main(){
        signal(SIGINT, f);
        shmid = shmget(2854, 1000*sizeof(char), IPC_CREAT | 0600);

        p = shmat(shmid, 0, 0);

        while(1){
                char* s = malloc(1000);
                scanf("%s", s);
                strcpy(p+1, s);
                free(s);
        }
        return 0;
}
