# MM-FI2
Fault injector for Microcontrollers

Currently, the only supported CPU is the Cortex-M0 what runs on the Raspberry Pi Pico. 

The program uses the dual core functionality that runs the fault injection program on the first core. The second core runs the target program and is monitored by the first core. 
