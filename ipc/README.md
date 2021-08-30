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
- 두 프로세스가 생산자와 소비자 방식으로 소통하도록 허용합니다.
	- 생산자가 쓰기전용 파이프 한쪽을 사용하고 소비자가 읽기전용 파이프 한쪽을 사용합니다.
- 한방향으로만 통신이 가능합니다.
- 양 방향 통신을 하고 싶으면 두개의 파이프를 사용해서 할 수 있습니다.
<img width="461" alt="op" src="https://user-images.githubusercontent.com/41960243/130849339-031213b0-492e-4b3a-bb7b-99c1339a8e11.PNG">

> unix에서의 구현
- 파이프는 함수를 사용해서 구현할 수 있습니다.
	```
	pipe(int fd[])
	```
	fd[0] : 읽기 전용 파이프
	fd[1] : 쓰기 전용 파이프

### Named Pipes
- 상위 프로세스 - 하위 프로세스 관계 없이 액세스할 수 있습니다.
### 클라이언트 - 서버 시스템에서 다른 두가지 전략
> sockets
- 통신을 위한 양 끝점을 의미합니다.
> RPCs (Remote Procedure Calls)
- 네트워크 시스템의 프로세스 간 프로시저 호출을 추상화합니다.
### 소켓 (Socket)
- 포트 번호와 연결된 IP주소로 식별됩니다.
<img width="461" alt="op" src="https://s3.us-west-2.amazonaws.com/secure.notion-static.com/4353c02d-e3cf-4df0-8e0b-693b126eb3c4/Untitled.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAT73L2G45O3KS52Y5%2F20210830%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20210830T070405Z&X-Amz-Expires=86400&X-Amz-Signature=ac1853e84dd183e0624219453ef4446c270d4ff819306ec8d69a95ed6d523f99&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22Untitled.png%22">

> Java에서 소켓 구현
- 소켓에 대한 훨씬 쉬운 인터페이스 및 세 가지 유형의 소켓을 제공합니다.
	- Socket class : connection-oriented (TCP)
	- DatagramSocket class : connectionless (UDP)
	- MulticastSocket class : multiple recipients
### RPC (Remote Procedure Call)
- 가장 일반적인 형태의 원격 서비스 중에 하나입니다.
- 프로시저 호출 메커니즘을 추상화하는 방법으로 설계되었습니다.
	- 네트워크 연결이 있는 시스템 간에 사용합니다.
- 클라이언트가 원격 호스트에서 프로시저를 호출합니다.
	- 로컬에서 프로시저를 호출할 수 있기 때문입니다.
> RPC 시스템
- 클라이언트 측에서 stub을 제공하여 통신이 이루어질 수 있는 세부 정보를 숨깁니다.
- 클라이언트 측 스텁이 서버를 찾고 매개변수를 마샬링합니다.
- 서버측 스텁이 이 메시지를 수신하고, 마샬링된 매개변수의 압축을 풀고, 서버에서 절차를 수행합니다.