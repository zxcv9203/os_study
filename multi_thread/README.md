# 멀티 쓰레딩 모델
## 쓰레드의 두가지 타입
### 유저 쓰레드 와 커널 쓰레드
> 유저 쓰레드
- 유저 쓰레드는 커널 위에서 동작하며 커널의 지원 없이 관리됩니다.
- 일반적으로 사용자의 라이브러리를 통해 구현되며, 라이브러리는 쓰레드의 생성 및 스케줄링 등에 관한 관리 기능을 제공합니다.
- 동일한 메모리 영역에서 쓰레드가 생성 및 관리되므로 속도가 빠른 장점이 있습니다.
- 여러개의 사용자 쓰레드 중 하나의 쓰레드가 시스템 호출 등으로 중단되면 나머지 모든 쓰레드도 중단되는 단점이 있습니다. -> 이는 커널이 프로세스 내부의 쓰레드를 인식하지 못하여 해당 프로세스를 대기 상태로 전환시키기 때문입니다.
> 커널 쓰레드
- 커널 쓰레드는 운영 체제에서 직접 지원하고 관리됩니다.
- 운영체제가 지원하는 쓰레드 기능으로 구현되며, 커널이 쓰레드의 생성 및 스케줄링 등을 관리합니다.
- 쓰레드가 시스템 호출 등으로 중단되도라도, 커널은 프로세스 내의 다른 쓰레드를 중단 시키지 않고 계속 실행시켜 줍니다.
- 프로세스의 쓰레드들을 몇몇 프로세서에 한번에 디스패치할 수 있기 때문에 멀티 프로세서 환경에서 매우 빠르게 동작합니다.
- 사용자가 프로그래밍할 때 구현하기 어렵고 자원을 더 많이 소모하는 경향이 있습니다.
- 사용자에서 커널로의 전환이 빈번하게 이뤄져 성능저하가 발생합니다.

<img src = "https://s3.us-west-2.amazonaws.com/secure.notion-static.com/192bf8bd-4f71-48c4-9db3-ce78693581e5/Untitled.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAT73L2G45O3KS52Y5%2F20210902%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20210902T094336Z&X-Amz-Expires=86400&X-Amz-Signature=daca32553fcba3e95e9823ff6c32a95ec460de00c80dd1b7c415c05f14b31364&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22Untitled.png%22" width = "50%" height = "50%">

## 유저 쓰레드와 커널 쓰레드 간의 세가지 모델(유저 쓰레드 : 커널 쓰레드)
1. Many-to-one Model(다대일 모델)
	여러개의 유저 쓰레드들이 하나의 커널 쓰레드(프로세스)로 매핑되는 방식으로 사용자 수준에서 쓰레드 관리가 이루어집니다.

	주로, 커널 쓰레드가 지원하지 않는 시스템에서 사용하며 한번에 하나의 쓰레드만이 커널에 접근할 수 있다는 단점이 있습니다.
	
	하나의 쓰레드가 커널에 시스템 호출을 하면 나머지 쓰레드들은 대기해야 하기 때문에 진정한 의미의 동시성을 지원하지 못합니다.

	즉, 여러 개의 쓰레드가 동시에 시스템 호출을 사용할 수 없습니다.

	또한, 커널 입장에서는 프로세스 내부의 유저 쓰레드들을 인식할 수 없고 하나의 프로세스로만 보이기 때문에 다중처리 환경이라도 여러 개의 프로세서에 분산하여 수행할 수 없습니다.

	<img src = "https://s3.us-west-2.amazonaws.com/secure.notion-static.com/5a4deca7-287b-41ca-9e3c-7acce89df948/Untitled.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAT73L2G45O3KS52Y5%2F20210902%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20210902T094754Z&X-Amz-Expires=86400&X-Amz-Signature=4e72f21582ffdf21c01d6b055bcf3d38be9de69742a2e55df32ab40ea658e22b&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22Untitled.png%22" width = "50%" height = "50%">
2. One-to-One Model(일대일 모델)
	유저 쓰레드들을 하나의 커널 쓰레드로 매핑 시키는 방식입니다.

	유저 쓰레드가 생성되면 그에 따른 커널 쓰레드가 생성됩니다.

	Many-to-one Model(다대일 모델)에서 시스템 호출 시 다른 쓰레드들이 중단되는 문제를 해결할 수 있으며 여러 개의 쓰레드를 다중처리기에 분산하여 동시에 수행할 수 있는 장점이 있습니다.

	그러나 커널 쓰레드도 한정된 자원을 사용하므로 무한정 생성할 수는 없기 때문에 쓰레드를 생성할 때 그 개수를 염두에 두어야 합니다.

	<img src = "https://s3.us-west-2.amazonaws.com/secure.notion-static.com/b4cddd01-23bc-4d03-93f4-815fc80645b0/Untitled.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAT73L2G45O3KS52Y5%2F20210902%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20210902T103041Z&X-Amz-Expires=86400&X-Amz-Signature=56cfc3b0f8aeb52c6a69a2d6e601a924c7f79b4467e0f7625b7f60b716c3e575&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22Untitled.png%22" width = "50%" height = "50%">
	
3. Many-to-Many Model(다대다 모델)
	여러 개의 유저 쓰레드들 여러 개의 커널 쓰레드로 매핑시키는 모델입니다.

	다대일 방식과 일대일 방식의 문제점을 해결하기 위해 고안되었습니다.

	커널 쓰레드는 생성된 사용자 쓰레드와 같은 수 또는 그 이하로 생성됩니다.

	커널이 사용자 쓰레드와 커널 쓰레드의 매핑을 적절하게 조절합니다.

	<img src = "https://s3.us-west-2.amazonaws.com/secure.notion-static.com/85e7b5f2-36fa-43b9-95c0-2f02db52f6ea/Untitled.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAT73L2G45O3KS52Y5%2F20210902%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20210902T094935Z&X-Amz-Expires=86400&X-Amz-Signature=681a2bfca2b02874c5281fb5f049410dd4eec00b7e96a13d93db50f0122c9263&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22Untitled.png%22" width = "50%" height = "50%">

## 쓰레드 라이브러리
쓰레드 라이브러리는 쓰레드를 생성하고 관리하기 API를 제공합니다.

### 자주 사용되는 3개의 라이브러리

- POSIX Pthreads 

	POSIX 표준 thread의 확장판이며 커널 수준의 라이브러리입니다.

	UNIX 계열과 Linux System, Mac OS 에서는 Pthreads로 구현됩니다.

- Windows thread
	
	Windows System에서 사용하는 커널 수준으로 라이브러리입니다.

- Java thread

	JVM(Java Virtual Machine)에서 실행되므로 호스트 시스템에서 사용 가능한 thread 라이브러리를 이용하여 구현됩니다.

### Pthreads

- POSIX 표준을 참조합니다. (IEEE 1003.1c)
- 구현이 아니라 쓰레드 동작에 대한 규격일 뿐입니다.

## Implicit Threading

- 멀티 코어 시스템에서 멀티 쓰레딩을 하는 애플리케이션의 설계는 애플리케이션 개발자가 설계하고 구현하는 것은 매우 어렵습니다.
- 그래서 컴파일러와 런타임 라이브러리에게 해당 역할을 맡깁니다.

### Implicit Threading을 위한 4가지 방법

> Thread Pool
- 작업을 기다리는 풀에 여러 개의 쓰레드를 만듭니다.
> Fork & join
- 명시적인 쓰레딩 방법이지만 Implicit Threading(암묵적인 쓰레딩)에도 적합한 후보입니다.