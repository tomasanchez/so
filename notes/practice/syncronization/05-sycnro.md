# Exercise 5

> Let processes A, B and C be, synchronize them so that they execute alternately: A, B, C, A, B, C

## Solution

```js
var sA = 1;
var sB = 0;
var sC = 0;
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
        sC.SIGNAL();
    }
}

processC(){
    while(true){
        sC.WAIT();
        sA.SIGNAL();
    }
}
```
