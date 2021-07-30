//Assume a cigarette requires three ingredients to make and smoke: tobacco, paper, and matches. There are three smokers around a table, each of whom has an infinite supply of one of the three ingredients — one smoker has an infinite supply of tobacco, another has paper, and the third has matches.

//There is also a non-smoking agent who enables the smokers to make their cigarettes by arbitrarily (non-deterministically) selecting two of the supplies to place on the table. The smoker who has the third supply should remove the two items from the table, using them (along with their own supply) to make a cigarette, which they smoke for a while. Once the smoker has finished his cigarette, the agent places two new random items on the table. This process continues forever.

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

pthread_cond_t ready, finished;
int paper = 0, tobacco = 0, matches = 0;
pthread_mutex_t mutex;

void *first_smoker(void *a) {		// has matches
	pthread_mutex_lock(&mutex);
	while(1) {
		while(paper == 0 || tobacco == 0)
			pthread_cond_wait(&ready, &mutex);
		printf("First smoker got paper, tobacco and is smoking\n");
		sleep(1);
		printf("First smoker finished \n");
		tobacco = 0;
		paper = 0;
		pthread_cond_signal(&finished);
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void *second_smoker(void *a) {		// has tobacco
        pthread_mutex_lock(&mutex);
        while(1) {
                while(paper == 0 || matches == 0)
                        pthread_cond_wait(&ready, &mutex);
                printf("Second smoker got paper, matches and is smoking\n");
                sleep(1);
                printf("Second smoker finished \n");
                paper = 0;
		matches = 0;
                pthread_cond_signal(&finished);
        }
        pthread_mutex_unlock(&mutex);
        return NULL;
}

void *third_smoker(void *a) {		// has paper
        pthread_mutex_lock(&mutex);
        while(1) {
                while(tobacco == 0 || matches == 0)
                        pthread_cond_wait(&ready, &mutex);
                printf("Third smoker got tobacco, matches and is smoking\n");
                sleep(1);
                printf("Third smoker finished \n");
                tobacco = 0;
                matches = 0;
                pthread_cond_signal(&finished);
        }
        pthread_mutex_unlock(&mutex);
        return NULL;
}

void *the_agent(void *a) {
	pthread_mutex_lock(&mutex);
	while(1) {
		while(paper == 1 || tobacco == 1 || matches == 1)
			pthread_cond_wait(&finished, &mutex);
		int nr = random()%3 + 1;
		if(nr == 1) {
			printf("The agent selected paper and tobacco\n");
			paper = 1;
			tobacco = 1;
			pthread_cond_broadcast(&ready);
		}
		if(nr == 2) {
			printf("The agent selected paper and matches\n");
                        paper = 1;
                        matches = 1;
                        pthread_cond_broadcast(&ready);
		}
		if(nr == 3) {
			printf("The agent selected tobacco and matches\n");
                        tobacco = 1;
			matches = 1;
                        pthread_cond_broadcast(&ready);
		}	
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main(int argc, char** argv) {
	pthread_t smoker1, smoker2, smoker3, agent;

	pthread_cond_init(&ready, NULL);
	pthread_cond_init(&finished, NULL);
	pthread_mutex_init(&mutex, NULL);

	pthread_create(&smoker1, NULL, first_smoker, NULL);
	pthread_create(&smoker2, NULL, second_smoker, NULL);
	pthread_create(&smoker3, NULL, third_smoker, NULL);
	pthread_create(&agent, NULL, the_agent, NULL);

	pthread_join(smoker1, NULL);
	pthread_join(smoker2, NULL);
	pthread_join(smoker3, NULL);
	pthread_join(agent, NULL);

	pthread_cond_destroy(&ready);
	pthread_cond_destroy(&finished);
	pthread_mutex_destroy(&mutex);

	return 0;
}
