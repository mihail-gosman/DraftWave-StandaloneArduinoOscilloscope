import struct
import time

import serial

serial_port = 'COM3'
baud_rate = 115200


ser = serial.Serial(serial_port, baud_rate, timeout=2)
ser.bytesize = 8
ser.stopbits = 1
ser.parity = 'N'

time.sleep(2)

try:
    while True:
        if ser.in_waiting > 0:
            # First, read the size of the array (1 byte)
            array_size = ser.read(1)  # Reading 1 byte (array size)
            array_size = ord(array_size)  # Convert byte to int

            # Now, read the integer values (each int is 2 bytes)
            raw_data = ser.read(array_size * 2)  # Read 2 bytes for each integer

            # Unpack the byte stream into a tuple of integers
            my_array = struct.unpack('h' * array_size, raw_data)  # 'h' is for short (2 bytes)

            # Print the received array
            print("Received array:", my_array)

except KeyboardInterrupt:
    print("\nProgram terminated by user.")

except Exception as e:
    print(f"Error: {e}")

finally:
    ser.close() # Close the serial connection when done