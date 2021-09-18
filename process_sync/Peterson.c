#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

/*
	프로그램의 흐름
	1. flag[0] = true로 설정하여 0번 스레드가 임계 영역에 진입하고 싶다고 표시합니다.
	2. 이때 turn = 1을 주며 1번 프로세스가 먼저 들어가라고 양보해줍니다.
	3. 만약 이때 컨텍스트 스위칭이 되지 않았다면 while문 안에 갖히게 됩니다.
	4. 1번 프로세스가 모든 작업을 끝내면 trun = 0, flag[1] = false가 되므로 0번 프로세스가 다시 돌 수 있습니다.
*/

int cnt;
bool flag[2] = {false, };
int turn = 0;

void *prod() {
	for (int i = 0; i < 10000; i++)
	{
		// entry section
		flag[0] = true;
		turn = 1;
		while (flag[1] == true && turn == 1) {}

		// critical section
		cnt++;
		// exit section
		flag[0] = false;
		// remainder section
	}
	pthread_exit(0);
}

void *cons() {
	for (int i = 0; i < 10000; i++)
	{
		// entry section
		flag[1] = true;
		turn = 0;
		while (flag[0] == true && turn == 0) {}
		
		// critical section
		cnt++;
		// exit section
		flag[1] = false;
		// remainder section
	}
	pthread_exit(0);
}

int main()
{
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, prod, NULL);
	pthread_create(&tid2, NULL, cons, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	printf("%d\n", cnt);
}

