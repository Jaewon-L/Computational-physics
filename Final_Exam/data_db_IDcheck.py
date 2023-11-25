import os
import sqlite3 as mdb


valid = os.path.isfile('data.db')

if(valid):
	#Connect to the database
	con = mdb.connect('data.db')
	cur = con.cursor()

	#Execute a query to fetch all IDs form the table
	cur.execute("select distinct ID from Data")

	#fetch all rows from the last executed statement
	rows = cur.fetchall()

	#Iterate over the rows and print each ID
	for row in rows:
		row = row[0]
		cur.execute("select count(*) from Data where ID=%d"%(row))
		count = cur.fetchone()[0]
		print("ID that currnetly exists: {}, Count: {}".format(row, count))

else:
	print('Wrong db name')

con.close()
