#include <stdio.h>
#include <unistd.h>

int main()
{
	// fork를 호출할 때마다 현재 프로세스에서
	// 하나씩 자식프로세스를 만듭니다.
	fork(); // 프로세스 개수 : 2
	fork(); // 프로세스 개수 : 4
	fork(); // 프로세스 개수 : 8
	printf("Hello, fork!\n");
	return (0);
}