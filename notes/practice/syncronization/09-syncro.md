# Exercise 9

> There is a program to simulate the execution of penalties in a soccer match, which consists of three processes: referee, player and goalkeeper. The pseudocode is as follows:

```js
const ref = () => {
  while (true) {
    order.give();
    order.sem.SIGNAL();

    shot.sem.WAIT();
    shot.validation.validate();
    shot.validation.SIGNAL();
    shot.validation.SIGNAL();
    turn[nextPlayer()].SIGNAL();
  }
};

const player = () => {
  while (true) {
    turn[actual()].WAIT();
    this.positionate();

    order.sem.WAIT();
    this.shot();
    shot.validation.WAIT();

    if (shot.equals(GOAL)) {
      this.celebrate();
    } else {
      this.cry();
    }
  }
};

const goalkeeper = () => {
  while (true) {
    this.positionate();

    shot.sem.WAIT();
    shot.intercept();

    shot.validation.WAIT();
    if (!shot.equals(GOAL)) {
      this.celebrate();
    } else {
      this.cry();
    }
  }
};
```
