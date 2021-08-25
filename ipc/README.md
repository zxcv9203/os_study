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
- Pipe는 두 프로세스가 통신할 수 있도록 하는 통로의 역할을 합니다.
### Pipe를 구현할 때 발생하는 4가지 고려사항
- 파이프가 단방향 통신입니까? 양방향 통신입니까?
- 양방향 통신의 경우 반이중 통신(Half-Duplex) 입니까? 전이중 통신(Full-Duplex)입니까?
- 서로 통신하는 프로세스 간에 관계가 있어야 합니까?
ex) 여기서 관계는 부모프로세스, 자식프로세스 간의 통신같이 두 프로세스가 연관성이 있는지를 의미합니다.
- 파이프가 네트워크를 통해서도 통신이 가능합니까? -> 네트워크를 통해서 사용하는 파이프를 소켓이라고 부릅니다.
### Ordinary Pipes
- 생성한 프로세스 외부에서 액세스할 수 없습니다.
- 일반적으로 상위 프로세스는 파이프를 만들고 파이프를 사용하여 만든 하위프로세스와 통신합니다.
<img width="461" alt="op" src="https://user-images.githubusercontent.com/41960243/130849339-031213b0-492e-4b3a-bb7b-99c1339a8e11.PNG">
### Named Pipes
- 상위 프로세스 - 하위 프로세스 관계 없이 액세스할 수 있습니다.
