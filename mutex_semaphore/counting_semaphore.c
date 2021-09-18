#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int sum = 0;

sem_t sem;

void *counter(void *param)
{
	int k;
	for (k = 0; k < 100000; k++) {
		// entry section
		sem_wait(&sem);
		// critical section
		sum++;
		// exit section
		sem_post(&sem);
		// remainder section
	}
	pthread_exit(0);
}

int main()
{
	pthread_t tid[5];
	int i;

	sem_init(&sem, 0, 5);
	for (i = 0; i < 5; i++)
		pthread_create(&tid[i], NULL, counter, NULL);
	for (i = 0; i < 5; i++)
		pthread_join(tid[i], NULL);
	printf("sum = %d\n", sum);
}

/*
	코드를 실행했을 때 값이 50만이 안나오는 것은 정상적인 동작입니다.
	한개의 공유데이터를 5개의 쓰레드가 계속 접근하기때문에 race condition(경쟁 상태)이 발생하게
	되고 상호 배제가 이루어지지 않습니다.
*/