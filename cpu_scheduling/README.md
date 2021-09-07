# CPU Scheduling
- 메모리에 올라온 프로세스들 중 어떤 프로세스를 먼저 처리할지 순서를 정하는 것을 의미합니다.
## CPU Scheduling의 목적
- CPU는 원래 한번에 하나의 프로세스만을 실행시킬 수 있는데 특정 프로세스가 I/O 요청등에 의해 대기하게 될 경우 CPU는 사용되지 않습니다.

	멀티 프로그래밍은 낭비되는 시간을 최소한으로 줄이기위해 CPU는 낭비되는 시간 동안 다른 프로세스를 실행하게 되고 `CPU는 낭비되는 시간을 줄여서 최대한의 성능을 이끌어 낼 수 있습니다.`

	<img src = "https://s3.us-west-2.amazonaws.com/secure.notion-static.com/920fe817-5127-415c-8de2-ff7eebd0bfab/Untitled.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAT73L2G45O3KS52Y5%2F20210907%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20210907T075121Z&X-Amz-Expires=86400&X-Amz-Signature=8a18df62b1b71a9a081e350608adf15eb75ad72ad70d10b36e14e6c3d0ca8f6e&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22Untitled.png%22" width = "40%" height = "40%">

# CPU Scheduler
- 메모리에서 실행할 준비가 된 프로세스 중에서 하나의 프로세스를 CPU에 할당합니다.

## CPU Scheduler 프로세스 선정 기준
- 연결리스트 or 이진트리
- FIFO Queue(First-In, First Out 먼저 들어온 데이터가 먼저나감) or Priority Queue(우선순위를 결정해서 출력하는 큐)

# 선점 및 비선점 스케줄링

## 비선점(Non-preemptive) 스케줄링
- 프로세스는 CPU를 종료하거나 대기 상태로 전환하여 CPU를 해제할 때까지 CPU를 유지합니다.

## 선점(preemptive) 스케줄링
- 실행중인 프로세스를 강제로 다른 프로세스로 전환하여 사용할 수 있습니다.

## CPU 스케줄링 기준
1. 한 프로세스가 실행상태에서 대기 상태로 전환될 때 (I/O 요청)
2. 프로세스가 실행 상태에서 준비완료 상태로 전환될 때 (프로세스에 할당된 시간이 끝났을때)
3. 프로세스가 대기 상태에서 준비완료 상태로 전환될 때 (I/O 종료)
4. 프로세스가 종료될 때

- 1번과 4번 -> 비선점(non-preemptive) 스케줄링 사용
- 2번과 3번 -> 선점(preemptive) or 비선점(non-preemptive) 스케줄링 사용

	단, 선점스케줄링이 더 CPU의 성능을 이끌어낼 수 있기 때문에 2번과 3번의 경우 선점 스케줄링이 많이 쓰입니다.

# dispatcher
- 준비완료 상태의 프로세스 중 하나를 CPU가 사용가능한 상태가 될 때 CPU에 할당해주는 역할을 합니다.

# 스케줄링의 목표
- CPU Utilization(CPU 사용률)

	CPU 사용률을 높여 최대한의 성능을 이끌어 내는 것이 목표입니다.

- Throughput(처리량)

	어떤 단위 시간당 완료된 프로세스의 개수를 늘리는 것이 목표입니다.

- Turnaround time(총 처리 시간)
	
	Ready Queue(준비 큐) + CPU에서 프로세스가 실행된 시간 + I/O 시간을 합한 시간을 최대한 줄이는 것이 목표입니다.

- Waiting time(대기 시간)

	어떤 프로세스가 Ready Queue에서 대기하고 있는 시간을 줄이는 것이 목표입니다.

- Response time(응답 시간)

	응답하는 시간을 최소한으로 줄이는 것이 목표입니다. (출력되는 시간이 포함되지 않고 순수하게 요청에 대한 응답만 포함합니다.)

# CPU 스케줄링 알고리즘

- FCFS(First-Come, First-Served)

	가장 간단한 CPU 스케줄링 알고리즘입니다.
	
	프로세스가 요청한 순서대로 CPU를 할당받습니다. (비선점 스케줄링)

	FIFO Queue를 이용해서 구현합니다.

	FCFS를 사용할 경우 프로세스의 CPU 버스트 타임(프로그램의 수행중에 연속적으로 CPU를 사용하는 구간)이 다른경우 일반적으로 최소 값이 아니며 최소 값과 상당히 다를 수 있습니다.(더 오랜시간이 걸림)

	convoy effect가 발생합니다. -> 소요시간이 긴 프로세스가 먼저 도달하여 시간을 잡아먹고 있는 현상

- SJF(Shortest Job First)

	가장 작은 CPU 버스트 시간을 가진 프로세스에게 우선적으로 CPU를 할당합니다.
	
	만약 CPU 버스트 시간이 동일하다면 FCFS 방식으로 작동합니다.

	SJF 알고리즘은 주어진 프로세스 집합에 대한 최소 평균 대기 시간을 제공합니다.

	긴 프로세스 이전에 짧은 프로세스를 먼저 처리하면 짧은 프로세스의 대기 시간이 긴 프로세스를 기다리는 것 보다 짧아지므로 평균 대기 시간이 감소합니다.

	하지만 SJF 알고리즘은 구현이 거의 불가능한데, 컴퓨터 입장에서는 프로세스의 CPU 버스트 타임의 길이가 얼마인지 알 수 있는 방법이 없기 때문입니다.

- RR(Round-Robin)
- Priority-based

- MLQ(Multi Level Queue)
- MLFQ(Multi-Level Feedback Queue)