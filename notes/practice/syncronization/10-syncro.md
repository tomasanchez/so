# Exercise 10

> Synchronize the following code, corresponding to a process that generates child processes, to avoid inconsistencies, deadlocks and starvation. In addition, you must take the following into account:

```js
 const main = () => {

    while (true) {

        pid = fork();

        if (pid < 0){
            log(‘Error’);
        } else if (pid == 0) {
            log("Y yo soy el hijo");
            realizarTarea();
            // Finaliza el procesohijo
            exit(0);
        } else {
            // Padre
            log(pid + "soy tu padre");
        }
    }
}
```

- Logger is unique
- No more than 50 process in execution
- Father must log before son.

## Solution

```js
let processes = 50
logger.mtx = 1;
logger.sem = 0;

 const main = () => {

    while (true) {

        processes.WAIT();

        pid = fork();

        if (pid < 0){
            logger.mtx.LOCK();
            log(‘Error’);
            logger.mtx.LOCK();
        } else if (pid == 0) {

            logger.sem.WAIT();
            logger.mtx.LOCK();
            log("Y yo soy el hijo");
            logger.mtx.LOCK();

            realizarTarea();
            // Finaliza el proceso hijo
            processes.SIGNAL();
            exit(0);
        } else {
            // Padre

            logger.mtx.LOCK();
            log(pid + "soy tu padre");
            logger.mtx.UNLOCK();
            logger.sem.SIGNAL();
            processes.SIGNAL();
        }
    }
}
```
