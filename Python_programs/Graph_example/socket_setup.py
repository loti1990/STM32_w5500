import socket
import time
import numpy as np

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
			return 1
		except socket.error as e:
			print("[-] Fail to open connection on:\nIP: %s\nPORT: %s\nERROR: %s"%(self.ip,self.port,e))
			return 0

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

