import serial

ser = serial.Serial('/dev/ttyUSB0', baudrate=115200, timeout=0.5)  # open serial port
print(ser.name)         # check which port was really opened

while(1):

	try:
		data = ser.read(1)
		#print("Data: %b"%(data.decode()))
		if(data != b''):
			print(data)

	except serial.SerialTimeoutException as e:
		print("Timeout %s"%e)
	#	pass

	except KeyboardInterrupt:
		ser.close()
		break

ser.close()
#while(1):
#	ser.flushInput()
#	ser.flushOutput()
#	ser.write(b'00011110')     	# write a string
#	data = ser.read(2)
#	adc_val = data[1]<<8|data[0]
#	voltage = (3./2**12)*adc_val
#	print("Voltage: %.2f"%(voltage))
#ser.close()             # close port
