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

## The Readers-Writers 문제

여러개의 프로세스가 하나의 저장 공간을 공유하며 이를 접근할 때 발생하는 문제입니다.

예를들어 동시에 실행되는 프로세스들이 하나의 데이터 베이스를 공유하는 상황이 있다면,

Reader는 데이터 베이스를 읽기만 원하는 반면, 작성자는 데이터베이스를 업데이트(읽고 쓰기)를 할 수 있습니다.

참고로 두 명이상의 Reader가 동시에 공유 데이터에 접근하는 경우 부작용은 발생하지 않습니다.

그러나 Writer가 다른 프로세스(Reader 혹은 Writer)가 동시에 데이터베이스에 액세스하면 혼란이 뒤따를 수 있습니다.

### Readers-Writers 문제 조건

첫번째로, 어떤 독자도 단순히 작가가 기다리고 있다는 이유로 다른 독자들이 끝나기를 기다려서는 안됩니다.

두번째로, 작성자가 공유 자원에 접근하기 위해 기다리고 있다면, 새로운 독자들은 읽기를 시작하지 않을 것입니다.

> 첫번째 Readers-Wrtiers 문제 해결 방안

``` c++
semaphore rw_metex = 1;	// Readers & writers 프로세스 확인
semaphore mutex = 1;	// 업데이트될 때 상호 배제를 확인하는데 사용합니다.
int read_count = 0;		// read_count 개체를 읽고 잇는 프로세스 수를 추적합니다. (0일때만 쓰기를 실행합니다.)
```

Writer 프로세스 구조
``` c++
while (true) {
	wait(rw_mutex);

	/* data 작성하는 영역 */

	signal(rw_mutex);
}
```

Reader 프로세스 구조
``` c++
while (true) {
	wait(mutex);
	read_count++;
	if (read_count == 1)
		wait(rw_mutex);
	signal(mutex);
	
	/* data 읽어오는 영역 */
	
	wait(mutex);
	read_count--;
	if (read_count == 0)
		signal(rw_mutex);
	signal(mutex);
}
```

writer가 임계영역에 있고 n개의 Reader가 대기 중인 경우 하나의 Reader는 rw_mutex에서 대기하고 n - 1 개의 Reader는 mutex에서 대기합니다.

또한, Writer가 signal(rw_mutex)를 실행할 때, 대기중인 Reader나 대기 중인 단일 Writer의 실행을 재개할 수 있음을 관찰합니다.

선택되는 프로세스는 스케줄러에 의해서 정해집니다.

## Reader-Writer Locks

Readers-Writer 문제에 대한 해결책은 이미 Reader-Writer lock을 이용해서 구현되어 있습니다.

Reader-Writer lock을 얻으려면 읽기 또는 쓰기의 잠금 모드를 지정해야 합니다.

읽기 모드에서는 여러 프로세스가 획득할 수 있지만

쓰기 모드에서는 Writer에게 독점적인 액세스가 필요하기 대문에 오직 하나의 프로세스만 쓰기에 대한 잠금을 얻을 수 있습니다.

# The Dining-Philosophers 문제

식사하고 먹으면서 일생을 보내는 다섯 명의 철학자가 있다고 했을 때 이 철학자들은 젓가락 한쪽을 5개 가지고 있습니다.

철학자는 밥을 먹을 때 가장 가까운 젓가락 두개를 집어서 식사를 시작합니다.

만약 인접한 두명의 철학자가 젓가락을 동시에 잡았을 때에 대한 문제입니다.

여러개의 공유자원과 여러개의 프로세스가 존재할때, 데드락과 기아문제에 대해서 자유롭게 실행이 되어야합니다.

## 세마포어를 이용한 식사하는 철학자 문제 해결방안

하나의 젓가락을 세마포어로 표현하여 해결할 수 있습니다.

철학자는 젓가락을 습득할때(공유자원에 접근할 때) wait()을 호출하고 젓가락을 다사용하면(공유자원을 다 사용한 경우) signal()을 호출합니다.

위의 해결방법으로는 상호배제 문제는 해결이 되지만 여전히 deadlock과 starvation 문제가 발생할 수 있습니다.

예를들어 5명 모두가 식사를 하려고하면 왼쪽 젓가락을 잡은 후 오른쪽 젓가락을 잡아야하는데 남는 젓가락이 없어 5명 모두가 굶게되고 결국 5명이 다 굶어죽게 됩니다. (데드락 상황)

### 식사하는 철학자 문제 데드락 해결방안

1. 철학자들의 숫자를 4명으로 제한하고 철학자가 젓가락을 양쪽 다 들 수 있는 경우에만 젓가락을 들 수 있도록 합니다.

2. 짝수 철학자는 왼쪽 젓가락과 오른쪽 젓가락 순서로 젓가락을 집고 홀수 철학자는 오른쪽 젓가락과 왼쪽 젓가락 순서대로 젓가락을 집습니다.

해당 방법으로 데드락 상황은 해결할 수 있지만 기아 문제는 해결하기 힘듭니다.

## 모니터를 이용한 식사하는 철학자 해결방안

철학자는 양쪽의 젓가락을 집을 수 있는 상태에만 젓가락을 듭니다.

철학자 상태를 3개로 지정합니다.
- 생각하는 상태
- 배고픈 상태
- 먹고있는 상태

철학자들은 자기 상태를 배고픈 상태에서 먹고있는 상태로 바꿀 수 있는데, 왼쪽에 있는 철학자와 오른쪽에 있는 철학자가 먹고있지 않을 때 가능합니다.

또한 철학자가 배가 고픈데 젓가락을 얻을 수 없을 때 지연시킬 수 있는 변수가 필요합니다.

젓가락을 사용하는 것은 모니터인 Dinning Philosopher에 의해 제어됩니다.

각 철학자는 식사를 하기전에 pickup()을 호출하여 먹을 수 있는 상태인지 확인 후 식사를 시작합니다.

픽업이 성공적으로 완료하면 철학자는 먹을수 있는 상태이고, 다 먹었으면 putdown()을 호출하여 젓가락을 내려 놓습니다.

위의 해결방안은 상호배제와 데드락 문제는 해결되지만 기아문제는 해결되지 않을 것 입니다.

``` c++
monitor DingingPhilosophers
{
	enum {THINKING, HUNGRY, EATING} state[5];
	condition self[5];

	void pickup(int i) {
		state[i] = HUNGRY;
		test(i);
		if (state[i] != EATING)
			self[i].wait();
	}

	void putdown(int i)
	{
		state[i] = THIKING;
		test((i + 4) % 5);
		test((i + 1) % 5);
	}

	void test(int i) {
		if ((state[(i + 4) % 5] != EATING) && (state[i] == HUNGRY) && (state[(i + 1) % 5] != EATING)) {
			state[i] = EATING;
			self[i].signal();
		}
	}
	initialization_code() {
		for (int i = 0; i < 5; i++)
			state[i] = THINKING;
	}
}
```

# thread-safe한 동시성 어플리케이션

동시성을 가지는 응용 프로그램은 뮤텍스, 세마포어 및 모니터와 같은 기술을 사용하여 다중 코어 시스템에서 우수한 성능을 발휘합니다.

그러나, 위험성이 증가하는데 경쟁 상태나 liveness hazards로 인해 deadlock 문제가 발생할 확률이 높아집니다.

thread-safe한 동시성 어플리케이션을 설계하기 위해서는 다음과 같은 방법이 있습니다.
- Transactional memory
- OpenMP
- 함수형 프로그래밍 언어
