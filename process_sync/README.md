# 프로세스 동기화
- 서로 데이터를 주고 받는 프로세스 사이에서 실행 순서 규칙을 정하여 공유되는 자원의 일관성을 보장할때 사용됩니다.

## 간단한 동기화의 필요성을 알려주는 예제

``` c
#include <stdio.h>
#include <pthread.h>

/*
*** 다음프로그램의 출력 값은?
*/

int sum;

void *run1(void *param)
{
	int i;
	
	for (i = 0; i < 10000; i++)
		sum++;
	pthread_exit(0);
}

void *run2(void *param)
{
	int i;
	
	for (i = 0; i < 10000; i++)
		sum--;
	pthread_exit(0);
}

int main(void)
{
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, run1, NULL);
	pthread_create(&tid2, NULL, run2, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	printf("%d\n", sum);
}
```
위의 예제의 출력값은 무엇일까요? 🤔

천천히 생각해보면 0으로 초기화 되어있는 sum을 10000증가 시켰다가 다시 10000만큼 감소시키때문에 Printf로 출력해보면 0이 나올 것 같습니다.

하지만 실제로 실행시켜보면 0이 나올때도 있지만 예상하지 못한 숫자들이 튀어나오기도 합니다.

그 이유는 대체 무엇일까요?

실제로 `count++` 과 `count--`의 동작은 다음과 같습니다.

1. 레지스터에 count 변수의 값을 가져옵니다.
2. 레지스터에 연산을 실시합니다.
3. count 변수에 레지스터를 연산한 값을 리턴합니다.

만약에 연산을 실시한 후 값을 리턴을 해야하는데 리턴하기 전에 context switch가 일어난다면 어떻게 될까요?

그 경우에 다른 스레드에서 연산한 결과가 사라져버리는 상황이 발생할 수 있습니다.

예를 들어, 현재 count가 3이라고 했을 때 레지스터에 count 값을 가져오고 레지스터에 연산을 실시해서 count가 4로 변경되었다고 합시다.

그런데 이 상황에서 context switch가 일어나서 다른 스레드에서 count의 값 3에서 2로 뺀 후 리턴까지 완료하고 다시 값을 리턴해 주고 context switch가 일어났습니다.

그때 레지스터에 저장되어있던 4라는 값이 반환이 되면서 count는 2에서 4로 변경됩니다.

이런 상황이 발생하면 값이 항상 정확하다고 보장할 수 없습니다.

위와 같은 상황을 `경쟁상황(Race Condition)`이라고 부릅니다.

# 경쟁상황(Race Condition)
- 여러 프로세스(또는 스레드)가 공유 자원에 동시에 접근할 때, 공유 자원에 대한 접근 순서에 따라 실행 결과가 달라질 수 있는 상황을 의미합니다.

## Race Condition을 해결할 수 있는 방법
- 한 번에 하나의 프로세스만 공유 데이터에 접근하게 하도록 합니다.(임계 영역 생성)

# 임계 영역(Critical Section)
- 여러 프로세스(또는 스레드)가 자원을 공유하는 상황에서, 하나의 프로세스(스레드)만 접근할 수 있도록 제한해둔 코드 영역

임계영역을 만들면 하나의 프로세스(스레드)만 데이터를 수정하므로 자연스럽게 프로세스 동기화가 이뤄질 수 있습니다.

## 소스코드 영역
- entry section

	critical section에 접근을 요청하는 영역

- critical section

	공유한 데이터를 사용하는 영역(count++)

- exit-section

	critical section에서 빠져나오는 영역

- remainder-section

	나머지 영역

``` c
while (true) {
	entry section
		critical section
	exit section
		remainder section
}
```

## 임계영역의 해결방안
- 상호배제(Mutual exclution)

	하나의 프로세스가 임계 영역(critical section)에 들어가 있다면 다른 프로세스는 들어갈 수 없어야 합니다.

- 진행(Progress)

	임계 영역에 들어간 프로세스가 없는 상태에서 들어가려 하는 프로세스가 여러개라면 어느 것이 들어갈지 결정해 주어야 합니다. (deadlock 방지)

- 한정 대기(Bounded waiting)

	다른 프로세스의 기아(Starvation)을 방지하기 위해, 한 번 임계 구역에 들어간 프로세스는 다음 번 임계 영역에 들어갈 때 제한을 두어야 합니다.

### Single core에서 가장 간단한 해결방법
- 공유된 자원을 사용할 때 인터럽트가 발생하지 않도록 합니다.
- 단, 멀티코어 환경일 경우 다른 코어도 전부 인터럽트를 발생시키지 않게되어 효율성이 매우 떨어집니다.

### 비선점형 커널과 선점형 커널
- 비선점형 커널

	한 프로세스가 종료될때까지 점유하기 때문에 race condition이 발생하지 않습니다.
	즉, 임계영역을 만들 필요가 없습니다.

- 선점형 커널

	계속해서 context switch가 일어나기 때문에 race condition 문제가 발생할 수 있습니다.
	즉, 임계영역을 만들어 문제가 생기지 않도록 막아야 합니다.

## 임계영역의 소프트웨어적 해결방안
- Dekker's 알고리즘

	flag를 이용해서 임계영역에 들어갈 프로세스를 결정하는 방식의 알고리즘입니다.

- Eisenberg and McGuire's 알고리즘

	여러개의 프로세스가 최대 n - 1번 시도 이내에 임계 구역에 들어갈 수 있게 보장하는 알고리즘입니다.

- Bakery Algorithm

	여러개의 프로세스가 동작할 때 프로세스마다 번호를 부여해 가장 낮은 번호를 받은 프로세스가 가장 먼저 임계영역에 들어갈 수 있습니다.

- Peterson's Algorithm

	flag를 이용해서 임계영역에 들어갈 프로세스를 결정하는 방식의 알고리즘입니다.

### Peterson's Algorithm

	flag와 turn이라는 변수로 임계영역에 들어갈 프로세스(혹은 스레드)를 결정하는 방식입니다.

	Dekker's 알고리즘과 상당히 유사하지만 상대방에게 진입기회를 양보한다는 차이가 있습니다.

	flag 값은 프로세스 중 누가 임계영역에 진입할 것인지 나타내는 변수이고, turn 변수는 누가 임계영역에 들어갈 차례인지 나타내는 변수입니다.


- 문제점

	피터슨 알고리즘은 현대 컴퓨터에서 정상 작동하지 않는 문제점이 있습니다.

	현대 컴퓨터의 구조가 load와 store 같은 기본적인 기계어를 수행하는 방식 때문에 Peterson의 해결안이 이러한 구조에서 올바르게 실행된다고 보장할 수 없습니다.

	하지만 임계영역을 문제를 해결하는 방법인 상호배제, 진행, 한정 대기를 하는 방법을 쉽게 이해할 수 있도록 해줍니다.

## 임계영역의 하드웨어 기반의 해결방법
- memory barriers or fences
- hardware instructions
- atomic variables

### 원자성(atomicity)
- 더 이상 인터럽트할 수 없는 최소의 단위

