#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main()
{
	char write_msg[BUFFER_SIZE] = "Greetings";
	char read_msg[BUFFER_SIZE];
	int fd[2];
	pid_t pid;

	/* pipe 생성 */
	pipe(fd);
	
	pid = fork(); // fork로 새로운 프로세스 생성

	if (pid > 0) { // 부모 프로세스
		close(fd[READ_END]);
		/* pipe로 전달할 데이터를 쓰기 */
		write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);
		close(fd[WRITE_END]);
	}
	else if (pid == 0) { // 자식 프로세스
		close(fd[WRITE_END]);
		/* pipe로 전달된 데이터 읽어오기 */
		read(fd[READ_END], read_msg, BUFFER_SIZE);
		printf("read %s\n", read_msg);
		close(fd[READ_END]);
	}
	return (0);
}