#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mtx1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx2 = PTHREAD_MUTEX_INITIALIZER;

int g;
int idx = 0;

void *f(void *a) {
        int i = *(int*)a;
 
	while(g>0) {
		if(g <= 0) {
			break;
		}
		if(idx == i) {
			if(g <= 0)
				break;
			pthread_mutex_lock(&mtx2);
			if(idx == 4)
				idx = 0;
			else
				idx ++;
			int nr = rand() % 10;
			printf("Thread %d decrements %d with %d and remains %d\n", i, g, nr, g-nr);
			pthread_mutex_lock(&mtx1);
			g -= nr;		
			pthread_mutex_unlock(&mtx1);
			pthread_mutex_unlock(&mtx2);
		}
	}       

	free(a);

        return NULL;
}
int main(int argc, char** arg) {
 	srandom(time(NULL));

        int i;

	printf("Enter g:\n");
	scanf("%d", &g);

        pthread_t t[5];
        for(i=0;i<5;i++) {
                int *v = (int*)malloc(sizeof(int));
                *v = i;
                if(pthread_create(&t[i], NULL, f, v) != 0) {
                        perror("Cannot create thread");
                        exit(1);
                }
        }

        for(i=0;i<5;i++)
                pthread_join(t[i], NULL);

        pthread_mutex_destroy(&mtx1);
	pthread_mutex_destroy(&mtx2);

        return 0;
}
