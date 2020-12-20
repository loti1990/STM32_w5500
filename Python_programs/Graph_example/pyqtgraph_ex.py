
#standard lib
import threading
from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
from pyqtgraph.dockarea import *
import numpy as np
import sys
import time

#self created lib
import serial_setup as ss
import socket_setup as sc

#enable disable DEBUG
DEBUG = 0

GRAPH_LEN = 2048*5

#serial1 = ss.SerialSetup(baudrate = 115200, com_port = "/dev/ttyUSB0", timeout = 0.5)
TCP_conn = sc.W5500Conn("192.168.1.100",1024)

class Gui(QtGui.QMainWindow):

	def __init__(self):
		super(Gui,self).__init__()
		self.workerContinuouse  = WorkThreadContinuouse()

		self.adcData 		= ([])

		self.initGui()

	def initGui(self):
		area = DockArea()
		self.setCentralWidget(area)
		##Dock
		d2 = Dock("Graph", size=(1000, 50))


		area.addDock(d2, 'top')

		##Widget
		w2 = pg.LayoutWidget()
		#set font
		font = QtGui.QFont()
		font.setBold(True)

		##continuous sample mode
		self.continuousModeLable = QtGui.QLabel("Continuous sample data:")
		self.continuousModeLable.setFont(font)
		w2.addWidget(self.continuousModeLable, row=2, col=0)

		##continuouse data sample start pb
		self.continuouseDataStartPb       = QtGui.QPushButton("Start")
		self.continuouseDataStartPb.setFixedWidth(90)
		self.continuouseDataStartPb.setFixedHeight(30)
		self.continuouseDataStartPb.clicked.connect(self.startContinuouseDownload)
		w2.addWidget(self.continuouseDataStartPb , row=3, col=0)

		##continuouse data sample stop pb
		self.continuouseDataStopPb       = QtGui.QPushButton("Stop")
		self.continuouseDataStopPb.setFixedWidth(90)
		self.continuouseDataStopPb.setFixedHeight(30)
		self.continuouseDataStopPb.clicked.connect(self.stopRuningContinuouse)
		self.continuouseDataStopPb.setEnabled(False)
		w2.addWidget(self.continuouseDataStopPb , row=3, col=1)
		d2.addWidget(w2)

		##Graph preasure
		pwPreas = pg.PlotWidget(name='ADC Value')
		pwPreas.setTitle(title = "ADC Value")
		pwPreas.setLabel('left', 'Value', units='bits')
		pwPreas.setLabel('bottom', 'Samples')
		self.p1 = pwPreas.plot(title="ADC_value")
		self.p1.setPen((200,200,100))
		d2.addWidget(pwPreas)

		##Sensor 1 fft
#		pwFFTS1 = pg.PlotWidget(name='Plot2')
#		pwFFTS1.setTitle(title = "Sensor1 FFT")
#		pwFFTS1.setLabel('left', 'Y', units='X')
#		pwFFTS1.setLabel('bottom', 'X')
#		self.p3 = pwFFTS1.plot(title="TEMPERATURE")
#		self.p3.setPen((200,200,100))
#		d2.addWidget(pwFFTS1)

		##Graph temperature
#		pwTemp = pg.PlotWidget(name='Plot2')
#		pwTemp.setTitle(title = "Sensor2")
#		pwTemp.setLabel('left', 'Value', units='bits')
#		pwTemp.setLabel('bottom', 'Samples')
#		self.p2 = pwTemp.plot(title="TEMPERATURE")
#		self.p2.setPen((200,200,100))
#		d2.addWidget(pwTemp)

		##Sensor 2 fft
#		pwFFTS2 = pg.PlotWidget(name='Plot2')
#		pwFFTS2.setTitle(title = "Sensor2 FFT")
#		pwFFTS2.setLabel('left', 'Y', units='X')
#		pwFFTS2.setLabel('bottom', 'X')
#		self.p4 = pwFFTS2.plot(title="TEMPERATURE")
#		self.p4.setPen((200,200,100))
#		d2.addWidget(pwFFTS2)


		#Setup main window
		self.setGeometry(300, 300, 600, 600)
		self.setWindowTitle('READ ADC DATA FROM STM32')
		self.show()
		if(TCP_conn.OpenTCP()):
			if DEBUG:
				print("Connected")
		else:
			self.continuouseDataStopPb.setEnabled(False)
			self.continuouseDataStartPb.setEnabled(False)


		#Connections between threads
		#Good example on treading signals
		#https://gitlab.com/aleksandaratanasov/pyqt_threaded_ui/blob/master/threaded_ui.py
		self.workerContinuouse.finished.connect(self.terminateWorkerContin)
		self.workerContinuouse.updating.connect(self.updateGraph)
		self.workerContinuouse.dataContin.connect(self.dataContinuouse)

	def dataContinuouse(self,adc_data):
		#temperature = (((3.0*(float)temp/4095.0)-0.76)/0.0025)+25.0;
		#temperature = ((((3.0*adc_data)/4096.0)-0.76)/0.0025)+25.0
		#print(temperature)
		voltage = (3./4096)*adc_data
		if(len(self.adcData) > GRAPH_LEN):
			self.adcData.pop(0)
			self.adcData.append(voltage)
		else:
			self.adcData.append(voltage)

	#Excecute if start PB was clicked
	def startContinuouseDownload(self):
		self.adcData = ([])
		self.continuouseDataStartPb.setEnabled(False)
		self.continuouseDataStopPb.setEnabled(True)
		self.runContinuouse = 1
		self.workerContinuouse.setRun(runFlag = 1)
		self.workerContinuouse.start()

	#Excecute if stop PB was clicked
	def stopRuningContinuouse(self):
		try:
			self.continuouseDataStopPb.setEnabled(False)
			self.continuouseDataStartPb.setEnabled(True)
			self.runContinuouse = 0
			self.workerContinuouse.setRun(runFlag = 0)
		except:
			self.workerContinuouse.terminate()
			self.workerContinuouse.quit()

	#Terminate worker
	def terminateWorkerContin(self):
		if(DEBUG):
			print("Finished worker continuouse")

	#	try:
	#		self.workerContinuouse.terminate()
	#		self.workerContinuouse.quit()
	#	except:
	#		if(DEBUG):
	#			print("Problem in thread termination")

	#Update graph
	def updateGraph(self):

		self.p1.setData(self.adcData)
		#self.p3.setData(self.fftData[0:95])
		#self.p2.setData(self.rawData2)
		#self.p4.setData(self.fftData2[0:95])

		#self.rawData = ([])
		#self.rawData2 = ([])
		#self.fftData  = ([])
		#self.fftData2 = ([])

	#Close event "when x in the right corner of main window was pressed"
	def closeEvent(self,event):

		result = QtGui.QMessageBox.question(self,
			"Confirm Exit...",
			"Are you sure you want to exit ?",
			QtGui.QMessageBox.Yes| QtGui.QMessageBox.No)
		event.ignore()

		if result == QtGui.QMessageBox.Yes:
			event.accept()

		if(self.runContinuouse):
			self.workerContinuouse.setRun(runFlag = 0)

		try:
			#ser1.closeSerial()
			TCP_conn.CloseTCP()
		except:
			if DEBUG:
				print("TCP unable to close closeEvent")



class WorkThreadContinuouse(QtCore.QThread):
	updating 		= QtCore.pyqtSignal(name = "updating")
	dataContin 		= QtCore.pyqtSignal(int,name = "data_contin")
	def __init__(self, parent = None):
		#QtCore.QThread.__init__(self, parent)
		super(WorkThreadContinuouse,self).__init__(parent)

		self.runFlag            = 1
		self.rawADC             = ([])

	def __del__(self):
		self.quit()
		self.wait()

	def setRun(self,runFlag):
		if(runFlag):
			TCP_conn.SendData(b'0')
		else:
			TCP_conn.SendData(b'1')
		self.runFlag = runFlag


	def run(self):
		while self.runFlag:
			#try:
			#serial1.flushInputData()
			#time.sleep(0.5)
			#TCP_conn.SendData(b'0')
			#time1 = time.time()

			self.rawADC = TCP_conn.ReceiveData(2048)
			data = []
			#print(self.rawADC)
			#for i in self.rawADC:
			#	data.append(int(ord(i)))

			for i in range(0,len(self.rawADC),2):
				data.append(int(self.rawADC[i] | self.rawADC[i+1]<<8))

			for i in data:
				#print(i)
				self.dataContin.emit(i)
			#time2 = time.time()
			#print(len(self.rawADC)/(time2-time1)/10e3)
			self.updating.emit()
			#except:
                	#	print("error")
                	#	pass


def main():
	app = QtGui.QApplication(sys.argv)
	ex = Gui()
	app.exec_()


if __name__ == '__main__':
	main()
