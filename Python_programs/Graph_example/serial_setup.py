import serial

#serial setup
class SerialSetup():

	def __init__(self, baudrate, com_port, timeout):

		self.connect = 0
		self.baudrate = baudrate
		self.com_port = com_port
		self.timeout = timeout

		try:
			self.ser = serial.Serial(self.com_port,self.baudrate,timeout = self.timeout)
			self. connect = 1

			if not self.ser.isOpen():
				self.ser.open()

		except serial.SerialException:
			print("CAN'T FIND %s SERIAL PORT"%(self.com_port))
			self. connect = 0

	def flushInputData(self):

		try:
			self.ser.flushInput()
			self.ser.flushOutput()
		except:
			pass

	def readData(self,numOfByts):

		try:
			return self.ser.read(numOfByts)

		except serial.SerialTimeoutException:
			if(DEBUG):
				print("Timeout")

	def writeData(self,data):

		try:
			self.ser.write(data)
		except:
			pass

	def serialOpen(self):
		return self.connect

	def getADCData(self):

		self.flushInputData()
		self.ser.write(b'01001001')
		temp = self.ser.read(2)
		return(temp[1]<<8|temp[0])

	def closeSerial(self):
		self.ser.close()
