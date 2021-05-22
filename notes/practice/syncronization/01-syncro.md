# Exercise 01

> Given the following processes with shared variables, synchronize them to guarantee mutual exclusion on them

## Shared variables

```js
var a = (b = 1);
```

## Processes

```js
process0(){
    let d = 1;

    while(true){
        a += d;
        d *= d;
        b -= d;
    }
}

process1(){
  let e = 2;
  while(true){
        b *= e;
        e = e ^ e;
        a++;
  }
}
```

## Solution

The first approach could be:

```js
var sA = new Semaphore(1);
var sB = new Semaphore(1);
```

```js
process0(){
    let d = 1;

    while(true){
        WAIT(sA);
        a += d;
        SIGNAL(sA)
        d *= d;
        WAIT(sB)
        b -= d;
        SIGNAL(sB);
    }
}

process1(){
  let e = 2;
  while(true){
        WAIT(sB)
        b *= e;
        SIGNAL(sB);
        e = e ^ e;
        WAIT(sA);
        a++;
        SIGNAL(sA);
  }
}
```
