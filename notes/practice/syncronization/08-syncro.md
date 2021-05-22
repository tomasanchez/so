# Exercise 8

> There is an airport that is used as the base of operations for a fleet of airplanes

> There are **many airplanes**, **ten landing / take-off** runways, and t**wo air traffic controllers**.

> Every time an airplane wants to take off or land, it must use a runway. To do this, it is requested from the input controller, and after being used the output controller is notified so that it is available again.

> It is requested to synchronize the following pseudo-code respecting the established rules, without deadlock and starvation (when the plane has already requested a runway). To do this, you should only use traffic lights, indicating their type and their initial values.

Shared variables

```js
freeRunways = 10;
```

```js
plane = () => {
    while(TRUE){
        mantainance();
        takeOff();
        fly();
        land();
    }
}

entranceController = () =>{
    while(TRUE){
        deliverRunway();
        freeRunways--;
        // Race condition
        console.log(freeRunways);
    }
}

exitController = () =>{
    while(TRUE){
        freeARunway();
        freeRunways++;
        // Race condition
        console.log(freeRunways);
    }
}
```

## Solution

```js
freeRunways = 10;
// Mutexes start in 1
runwayMutex = new Mutex();

//-----------------------
// Sempahores
//-----------------------
runways = new Semaphore(10);

// Entrance Request
runwayResponse = new Sempahore(0);
runwayRequest = new Sempahore(0);

// Exit sync
runwayFree = new Sempahore(0);
```

```js
plane = () => {
    while(TRUE){
        mantainance();

        // Sync with take-off
        runwayRequest.SIGNAL();
        runwayResponse.WAIT();
        takeOff();
        // Sync with exitController
        runwayFree.SIGNAL();

        fly();

        // Sync with landing
        runwayRequest.SIGNAL();
        runwayResponse.WAIT();
        land();
        // Sync with exitController
        runwayFree.SIGNAL();
    }
}

entranceController = () =>{
    while(TRUE){

        runwayRequest.WAIT();

        runways.WAIT();
        runwayDeliver();

        // Fix race condition
        runwayMutex.LOCK();
        freeRunways--;
        console.log(freeRunways);
        runwayMutex.UNLOCK();

        runwayResponse.SIGNAL():
    }
}

exitController = () =>{
    while(TRUE){
        // Sync with plane
        runwayFree.WAIT();

        freeARunway();
        runaways.SIGNAL();

        // Fix race condition
        runwayMutex.LOCK();
        freeRunways--;
        console.log(freeRunways);

        runwayMutex.UNLOCK();
    }
}
```
