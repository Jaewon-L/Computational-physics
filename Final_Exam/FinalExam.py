#Import required package
import os
import sys
import subprocess
import random
import time
import signal
import matplotlib.pyplot as plt
from PyQt5.QtWidgets import *
from PyQt5.QtCore import QTimer

#Define a class ofr the application GUI
class JWLAPP(QWidget):
	#Constructor of the class
	def __init__(self):
		super().__init__()	# Call constructor of parent class QWidget
		self.initGUI()	# Call method to initialize the GUI
		self.proc = None #define proc property



	#Method to initialize the GUI
	def initGUI(self):
		self.resize(220,180)

		#Create a push button titled 'summary.db' and place it at (70,20)
		button_1 = QPushButton('summary.db', self)
		button_1.move(70,20)
		#Connect the click event of the button to the button_1_clicked() method
		button_1.clicked.connect(self.button_1_clicked)

		button_2 = QPushButton('data.db', self)
		button_2.move(70,60)
		button_2.clicked.connect(self.button_2_clicked)
		
		button_3 = QPushButton('start', self)
		button_3.move(20,100)
		button_3.clicked.connect(self.button_3_clicked)

		button_4 = QPushButton('stop', self)
		button_4.move(120,100)
		button_4.clicked.connect(self.button_4_clicked)

		button_5 = QPushButton('draw', self)
		button_5.move(70,140)
		button_5.clicked.connect(self.button_5_clicked)

	#Method to be exectued when button_1 is clicked
	def button_1_clicked(self):
		#Show a message box asking the user if they want to create a summary.db
		reply = QMessageBox.question(self, 'Message', 'Create a summary.db? Also, the existing database is deleted.', 
									QMessageBox.Yes | QMessageBox.No)

		#If the user clicked 'Yes'
		if reply == QMessageBox.Yes:
			#Run a Python2 script to create a summary.db
			subprocess.run(['python2', 'create_summary_db.py'])  
			#List the files in the current directory
			os.system('ls')

		#If the user clicked 'No', do nothing
		else:
			pass

	def button_2_clicked(self):
		reply = QMessageBox.question(self, 'Message', 'Create a data.db? Also, the existing database is deleted.', 
									QMessageBox.Yes | QMessageBox.No)

		if reply == QMessageBox.Yes:
			subprocess.run(['python2', 'create_data_db.py'])  
			#Initialises run_number to 1
			self.run_number = 1
			#Opens the file run_number_save.txt in write mode
			with open('run_number_save.txt', 'w') as file:
				#Writes the run number into the file
				file.write(str(self.run_number)) 
			os.system('ls')
			
		else:
			pass

	def button_3_clicked(self):
		reply = QMessageBox.question(self, 'Message', 'Do you want to start?',
									QMessageBox.Yes | QMessageBox.No)

		if reply == QMessageBox.Yes:		
			subprocess.Popen(['python2', 'insert_summary_db.py'])  
			self.proc = subprocess.Popen(['python2', 'insert_data_db.py'])  
			#Prints the PID of the newly created subprocess
			print(f"PID of subprocess: {self.proc.pid}")
			
			with open('run_number_save.txt', 'r') as file:
				lines = file.readlines()
			for line in lines:
				self.run_number = int(line)
		
		else:
			pass

	def button_4_clicked(self):
		if self.proc is None:
			QMessageBox.warning(self, 'Warning', 'You must click "start" before clicking "stop"!')
			return

		reply = QMessageBox.question(self, 'Message', 'Do you want to stop?',
									QMessageBox.Yes | QMessageBox.No)

		if reply == QMessageBox.Yes:
			subprocess.Popen(['python2', 'update_summary_db.py'])
			#Terminates the subprocess created in button_3_clicked() using its PID
			os.kill(self.proc.pid, signal.SIGTERM)	
			#Increments the run_number by 1
			self.run_number += 1
			#Opens the file run_number_save.txt in write mode
			with open('run_number_save.txt', 'w') as file:
				#Writes the incremented run number into the file
				file.write(str(self.run_number))
		else:
			pass

	def button_5_clicked(self):		
		reply = QMessageBox.question(self, 'Message', 'Did you check if the data file existed? If not, an error appears!', 
									QMessageBox.Yes | QMessageBox.No)

		subprocess.run(['python2', 'data_db_IDcheck.py'])
	
		if reply == QMessageBox.Yes:
			subprocess.run(['python2', 'save_data_db.py'])  
			subprocess.run(['python3.10', 'draw_data_db.py'])
		else:
			pass

	#It is a code that prevents data from being recorded continuously if the start button is pressed and the stop button is not pressed.
	def closeEvent(self, event):
		#Check if proc attribute is not None
		if self.proc is not None:
			#If it's not, then check if the process is still running
			if self.proc.poll() is None:
				reply = QMessageBox.question(self, 'Message', "A process is still running. Do you want to terminate it and exit?", 
											QMessageBox.Yes | QMessageBox.No)
			
				if reply == QMessageBox.Yes:
					subprocess.Popen(['python2', 'update_summary_db.py'])
					os.kill(self.proc.pid, signal.SIGTERM)
					self.run_number += 1
					with open('run_number_save.txt', 'w') as file:
						file.write(str(self.run_number))
					#Let the window close
					event.accept()
				else:
					#Don't let the window close
					event.ignore()
			else:
				event.accept()
		else:
			event.accept()


#Check if the script is being run directly
if __name__ == '__main__':
	#Create a new QApplication instance
	app = QApplication(sys.argv)

	#Create an instance of the application GUI
	myapp = JWLAPP()
	#Show the GUI
	myapp.show()

	#Execute the application's main loop
	app.exec()

