# Exercise 02

> Given a system with N processes of the same program, synchronize your code using semaphores to respect the following limits

- `3` shared resources with `M` instances
- `M` shared resources with `3` instances

```js
program(){

    while(true){
        let idResource = getResource();
        useResouse(idResource);
    }

}
```

## Solution for 3 - M

```js
// Semaphores
var s = [M, M, M];

program(){

    while(true){
        // suppose idResource can have values of [0, 1, 2]
        let idResource = getResource();
        // BEGIN OF: critical section.
        WAIT(s[idResource]);
        useResouse(idResource);
        SIGNAL(s[idResource]);
        // END OF: critical section.
    }
}
```

### Solution for M - 3

```js
// Semaphores
var s = [3, 3, ...];

program(){

    while(true){
        // suppose idResource can have values of [0, 1, 2, M-1]
        let idResource = getResource();
        // BEGIN OF: critical section.
        WAIT(s[idResource]);
        useResouse(idResource);
        SIGNAL(s[idResource]);
        // END OF: critical section.
    }
}
```
