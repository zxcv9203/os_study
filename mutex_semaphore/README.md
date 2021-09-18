# 뮤텍스와 세마포어
- 뮤텍스(Mutex Locks)

	동기화를 위한 가장 간단한 도구입니다.

- 세마포어(Semaphore)

	뮤텍스보다 강력하고 편리하며 효과적인 도구입니다.

- 모니터(Monitor)

	뮤텍스와 세마포어의 문제를 개선한 도구입니다.

- 라이브니스(Liveness)

	프로세스가 진행되도록 보장합니다. 위의 도구들이 상호배제 문제만 해결주었다면 라이브니스는 데드락 문제도 해결해줍니다.

# 뮤텍스(Mutex Lock)
- mutex(`Mut`ral `ex`clusion) -> 상호배제를 구현하는 도구
- 임계영역을 보호해주고 경쟁상황이 발생하는 것을 막아줍니다.
- 프로세스는 임계영역에 들어가기 전에 lock을 겁니다. (acquire lock)
- 임계영역에 벗어나면 lock을 해제합니다. (release lock)

### 뮤텍스의 구현
acquire()로 lock을 걸고 releases()로 lock을 해제합니다.

avaliable : 잠금 상태를 확인하는 boolean 변수를 사용합니다.
```
while (true) {
	acquire lock
		critical section
	releases lock
		remainder section
}
```
- acquire() 구현
```
acquire() {
	while (!available)
		; /* busy wait */
	available = false;
}
```

- releases() 구현
```
 releases() {
	 available = true;
 }
```

acquire() 와 releases()는 원자적으로 구현되어야 합니다. (원자적이지 않으면 context switch가 일어나면서 값이 이상하게 나올 수 있음)

compare_and_swap 방식으로 구현할 수 있습니다.

## busy waiting 방식

- 어떤 프로세스가 임계영역에 진입하기 위해 계속해서 acquire()를 호출합니다.
- busy wating 방식은 계속해서 루프를 돌며 기다리기 때문에 멀티프로그래밍 환경에서 CPU 처리시간을 낭비하게 됩니다.

# Spinlock
- busy waiting을 사용하는 mutex lock을 Spinlock이라고 합니다.
- 사용가능한 상태가 될때까지 계속해서 프로세스를 회전합니다.
- busy wating 상태로 대기하다가 권한을 얻는 순간 바로 작업이 수행할 수 있기 때문에 context switch를 하면서 소모되는 시간이 줄어들지만 CPU를 선점하는 동안 사실상 아무 동작을 하고 있지 않는 것이기 때문에 시간을 낭비하게 됩니다.

# Semaphore(세마포어)
- 공유된 자원의 데이터 혹은 임계영역 등에 프로세스나 스레드를 나타내는 값을 두어서 상호배제를 구현할 수 있습니다.

## 세마포어의 구현
세마포어는 두 가지 원자연산을 통해서만 접근할 수 있는 정수 변수입니다.

wait(), signal() or P() V()로 표현합니다.

``` C++
wait(s) {
	while (s <= 0);
}
s--;

signal(s) {
	s++;
}
```

## 세마포어의 종류
- Binary Semaphore(이진 세마포어)

	세마포어의 값으로 0또는 1을 가집니다. 뮤텍스와 비슷한 방식입니다.

- counting semaphore

	초기값은 할당가능한 자원의 수로 정해지며, 세마포어의 값의 범위는 정해져 있지 않습니다.

### 카운팅 세마포어
- 할당가능한 자원수로 세마포어 변수를 초기화합니다.
- 프로세스가 자원을 사용하려고 하면 wait()을 호출하여 값을 1 감소시킵니다.
- 프로세스가 자원을 다 사용하면 signal()을 호출하여 값을 다시 증가시킵니다.
``` c++
typedef struct {
	int value;
	struct process *list;
} semaphore;
wait(semaphore *s) {
	s->value--;
	if (s->value < 0) {
		add this process to s->list
		sleep();
	}
}
signal(semaphore *s) {
	s->value++;
	if (s->value <= 0) {
		remove a process P from S->list;
		wakeup(P);
	}
}
```