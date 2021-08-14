#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main()
{
	pid_t pid, fpid;
	fpid = getpid();
	printf("프로그램의 pid : %d\n", fpid);
	pid = fork();

	if (pid == 0)
	{
		fpid = getpid();
		printf("자식 프로세스\n");
		printf("자신의 pid : %d\n부모의 pid : %d\n", pid, fpid);
	}
	else if (pid > 0)
	{
		wait(NULL);
		fpid = getpid();
		printf("부모 프로세스\n");
		printf("자신의 pid : %d\n부모의 pid : %d\n", pid, fpid);
	}
}