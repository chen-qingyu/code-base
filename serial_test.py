import serial
import binascii

ser = serial.Serial("COM6", 4800)
ser.close()
ser.open()
if ser.isOpen():
    print("OK, begin")

    data = binascii.a2b_hex("01")
    ser.write(data)
    print("Send:", data) # 0x01
    rec = ser.read()
    print("Receive:", rec) # 0x02

    data = binascii.a2b_hex("41") 
    ser.write(data)
    print("Send:", data) # "A"
    rec = ser.read()
    print("Receive:", rec) # "B"

    data = binascii.a2b_hex("61")
    ser.write(data)
    print("Send:", data) # "a"
    rec = ser.read()
    print("Receive:", rec) # "b"
