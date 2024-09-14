import time

import serial

serial_port = 'COM3'
baud_rate = 115200


ser = serial.Serial(serial_port, baud_rate, timeout=2)

time.sleep(2)

try:
    while True:
        # Read a line from the serial port
        if ser.in_waiting > 0: # Check if there is data waiting in the serial buffer
            line = ser.readline()#.decode('utf-8', errors='ignore')
            print(line) # Print the received data

except KeyboardInterrupt:
    print("\nProgram terminated by user.")

except Exception as e:
    print(f"Error: {e}")

finally:
    ser.close() # Close the serial connection when done