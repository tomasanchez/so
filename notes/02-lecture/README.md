# 02 - Process

## Content

- Life cycle
  - 2 States
  - 5 States
  - 7 States
- States in Linux
- Syscalls
- Process Switch

## Process

### Life Cycle

**2-state Diagram**

![2-State](images/2-state.png)

**5-state Diagram**

![5-State](images/5-state.png)

**7-state Diagram**

![7-State](images/7-state.png)

Even though the `process` is _suspended_, `PCB` is **never** on disk, always on memory until process _exists_.

### States in Linux

When running `ps`

```
D:    uninterruptible sleep (usually IO)
R:    Running or runnable (on run queue)
I:    Idle kernel thread
S:    interruptible sleep (waiting for an event to complete)
T:    stopped by job control signal
t:    stopped by debugger during the tracing
W:    paging (not valid since the 2.6.xx kernel)
X:    dead (should never be seen)
Z:    defunct ("zombie") process, terminated but not reaped by its parent
```

## Syscall

|                                        | Blocking |             Non-blocking             |
| :------------------------------------- | :------: | :----------------------------------: |
| Operation can be executed immediatly   | Operates |               Operates               |
| Operation may take a while (undefined) |  Blocks  | No operates, but continues execution |
| Return values                          | OK/ERROR |           OK/ERROR/RE-TRY            |

## Process Switch

**When does it occur?**

Whenever OS recover control after:

- Syscall
- Interruption (hw/sw)

Process Context, within the PCB, is saved during this operation.

### Steps

1. Interruption
2. HW: SO-Stack <-- PC and PSW (save process context)
3. HW: PC <-- SO routine && **mode switch** (user to kernel)
4. SO: Stack <-- other registers (rest of context)
5. SO: Decides to **switch process**
6. SO: A's PCB <-- PC, PSW and rest (from SO-Stack)
7. SO: A's PCB.state <-- _Ready_
8. SO: Ready Queue <-- A's PCB
9. SO: Selec other process: _B_
10. SO: B's PCB.state <-- _Running_
11. SO: Memory Management register <-- B's limits
12. SO: Processor state <-- PCB's B (PC, PSW, etc) && **mode switch**( kernel to user)
