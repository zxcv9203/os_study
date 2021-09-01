# thread
- 지금까지 공부한 내용의 프로세스는 하나의 제어 스레드를 가진 실행 프로그램이었습니다.
- 그러나 프로세스는 여러 개의 제어 스레드를 가질 수 있습니다.
## thread 란
- 가벼운 프로세스입니다.
- CPU를 활용하는 기본 단위입니다.
- thread ID, 프로그램 카운터, 레지스터 세트 및 스택으로 구성됩니다.

	<img src="https://s3.us-west-2.amazonaws.com/secure.notion-static.com/42bbd9f8-5c97-496d-be23-8397ad894eef/Untitled.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAT73L2G45O3KS52Y5%2F20210901%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20210901T065618Z&X-Amz-Expires=86400&X-Amz-Signature=3aa4fec26ed6848713ff6c21515a5cd19cc2850bc84a67f5373111a8d35e091c&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22Untitled.png%22" width = "50%" height = "50%"></img>
### 멀티 쓰레딩의 사용예시
- 클라이언트-서버 시스템의 경우 다음 그림과 같습니다.(ex. webserver)

	<img src="https://s3.us-west-2.amazonaws.com/secure.notion-static.com/dbd46cac-e368-4d21-b05c-40880bbfe937/Untitled.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAT73L2G45O3KS52Y5%2F20210901%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20210901T072351Z&X-Amz-Expires=86400&X-Amz-Signature=b00744745348891d9342d4d84cc64aa7d9d53401668c91b6818805a5003dcb79&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22Untitled.png%22" width = "50%" height = "50%"></img>
### 멀티 쓰레드 프로그래밍의 장점
- 응답성 : 프로그램의 일부분(thread)이 중단되거나 긴 작업을 수행하더라도 프로그램 수행이 계속 되어 사용자에 대한 응답성이 증가합니다.
예를들어, 멀티 쓰레드가 적용된 웹 브라우저 프로그램에서 하나의 스레드가 용량이 큰 파일을 로드하는 동안 다른 스레드에서 사용자와 상호작용을 할 수 있습니다.
- 경제성 : 프로세스 내 자원들과 메모리를 공유하기 때문에 메모리 공간과 시스템 자원 소모가 줄어듭니다. 스레드 간 통신이 필요한 경우에도 쉽게 데이터를 주고 받을 수 있으며, 프로세스의 context switching과 달리 스레드 간의 context switching은 캐시 메모리를 비울 필요가 없기 때문에 더 빠릅니다.
- 확장성 : 다중 CPU 구조에서는 각각의 스레드가 다른 프로세서에서 병렬로 수행될 수 있으므로 확장성이 증가합니다.
### java에서 thread 구현
- 자바 프로그램에서 thread는 프로그램 실행의 기본 모델입니다.
- 자바는 thread의 생성 및 관리를 위한 많은 기능을 제공합니다.
### java에서 스레드를 명시적으로 만드는 세가지 방법
1. thred class에서 상속
	- thread class에서 파생된 새 class를 만듭니다.
	- public void run() 메서드를 재정의(override)합니다.
		```
		class MyThread1 extends Thread {
			public void run() {
				try {
					while (true) {
						System.out.println("Hello, Thread");
						Thread.sleep(500);
					}
				}
				catch (InterruptedException ie) {
					System.out.println("I'm interrupted");
				}
			}
		}
		public class ThreadExample1 {
			public static final void main(string[] args) {
				MyThread1 thread = new MyThread1();
				thread.start();
				System.out.println("Hello, My Child");
			}
		}
		```
2. 실행 가능한 인터페이스 구현
	- 실행 가능한 인터페이스를 구현하는 새 class를 정의합니다.
	- public void run()메서드를 재정의합니다.
		```
		class MyThread2 implements Runnable {
			public void run() {
				try {
					while (true) {
						System.out.println("Hello, Runnable");
						Thread.sleep(500);
					}
				}
				catch (InterruptedException ie) {
					System.out.println("I'm interrupted");
				}
			}
		}
		```
3. 람다 표현식 사용(java 1.8 버전 이상)
	- 새로운 클래스를 정의하는 대신, 실행가능한 람다식을 대신 사용합니다.
		```
		public class ThreadExample3 {
			public static final void main(String[] args) {
				Runnable task = () -> {
					try {
						while (true) {
							System.out.println("Hello, Lambda Runnable!");
							Thread.sleep(500);
						}
					}
					catch (InterruptException ie) {
						System.out.println("I'm interrupted");
					}
				};
				Thread thread = new Thread(task);
				thread.start();
				System.out.println("Hello, My Lambda Child!");
			}
		}
		```
### 부모 thread 대기
- fork()를 이용해서 멀티 프로세스를 만들때 부모 프로세스를 wait()을 이용해서 대기시켰었습니다.
thread에서도 이와 같이 부모 thread를 대기시킬 수 있는데 join()을 사용합니다.
	```
	public class ThreadExample4 {
		public static final void main(String[] args) {
			Runnable task = () -> {
				for (int i = 0; i < 5; i++) {
					System.out.println("Hello, Lambda Runnable!");
				}
			};
			Thread thread = new Thread(task);
			thread.start();
			try {
				thread.join();
			}
			catch (InterruptedException ie) {
				System.out.println("Parent thread is interrupted");
			}
			System.out.println("Hello, My Joined Child");
		}
	}
	```
### thread 종료
- interrupt()를 사용해서 종료할 수 있습니다.
	```
	public class ThreadExample5 {
		public static final void main(String[] args) throws InterruptedException {
			Runnable task = () -> {
				try {
					while (true) {
						System.out.println("Hello, Lambda Runnable!");
						Thread.sleep(100);
					}
				}
				catch (InterruptedException ie) {
					System.out.println("I'm interrupted");
				}
			};
			Thread thread = new Thread(task);
			thread.start();
			Thread.sleep(500);
			thread.interrupt();
			System.out.println("Hello, My Interrupted Child!");
		}
	}
	```
## 멀티코어 시스템에서의 멀티 쓰레딩
- 멀티코어를 보다 효율적으로 사용하여 동시성을 개선할 수 있습니다.
- 하나의 어플리케이션과 4개의 쓰레드를 고려해봅시다.
	- 싱글 코어 : thread는 시간이 지나면서 인터리빙 됩니다.(사이 사이에 쓰레드를 끼워놓는다고 생각하면 됩니다.)

		<img src = "https://s3.us-west-2.amazonaws.com/secure.notion-static.com/219423f5-1a46-4ac7-abfd-21c58699f844/Untitled.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAT73L2G45O3KS52Y5%2F20210901%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20210901T084049Z&X-Amz-Expires=86400&X-Amz-Signature=6313b54768313955e1f722a0e34dcbb5bcb44c6066e51eaffb28a7ad730ae071&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22Untitled.png%22" width = "50%" height = "50%">
	- 멀티 코어 : 일부 thread는 병렬로 실행될 수 있습니다.

		<img src = "https://s3.us-west-2.amazonaws.com/secure.notion-static.com/9a23d815-b456-4fcc-89dc-469d6d2f23b0/Untitled.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAT73L2G45O3KS52Y5%2F20210901%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20210901T084306Z&X-Amz-Expires=86400&X-Amz-Signature=004091d535630d15e76ac144fc606eea2fa5cf4e09f7d8f0c1b6a5af97387958&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22Untitled.png%22" width = "50%" height = "50%">
### 멀티코어 시스템에서 프로그래밍 문제
- 태스크 식별 : 독립된 병행 가능 태스크로 나눌 수 있는 영역을 찾는 작업이 필요합니다.
- 균형 : 병렬로 실행될 수 있는 태스크를 전체 작업에 균등한 처리량을 가지도록 태스크를 나누어야 합니다. 
- 데이터 분리 : 태스크가 접근하고 조작하는 데이터 또한 개별 코어에서 사용할 수 있도록 나뉘어져야 합니다.
- 데이터 종속성 : 태스크가 접근하는 데이터는 둘 이상의 태스크 사이에 종속성이 없는지 검토해야 합니다.
- 테스트와 디버깅 : 프로그램이 다중 코어에서 병렬로 실행될 때 다양한 실행 경로가 존재할 수 있으므로 시험하고 디버깅 해야합니다.
### 병렬처리 유형
- 데이터 병렬 실행
	
	<img src = "https://s3.us-west-2.amazonaws.com/secure.notion-static.com/0f99858b-ea35-44c3-87f4-6ab850ac77d8/Untitled.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAT73L2G45O3KS52Y5%2F20210901%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20210901T085615Z&X-Amz-Expires=86400&X-Amz-Signature=dd6360d38c786c3db6e921b0ab2dd359a8d4145f777b0386834a47a4f49c0d54&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22Untitled.png%22" width = "50%" height = "50%">
- 태스크 병렬 실행

	<img src = "https://s3.us-west-2.amazonaws.com/secure.notion-static.com/fae7102a-3f2e-4400-b4fc-2edf9ad1c0ed/Untitled.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAT73L2G45O3KS52Y5%2F20210901%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20210901T085744Z&X-Amz-Expires=86400&X-Amz-Signature=0f36456e19d97dbfbc2b9a24ed21611efe7daa73bec8c8950744668dacc1e816&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22Untitled.png%22" width = "50%" height = "50%">