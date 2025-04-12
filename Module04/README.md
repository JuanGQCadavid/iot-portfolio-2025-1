# Module 2

> **_NOTE:_**  All the work was with my teammate Martinm aka [LogicLobster](https://github.com/LogicLobster/IoT-Tartu-Spring25)

## Catalog

* Catalog could be accessed here: [catalog.md](../catalog.md)

## Reflections

### Reflection 6
[Reflection 4](../Reflections/ref06.md)

### Reflection 7
[Reflection 5](../Reflections/ref07.md)

## Tasks - Session 1

### Task - Crash!

Divided by 0

> Main code: [main.cpp](./code/simplebreak/src/main.cpp)

``` c
value = value/0;
snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
Serial.print("Publish message: ");
```

![Blink image](./pictures/div0.png)

--- 

> Main code: [main.cpp](./code/simplebreak/src/main_2.cpp)

``` c
--value;
snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld division %ld", value, 100/value);
```

![Blink image](./pictures/div0_2.png)

--- 

> Main code: [main.cpp](./code/simplebreak/src/main_3.cpp)

``` c
char* msg = new char[512]; // Allocate space
sprintf(msg, "Hello at %ld.", millis());

static String extend_msg;
extend_msg += msg;
extend_msg += "And more";

// Publish without freeing memory
client.publish("test/output", extend_msg.c_str());
```

![Blink image](./pictures/space.png)

--- 

This time intenrrupts crasshes due to the sleep.

> Main code: [main.cpp](./code/simplebreak/src/main_4.cpp)

``` c
void ICACHE_RAM_ATTR handleInterrupt() {
 interruptFlag = true;
//  delay(1000); // Blocking delay
}
```

![Blink image](./pictures/interrup.png)

--- 

## Tasks - Session 2

### Task  - Simulator in Python

**Notes** : 

> integration code: [integration.py](./code/iotknit-demo/integration.py)

> simulators code: [simulators.py](./code/iotknit-demo/simulators.py)

![Blink image](./pictures/2_2_1.png)

![Blink image](./pictures/2_2_2.png)


### Task - Mini project: Restricted HVAC system and Relay

**Notes** : 

> Main code: [main.cpp](./code/iotknit-demo/)

![Blink image](./pictures/2_1_1.png)

![Blink image](./pictures/2_1_2.png)

![Blink image](./pictures/2_1_3.png)


### Task - Node-RED bigger integration

![Blink image](./pictures/node-red-no-dash.png)

> Node red code: [main.cpp](./nodered/no-dashboard.json)

> Video: [main.cpp](./videos/3_1.mp4)

![Blink image](./pictures/2_1.gif)


### Task - Node-RED Dashboard

![Blink image](./pictures/node-red-dash.png)

![Blink image](./pictures/dash.png)

> Node red code: [main.cpp](./nodered/dashboard.json)

> Video: [main.cpp](./videos/3_2.mp4)

![Blink image](./pictures/2_2.gif)

## Tasks - Session 3

### Task  - Mini Project: Install SNodeC on the MANGO router

![Blink image](./pictures/3_mini_1.png)

![Blink image](./pictures/3_mini_2.png)


### Task  - Project: Full Access Control system in Node-RED

**Notes** : For this project we simualte the entrance door. It could be open by two cards (One for Martin, one for Juan) and a proximity sensor for the dog, the display will say a greeting message and the door will be opened. Furthermore, there will be a greeting message from nodered dashboard which will be located on the door, showing also the status of the door.


> RFID Reader: [main.cpp](./code/RFIDreaderMOD4/src/main.cpp)

> Proximity sensor Reader: [main.cpp](./code/DistanceSensor/src/main.cpp)

> Display code: [main.cpp](./code/OLED_MOD_4/src/main.cpp)

> Door (Relee with actuator) code: [main.cpp](./code/HVAC_AC_Mod4/src/main.cpp)


> Node red integrator: [main.cpp](./nodered/full-integration.json)

![Blink image](./pictures/3_Project_1.jpg)
![Blink image](./pictures/3_Project_5.jpg)
![Blink image](./pictures/3_Project_3.jpg)
![Blink image](./pictures/3_Project_4.jpg)
![Blink image](./pictures/3_Project_6.jpg)
![Blink image](./pictures/3_Project_7.jpg)

---

> Video all working: [3_project.mp4](./videos/3_project.mp4)




<!-- 
### Task  - 

**Notes** : 

> Main code: [main.cpp](./code/Blink3/src/main.cpp)
![Blink image](./pictures/blink.jpg)
![Blink image](./pictures/blink_2.JPG)
---
![Blink image](./pictures/blink.gif)

 -->



