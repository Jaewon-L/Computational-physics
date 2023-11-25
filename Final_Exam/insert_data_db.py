import sqlite3 as mdb
import sys
import os
import time
import random

#Check if the ifle 'data.db' exists
valid = os.path.isfile('data.db')

#If the file' data.db' exists
if(valid):
	#Connect to the SQLite database 'data.db'
	con = mdb.connect('data.db')
	#Create a cursor object
	cur = con.cursor()
	#Open the file 'run_number_save.txt' in read mode
	with open('run_number_save.txt', 'r') as file:
		#Read all lines in the file
		lines = file.readlines()

	#Loop through each line in the lines
	for line in lines:
		#Convert the line to an integer and store it in run_number
		run_number = int(line)
		#Print the run_number
		print("run number: {}".format(run_number))
	
	#An infinite loop
	while True:
		#Generate a random integer between 1 and 10
		data_value = random.randint(1,10)
		#Print the generated random number
		print("data value: {}".format(data_value))
		#Prepare a SQL command
		cmdd = "insert into Data (ID, int_val) values (%d, %d)"%(run_number, data_value)
		#Execute the SQL command
		cur.execute(cmdd)
		#Commit the transaction
		con.commit()

		#Sleep for 2 seconds
		time.sleep(2)

else:
	print('Wrong db name')
