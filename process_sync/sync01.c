#include <stdio.h>
#include <pthread.h>

/*
*** 다음프로그램의 출력 값은?
*/

int sum;

void *run1(void *param)
{
	int i;
	
	for (i = 0; i < 10000; i++)
		sum++;
	pthread_exit(0);
}

void *run2(void *param)
{
	int i;
	
	for (i = 0; i < 10000; i++)
		sum--;
	pthread_exit(0);
}

int main(void)
{
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, run1, NULL);
	pthread_create(&tid2, NULL, run2, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	printf("%d\n", sum);
}