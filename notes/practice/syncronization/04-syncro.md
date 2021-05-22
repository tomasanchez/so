# Exercise 4

> Let be two processes A and B, synchronize them so that they execute alternately: A, B, A, B

## Solution

```js
var sA = 1;
var sB = 0;
```

```js
processA(){
    while(true){
        sA.WAIT();
        sB.SIGNAL();
    }
}

processB(){
    while(true){
        sB.WAIT();
        sA.SIGNAL();
    }
}
```
