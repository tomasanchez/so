# 09 - Deadlock

## Introduction

- Limited resources (CPU, Memory, Devices, etc)
- Processes
  - Request
  - Use
  - Free
- Unavailable resource, process can block itself

![Car expample](images/deadlock_car.png)

```c
void car1(void){
   wait(a);
   wait(b);

   execute();

   signal(a);
   signal(c);
}

void car2(void){
   wait(b);
   wait(c);

   execute();

   signal(b);
   signal(c);
}

void car3(void){
   wait(c);
   wait(d);

   execute();

   signal(c);
   signal(d);
}

void car4(void){
   wait(d);
   wait(a);

   execute();

   signal(d);
   signal(a);
}
```

## Definition

> Permanent blocking of a set of processes
> where each of these processes is waiting
> an event that can only generate a process of the set.

## Resources

### Types

- Reusable
- Consumable

### Asignment

#### Graph

> It allows to represent the state of the system with respect to
> allocation of resources to each process at a specific time

![graph](images/graph.png)

##### Cycles

- No cycle, no deadlock
- A cycle MAY imply deadlock existance
- A cycle and all resources have only one instance, then there is deadlock

![deadlock existance](images/deadlock_existance.png)

## Existance Condition

### Necessary condition

- Mutual exclusion
- Hold and waiting
- No resource preemptiveness

### Necessary and sufficient condition

- Circular waiting

> NOTE: All 4 at the same time
