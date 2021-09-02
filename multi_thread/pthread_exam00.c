#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* 쓰레드끼리 데이터를 공간하기 위해 사용할 변수 */
int sum;

/* 쓰레드에서 호출할 함수 */
void *runner(void *param);

int main(int argc, char *argv[])
{
	pthread_t tid;					// thread 식별자
	pthread_attr_t attr;			// thread 특성

	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, runner, argv[1]);
	pthread_join(tid, NULL);
	printf("sum = %d\n", sum);
}

void *runner(void *param)
{
	int i, upper = atoi(param);
	sum = 0;
	for (i = 1; i <= upper; i++)
		sum += i;
	pthread_exit(0);
}