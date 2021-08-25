#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main()
{
	const int		SIZE = 4096;		// shared memory의 크기
	const char		*name = "OS";		// shared memory의 이름
	const char		*message_0 = "Hello, ";
	const char		*message_1 = "Shared Memory!\n";

	int				shm_fd;				// shared memory의 file descriptor
	char			*ptr;				// shared memory의 포인터
	
	/* shared memory 객체 생성*/
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	/* shared memory 크기 지정 */
	ftruncate(shm_fd, SIZE);
	/* shared memory object의 메모리 영역할당 */
	ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

	/* shared memory에 내용작성*/
	sprintf(ptr, "%s", message_0);
	ptr += strlen(message_0);		//message_0 만큼 ptr 위치 옮김
	sprintf(ptr, "%s", message_1);
	ptr += strlen(message_1);		//message_1 만큼 ptr 위치 옮김

	return (0);
}