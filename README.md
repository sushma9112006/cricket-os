---

# T20 World Cup Cricket Simulator (OS Project)

This project is a multi-threaded simulation of a T20 cricket match built to demonstrate core OS concepts like threads, synchronization, scheduling, and deadlock handling.

The match simulated is India vs New Zealand in a T20 World Cup Final scenario.

---

## What this project does

This program simulates a full T20 match ball by ball. It includes:

* Two innings (first batting and chasing)
* Ball-by-ball match log
* Dynamic scoring and wickets
* Bowler selection based on match situation
* Batter selection using scheduling algorithms
* Gantt chart showing resource usage
* Wait time analysis for scheduling

---

## Core Operating System Concepts Used

### 1. Threads

* Each ball is handled as a threaded task
* Bowler(threads) acts as a thread that modifies to the pitch(critical section)
* Fielders are passive threads that wake up when the ball is hit
* Batters are modeled as active entities interacting with shared resources

---

### 2. Critical Section (Pitch)

The pitch is treated as a shared resource.

* Only one ball can be played at a time
* Protected using a mutex (`pitch_mutex`)
* Ensures no two threads modify match state at the same time

---

### 3. Synchronization

#### Mutexes

Used to protect shared data:

* Scoreboard
* Match state
* Logging output

#### Semaphores

* The crease has capacity 2
* Controlled using a semaphore
* Prevents more than two batters being active

#### Condition Variables

* Fielders wait on the condition variable **ball_hit_cond**, which is triggered when **match_state.ball_in_air** becomes true

---

### 4. Scheduling (Batter Selection)

Two scheduling strategies are implemented, you can choose either of these algorithms:

#### FCFS (First Come First Serve)

* Batters come in fixed order

#### SJF (Shortest Job First)

* Batters are selected based on:

  burst = 1 / (batting average × strike rate)

* Lower burst means higher priority

* This prioritizes aggressive batters


---

### 5. Deadlock Handling (Run-Out Situation)

Run-out is the deadlock problem here.

Scenario:

* Two batters try to reach the same end (resource conflict)

Approach:
* Resource Allocation Graph (RAG) is maintained
* Cycles are detected
* If deadlock occurs, one batter is selected as victim

Victim selection is based on cost:
* Lower performing batter is more likely to get out

This simulates OS deadlock detection and recovery.

---

### 6. Bowler Scheduling

Bowlers are grouped into queues:

* Normal
* Economical
* Wicket-taking

Selection depends on previous over performance:

* Low runs - normal
* Medium runs - economical
* High runs - wicket-taking

---

### 7. Gantt Chart

A simple Gantt chart is printed:

* Each dot represents a ball
* Shows which batter used the pitch at each step

---

### 8. Wait Time Analysis

The program calculates:

* Arrival time of batters
* Start time
* Waiting time

This helps compare FCFS vs SJF behavior.

---

## How to compile and run

Use a Linux system or any environment with pthread support(Windows doesn't have pthreads support, soi you can use WSL as well).

Compile:

```
g++ main.cpp -lpthread -o simulator
```

Run:

```
./simulator
```


---

## Assumptions made

* Each ball is treated as one execution unit
* Pitch is a single shared resource
* Only two batters can exist at the crease
* Deadlock is limited to two-process cycle detection
* Threads are used in a controlled manner for simulation clarity

---

## Limitations

* True parallelism is limited since some threads are joined immediately
* Deadlock detection handles simple cases, not full graph cycles
* Scheduling is not exact OS CPU scheduling, they are modified versions according to our needs

---
## Demo link



---
## Team members
*Jakkula Charita Sai Sushma(24114044)
*Ragala Akhil(24114072)
*Srutha Keerthi Cheruku(24114094)
*Nitta Anshu Sri(24114063)

