# 동기화에 대한 대표적인 문제들
- Bounded-Buffer 문제
	- 생산자-소비자 문제

- Readers-Writers 문제

- Dining-Philosophers 문제

## Bounded-Buffer 문제

생산자-소비자 문제는 공유되는 버퍼에 생산자는 데이터를 보내고 소비자는 데이터를 받는 것에 대한 문제입니다.

공유되는 버퍼는 다음과 같이 초기화 합니다.

``` c++
int n;
semaphore mutex = 1; // 이진 세마포어를 이용하여 생산자와 소비자가 동시에 접근할 수 없게 해줍니다.

/* empty와 full은 카운팅 세마포어를 사용하는데 이용합니다. */
semaphore empty = n; 	// 버퍼의 현재 남은 공간을 표시합니다. 
semaphore full = 0; 	// 버퍼의 현재 사용되는 공간을 표시합니다.
```

생산자는 다음과 같은 형태로 구현합니다.
``` c++
wait(empty); 	// 소비자가 버퍼를 다 비울때 까지 기다립니다.
wait(mutex); 	// 여러명의 생산자가 공유 자원에 접근할 수 있으므로 뮤텍스를 이용해 한 프로세스만 접근하도록 합니다.

/* critical section */

signal(mutex);	// 공유자원에 접근이 끝나면 뮤텍스를 반납합니다.
signal(full);	// 소비자가 다 버퍼를 사용할때 까지 기다립니다.
```

소비자는 다음과 같은 형태로 구현합니다.
``` c++
wait(full);	// 버퍼가 다 찰때까지 기다립니다.
wait(mutex); // 여러개의 프로세스가 공유자원에 접근할 수 있으므로 뮤텍스를 이용해 한 프로세스만 접근하도록 합니다.

/* critical section */

signal(mutex);	// 공유자원에 접근이 끝나면 뮤텍스를 반납합니다.
signal(empty);	// 버퍼가 다 비었다는 것을 알려줍니다.
```