#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_rwlock_t rwl;
int g;

void *producer(void *a) {
        int id = *(int*)a;
        printf("Producer %d started!\n", id);

        while(1) {
                sleep(2);
                int x = rand() % 101;
                printf("Producer %d writing %d value!\n", id, x);
                pthread_rwlock_wrlock(&rwl);
                g = x;
                pthread_rwlock_unlock(&rwl);
        }

        free(a);
        return NULL;
}

void *consumer(void *a) {
        int id = *(int*)a;
        printf("Consumer %d started!\n", id);

        while(1) {
                sleep(1);
                pthread_rwlock_rdlock(&rwl);
                printf("Consumer %d reading %d value!\n", id, g);
                pthread_rwlock_unlock(&rwl);
        }

        free(a);
        return NULL;
}

int main() {
        pthread_t t[5];
        int i, *a;

        pthread_rwlock_init(&rwl, NULL);

        for(i=0;i<2;i++) {
                a = (int*)malloc(sizeof(int));
                *a = i;
                if(pthread_create(&t[i], NULL, producer, a) != 0) {
                        perror("Cannot create thread");
                        exit(1);
                }
        }
        for(i=2;i<5;i++) {
                a = (int*)malloc(sizeof(int));
                *a = i;
               if(pthread_create(&t[i], NULL, consumer, a) != 0) {
                        perror("Cannot create thread");
                        exit(1);
                }
        }

        for(i=0;i<5;i++)
                pthread_join(t[i], NULL);

        pthread_rwlock_destroy(&rwl);

        return 0;
}

