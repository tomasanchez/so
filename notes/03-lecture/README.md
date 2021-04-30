# 03 - Scheduling

## Content

- Scheduling
  - Types
    - LTS
    - MTS
    - STS
  - Multiprogramming
- Criteria to evaluate Schedulers
  - Gantt's diagram
- Scheduling Algorithms

## Scheduling

As with **multiprogramming** we want to get it best, many process are created.
As resource `CPU TIME` is limited. We need an efficient multiprogramming.

It is **key** to have some sort od coordination: `Scheduling`.

### Long Term Scheduler (LTS)

Dedices wheter a process will be admited at `Ready Queue` (or _Ready/suspended_).

### Medium Term Scheduler (MTS)

Decides wether to suspend a process in both suspended queue.

Both `LTS` and `MTS` define how _loaded_ the system is.
Relevants on critical systems.

<hr>

### Multiprogramming Level

The number of active process in memory. Refers to how much _stressed_ the system is.

<hr>

### Short Term Scheduler (STS)

Decides which of the ready, in-memory processes is to be executed.

> NOTE: Stallings states that STS is the Dispatcher

- Executes with greater frequency
- Essential for multiprogramming
- Executes when OS is requested
  - Interuptions
  - Syscalls

## Criteria to evaluate Schedulers

<style type="text/css">
.tg  {border-collapse:collapse;border-spacing:0;}
.tg td{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  overflow:hidden;padding:4px 17px;word-break:normal;}
.tg th{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  font-weight:normal;overflow:hidden;padding:4px 17px;word-break:normal;}
.tg .tg-baqh{text-align:center;vertical-align:top}
.tg .tg-nrix{text-align:center;vertical-align:middle}
</style>
<table class="tg">
<thead>
  <tr>
    <th class="tg-baqh"></th>
    <th class="tg-baqh">Benefits</th>
    <th class="tg-baqh">Other Criteria</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td class="tg-nrix">Process<br>User<br>Oriented<br></td>
    <td class="tg-nrix">Execution Time<br>Waiting Time<br>Response Time</td>
    <td class="tg-nrix">Predictability<br></td>
  </tr>
  <tr>
    <td class="tg-nrix">System<br>Oriented<br></td>
    <td class="tg-nrix">Throughput<br>CPU Usage<br></td>
    <td class="tg-nrix">Equity<br></td>
  </tr>
</tbody>
</table>

### Gantt Diagram

![Gantt](images/gantt.png)

See how in the first Diagram:

```
Waiting Time (A)    = 0
Waiting Time (B)    = 2
Waiting Time (C)    = 4
```

```
Waiting Time (A)    = 12
Waiting Time (B)    = 0
Waiting Time (C)    = 2
```

## Scheduling Algorithms

### First Come First Served (FCFS or FIFO)

First process which arrives to the ready queue is also the first one selected to be executed. And is executed until is blocked. (Non-preemtive)

![FIFO](images/fifo.png)

- Ignoring OS CPU time.
- Table is an execution trace.
- CPU burst vs I/O burst.
- Priority: arrive time.

### Shortest Process Next (SPN or SJF)

Shortest Job, in the ready queue is the Next to be executed.

![SJF](images/spn.png)

This algorithm may cause `starvation` for long CPU burst process. As it is Non-preeptive.
