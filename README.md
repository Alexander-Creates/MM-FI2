# Fault injector for Microcontrollers
This is a fault injector software that is heavily inspired by the Carol-FI fault injector:
https://github.com/UFRGS-CAROL/carol-fi

Currently, the only supported CPU is the Cortex-M0 what runs on the Raspberry Pi Pico. 

The program uses the dual core functionality that runs the fault injection program on the first core. The second core runs the target program and is monitored by the first core. 


To run the program, change the CMakeLists.txt file and change this line: set(PICO_SDK_PATH "set directory to Pico SDK path") to include the Pico SDK directory.
cd into /build and run cmake ..
run make
