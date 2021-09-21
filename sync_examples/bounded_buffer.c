#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

#define BUFFER_SIZE 5

int buf[BUFFER_SIZE];

pthread_mutex_t mutex;
sem_t empty, full;

int in = 0;
int out = 0;

void insert_item(int item)
{
	sem_wait(&empty);
	pthread_mutex_lock(&mutex);
	
	buf[in] = item;
	in = (in + 1) % BUFFER_SIZE;
	printf("Producer : inserted $%d\n", item);
	
	pthread_mutex_unlock(&mutex);
	sem_post(&full);
}

void remove_item(int *item)
{
	sem_wait(&full);
	pthread_mutex_lock(&mutex);

	*item = buf[out];
	out = (out + 1) % BUFFER_SIZE;
	printf("Consumer : removed $%d\n", *item);

	pthread_mutex_unlock(&mutex);
	sem_post(&empty);
}

void *producer(void *param)
{
	int item;

	while (true)
	{
		usleep((1 + rand() % 5) * 100000);
		item = 1000 + rand() % 1000;
		insert_item(item);	// critical section
	}
}

void *consumer(void *param)
{
	int item;

	while (true)
	{
		usleep((1 + rand() % 5) * 100000);
		remove_item(&item);		// critical section
	}
}
int main(int argc, char **argv)
{
	int i;
	int numOfProducers = 1, numOfConsumers = 1;
	pthread_t tid;

	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty, 0, 5);
	sem_init(&full, 0, 0);
	srand(time(0));
	
	// create the Producer
	for (i = 0; i < numOfProducers; i++)
		pthread_create(&tid, NULL, producer, NULL);
	// create the Consumer
	for (i = 0; i < numOfConsumers; i++)
		pthread_create(&tid, NULL, consumer, NULL);
	sleep(10);
	return 0;
}