import sqlite3 as mdb
import sys
import os
import time

#Check if the file 'summary.db' exists
valid = os.path.isfile('summary.db')

#If the file 'summary.db' exists
if(valid):
	#Connect to the SQLite database 'summary.db'
	con = mdb.connect('summary.db')
	#Create a cursor object
	cur = con.cursor()
	#Get the current time in the format Year-Month-Day Hour:Minute:Second
	current_time = time.strftime("%Y-%m-%d %H:%M:%S")
	print("start time: {}".format(current_time))
	#Prepare a SQL insert command to insert the current time into the Timecheck table
	cmd = "insert into Timecheck (time1) values('%s')"%(current_time)
	#Execute the SQL command
	cur.execute(cmd)
	#Commit the transaction
	con.commit()

#If the file 'summary.db' does not exist
else:
	print('Wrong db name')
