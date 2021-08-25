# IPC
## Share Memory : POSIX Shared Memory
### POSIX : UNIX에 이식되는 운영체제 인터페이스
- 메모리 저장 파일을 이용하여 구성되어있습니다.
- 공유 메모리 영역을 파일과 연결합니다.
### Producer
1. Shared-Memory 객체를 생성합니다.
	```
	fd = shm_open(name, O_CREAT | ORDWR, 0666)
	```
2. Shared-Memory 객체의 크기를 지정합니다.
	```
	ftruncate(fd, 4096)
	```
3. memory-mapped file에 내용을 작성합니다.
	```
	mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)
	```
### Consumer
1. Shared-Memory 객체를 생성합니다.
	```
	fd = shm_open(name, O_CREAT | ORDWR, 0666)
	```
2. memory-mapped file의 내용을 읽어옵니다.
	```
	ptr = (char *)mmap(0, SIZE, PROT_READ , MAP_SHARED, shm_fd, 0);
	```
3. 읽어온 Shared memory를 삭제합니다.
	```
	shm_unlink(name);
	```
### Share Memory 방식의 문제
- 개발자가 직접 할당해주고, write하고 read하는 것을 전부 관리해야 합니다.
## Message Passing : Pipes
### Pipes : UNIX 시스템의 초기 IPC 메커니즘 중 하나입니다.
