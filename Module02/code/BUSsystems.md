# Module 3

## DIfferent BUS

### 1 Wire

- useful for easy data transmission
- 2 wires - data and ground
- Speed 16.3 kbit/s
- max length: 100m under normal conditions
- each device has a 64 bit address that the master addresses
- use example: NFC, locks, single wire thermostats

### RS232

- was used fpr usb
- up to 9 or 25 wirees, minimum 3
  - transmit
  - receive
    ground
- speed 20 kbps
- length up to 15m

### RS485

- predecessor of RS232
- 2 (4) wires
- speed: 10 Mbit/s
- max length: 1200m
- high immunity against electrical noise
- usage: industry, automation, computer
- connects up to 32 devices

### CAN

- high speed data transmission
- used for microcontroller communication over the network
- lightweight and efficient
- length up to 10km at lower speeds

### I2C/I3C

- goal: standardize sensor communication
- 7 bit addressing -> up to 128 devices
- speed: I2C up to 3.4 Mbit/s, I3C up to 20bit/s
- max length up to a few meters

### SIP

- see presentation
