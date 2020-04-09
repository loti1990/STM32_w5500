import socket
import time
import numpy as np
IP 	= '192.168.1.100'
#IP 	= '172.17.10.96'
PORT 	= 1024


class W5500Conn():

	def __init__(self,ip,port):
		self.ip 	= ip
		self.port 	= port

	def OpenTCP(self):

		try:
			self.s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
			self.s.settimeout(5) 	#timeout 5s
		#	self.s.setsockopt(socket.SOL_SOCKET,socket.SO_RCVBUF, 100000)
			self.s.connect((self.ip,self.port))
			self.s.settimeout(None) #reset timeout to default
			print("[+] Susesfully connect to:\nIP: %s\nPORT: %s"%(self.ip,self.port))
		except socket.error as e:
			print("[-] Fail to open connection on:\nIP: %s\nPORT: %s\nERROR: %s"%(self.ip,self.port,e))

	def CloseTCP(self):

		try:
			self.s.close()
			print("[+] Susesfully close connection on:\nIP: %s\nPORT: %s"%(self.ip,self.port))

		except socket.error as e:
			print("[-] Fail to close connection on:\nIP: %s\nPORT: %s\nERROR: %s"%(self.ip,self.port,e))

	def ReceiveData(self,data_len):
		try:

			#self.s.settimeout(5) 	#timeout 5s
			#recv_data = self.s.recv(data_len)
			#self.s.settimeout(None) #reset timeout to default
			return(self.s.recv(data_len))

		except socket.error as e:

			print("[-] Fail to receive data from:\nIP: %s\nPORT: %s\nERROR: %s"%(self.ip,self.port,e))

	def SendData(self,data):

		try:

			flag = self.s.send(data)
			if(flag == 0):
				print("Error sending data")
			#self.s.sendall(data)
		except socket.error as e:

			print("[-] Fail to send data to:\nIP: %s\nPORT: %s\nERROR: %s"%(self.ip,self.port,e))

def main():


	speed_samples_down = []
	speed_samples_up = []
	a = W5500Conn(ip = IP, port = PORT)
	a.OpenTCP()
	data = ""
	for i in range(1):
		data = data + "0"
	data = data.encode()

	for i in range(10):
		start_time = time.time()
		a.SendData(data)
		speed_samples_up.append((1)/(time.time()-start_time)/1e6)
		#time.sleep(0.001)
		start_time2 = time.time()
		print(a.ReceiveData(2048))
		speed_samples_down.append((2048)/(time.time()-start_time2)/1e6)

	print("Upload: %.2f Mbit/s"%np.average(speed_samples_up))
	print("Down: %.2f Mbit/s"%np.average(speed_samples_down))
	time.sleep(0.5)

	a.CloseTCP()

#Run main proram
if(__name__ == "__main__"):

	main()
