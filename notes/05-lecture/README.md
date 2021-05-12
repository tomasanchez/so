# 05 - Concurrency and Sincronization

## Content

- Race condition

## Race condition

Suppose

```c
int counter = 0;

// THREAD A ---------------
for( i = 0; i < 1000 ;i++ )
  counter++;
// _________________________


// THREAD B ---------------
for( i = 0; i < 1000 ;i++ )
  counter++;
// _________________________

```

> Will the final value of counter be 2000?

_Answer_: not necessarily.

Then:

**Race Condition** is the situation in which multiple processes / threads modify shared data, and the final value of the same depends on the speed of their execution (which can produce inconsistent values ​​for both).

## Concurrency

### Types

- **Multiprogramming**: refers to the manage of multiple processes in memory .
- **Mutiprocessing**: refers to the manage of multiple processes in a multriprocessor system.
- **Distributed processing**: refers to the management of multiple processes on multiple distributed computers.

### Why?

- **Performance**: due to multiprogramming.
- **Structurated application**: design driven. A program may be defined as a set of processes or concurrent threads.

### Iteration forms

|                      |          Coupling          | Resourse Managament |
| :------------------- | :------------------------: | :-----------------: |
| Competency           | Unknowledge of contestants |         OS          |
| Indirect cooperation |      Knows existance       |   Process/Thread    |
| Direct cooperation   |      Knows existance       |   Process/Thread    |

### Conclussions

- The relative speed of processes can never be predicted.
- The speed of processes cannot be relied upon to assume "_atomicity_" of certain operations.

## Critical Section

```
  <Irrelevant section>
          ...
<Begin of Critical Section>
    <Critical section>
<End of Critical Section>
          ...
  <Irrelevant section>
```

Is the code section where threads will use shared resources.

For example, continueing the `counter` problem...

```c
int f(void){
//...
wait_my_turn();
counter++;
end_my_turn();
//...
}
```

### Mutual exclusion

Requirement by which it is said that while a process is in a critical section to use a resource, no other process must be able to access its critical section to use that same resource.

**Exclusive requirements**

1. Mutual exclusion
2. Limited wait (neither _deadlock_ nor _starvation_)

**Considerations** (_desirable ascpects_)

- Process NOT in critical section (_CS_) does not interfer in anyway with others.
- Immediate admission for _CS_ when no process on it.
- The permanence in the _CS_ must be for a finite and reduced time

**Possible Solutions**

- Software

  - Global variables, conditions and algorithms

- Hardware

  - Disable interruptions
  - Special instructions

- OS

  - Semaphores
  - Monitors
