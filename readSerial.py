import serial
import time

# create SDC and hangs
# How can I create DUEs and hangs?


address = "/dev/ttyACM0"
port = 115200

fname = "results.txt"
fmode = "a"
iterations = 1000
ser = serial.Serial(address, port)  

with ser as port, open(fname, fmode) as outf:
    print("Running ", iterations, "iterations: \n" )
    for i in range(iterations + 1):
        message = ser.read(ser.inWaiting()).decode("utf-8") # inWaiting- get the number of bytes in the inout buffer
        print(message)
        outf.write(message)
        outf.flush()
        time.sleep(1)
