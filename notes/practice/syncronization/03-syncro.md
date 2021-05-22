# Exercise 3

> Given a system with the following types of processes, synchronize your code using semaphores knowing that there are three printers, two scanners, and a shared variable

```js
processA(){
    while(true){
        printer.use();
        shared++;
    }
}

processB(){
    while(true){
        shared++;
        scanner.use();
    }
}

processC(){
    while(true){
        scanner.use();
        printer.use();
    }
}
```

## Solution

### Semaphores

```js
var printerSem = 3;
var scannerSem = 2;
var s = 1;
```

```js
processA(){
    while(true){

        printerSem.WAIT();
        printer.use();
        printerSem.SIGNAL();

        s.WAIT();
        shared++;
        s.SIGNAL();
    }
}

processB(){
    while(true){

        s.WAIT();
        shared++;
        s.SIGNAL();

        scannerSem.WAIT();
        scanner.use();
        scannerSem.SIGNAL();
    }
}

processC(){
    while(true){

        scannerSem.WAIT();
        scanner.use();
        scannerSem.SIGNAL();

        printerSem.WAIT();
        printer.use();
        printerSem.SIGNAL();
    }
}
```
