#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define true 1
#define NUM_PHILS 5

enum {THINKING, HUNGRY, EATING} state[NUM_PHILS];

pthread_mutex_t mutex_lock;
pthread_cond_t cond_vars[NUM_PHILS];

void init()
{
	int i;
	for (i = 0; i < NUM_PHILS; i++)
	{
		state[i] = THINKING;
		pthread_cond_init(&cond_vars[i], NULL);
	}
	pthread_mutex_init(&mutex_lock, NULL);
	srand(time(0));
}

int leftOf(int i)
{
	return (i + NUM_PHILS - 1) % NUM_PHILS;
}

int rightOf(int i)
{
	return (i + 1) % NUM_PHILS;
}

void think(int id)
{
	printf("%d : Now, I'm thinking...\n", id);
	usleep((1 + rand() % 50) * 10000);
}

void eat(int id)
{
	printf("%d : Now, I'm eating...\n", id);
	usleep((1 + rand() % 50) * 10000);
}

void test(int i)
{
	// 만약 배고프고 근처 철학자가 먹고 있지 않다면 식사를 시작합니다.
	if (state[i] == HUNGRY && state[leftOf(i)] != EATING && state[rightOf(i)] != EATING)
	{
		state[i] = EATING;
		pthread_cond_signal(&cond_vars[i]);
	}
}

void pickup(int i)
{
	pthread_mutex_lock(&mutex_lock);

	state[i] = HUNGRY;
	test(i);
	while (state[i] != EATING)
		pthread_cond_wait(&cond_vars[i], &mutex_lock);
		
	pthread_mutex_unlock(&mutex_lock);
}

void putdown(int i)
{
	pthread_mutex_lock(&mutex_lock);

	state[i] = THINKING;
	test(leftOf(i));
	test(rightOf(i));

	pthread_mutex_unlock(&mutex_lock);
}

void *philosopher(void *param)
{
	int id = *((int *)param);
	while (true) {
		think(id);
		pickup(id);
		eat(id);
		putdown(id);
	}
}

int main()
{
	int i;
	pthread_t tid;

	init();
	for (i = 0; i < NUM_PHILS; i++)
		pthread_create(&tid, NULL, philosopher, (void *)&i);
	for (i = 0; i < NUM_PHILS; i++)
		pthread_join(tid, NULL);
	return (0);
}