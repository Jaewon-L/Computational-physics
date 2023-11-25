import sqlite3 as mdb
import sys
import os
import time

#Check if the file 'summary.db' exists
valid = os.path.isfile('summary.db')

if (valid):
	con = mdb.connect('summary.db')
	cur = con.cursor()
	#Prepare a SQL command to select the ID of the latest entry in the Timecheck table
	cmd = 'select ID from Timecheck order by ID desc limit 1'
	#Execute the SQL command
	cur.execute(cmd)
	#Fetch the first (and only) row of the results, which is the ID of the latest entry
	row = cur.fetchone()
	#print(row)
	print("time run_number: {}".format(row[0]))
	#Get the current time in the format Year-Month-Day Hour:Minute:Second
	current_time = time.strftime("%Y-%m-%d %H:%M:%S")
	print("end time: {}".format(current_time))
	
	#Prepare a SQL command to update the time2 field of the latest entry in the Timecheck table with the current time
	cmd = "update Timecheck set time2='%s' where ID=%d"%(current_time, row[0])
	cur.execute(cmd)
	con.commit()

#If the file 'summary.db' does not exist
else:
	print('Wrong db name')
