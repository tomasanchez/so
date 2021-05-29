# Exersice 6

> Let the processes A, B and C be, synchronize them so that they execute as follows: B, A, C, A, B, A, C, A ..

## Solution

```js
var sA = 0;
var sB = 1;
var sC = 0;
```

```js
processA(){
    while(true){
        sA.WAIT();
        sC.SIGNAL();
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

processC(){
    while(true){
        sC.WAIT();
        sA.SIGNAL();
    }
}
```
