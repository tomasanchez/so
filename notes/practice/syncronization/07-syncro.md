# Exercise 7

> Suppose a process is tasked with compiling a set of programs and then sending the result of each compilation by email to the person in charge of that project. This process is organized as follows: N dekernel threads each compile a different program, and then each of them deposit in a list the process) the result; on the other hand, a kernel thread retrieves the results of the compilations and sends an email for each one of them.

## Solución

### A - assuming no limit in list size

```js
let list = [];

comipiler.sem = N;

const compiler = () => {
  while (true) {
    program = new Program();

    compiler.sem.WAIT();
    r = program.compile();
    compiler.sem.SIGNAL();

    list.mtx.LOCK();
    list.push(r);
    list.mtx.UNLOCK();

    r.sem.SIGNAL();
  }
};

const notifyer = () => {
  while (true) {
    r.sem.WAIT();

    list.mtx.LOCK();
    r = list.pop();
    list.mtx.UNLOCK();

    r.sentMail();
  }
};
```

### B - With list limited to <M>

```js
let list = [];

comipiler.sem = N;
list.sem = M;

const compiler = () => {
  while (true) {
    program = new Program();

    compiler.sem.WAIT();
    r = program.compile();
    compiler.sem.SIGNAL();

    list.sem.WAIT();
    list.mtx.LOCK();
    list.push(r);
    list.mtx.UNLOCK();

    r.sem.SIGNAL();
  }
};

const notifyer = () => {
  while (true) {
    r.sem.WAIT();

    list.mtx.LOCK();
    r = list.pop();
    list.mtx.UNLOCK();
    list.sem.SIGNAL();

    r.sentMail();
  }
};
```
