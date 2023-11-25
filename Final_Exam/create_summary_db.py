#Import the sqlite3 module.
import sqlite3 as mdb
import sys #The sys module provides access to some variables used or maintained by the Python interpreter and to funtions that interact with the interpreter.

#Create a connection to the SQLite3 database.
#If the database specified in the argument does not exist, SQLite will create it.
con = mdb.connect('summary.db')

#Using the connection, we get the cursor object. The cursor is used to traverse the records from the result set.
with con:
	cur = con.cursor()
	#Drop the talbe named Timecheck if it exists in the database.
	cur.execute("DROP TABLE IF EXISTS Timecheck")

	#Define a SQL command to create a new table named Timecheck.
	#This table contains three fields: ID (integer and primary key), time1 (text), and time2 (text).
	cmd = 'CREATE TABLE Timecheck (\
	ID INTEGER PRIMARY KEY AUTOINCREMENT,\
	time1 TEXT,\
	time2 TEXT)'

	#Execute the SQL command to create the table
	cur.execute(cmd)
