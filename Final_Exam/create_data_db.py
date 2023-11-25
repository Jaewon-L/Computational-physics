import sqlite3 as mdb
import sys

#Create a connection to the SQLite database.
#If the database specified in teh arguement does not exist, SQLite will create it.
con = mdb.connect('data.db')

#Using the connection, we get the cursor object. The cursor is used to traverse the records from the result set.
with con:
	cur = con.cursor()
	#Drop the table named Data if it exists in the database.
	cur.execute("DROP TABLE IF EXISTS Data")

	#Define a SQL command to create a new table named Data. 
	#This table contains three fields: ID (integer), int_val (integer).
	cmd = 'CREATE TABLE Data (\
	ID INTEGER,\
	int_val INTEGER)'
	
	#Execute the SQL command to create the table
	cur.execute(cmd)

