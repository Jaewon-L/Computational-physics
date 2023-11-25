import sqlite3 as mdb

con = mdb.connect('data.db')
cur = con.cursor()

#Get a run number from the user as an integer input
run_number = int(input("Enter the run number: "))
#Prepare a SQL command to select all rows from the 'Data' table where the ID is equal to the run number
cmd = "select * from Data where ID=%d"%(run_number,)
#Execute the SQL command
cur.execute(cmd)

#Fetch all the rows as a list of tuples from the 'Data' table where the ID equals the run number
data_rows = cur.fetchall()

#Create a list of x values as sequential integers starting from 0 up to the length of the data_rows
x = [i for i in range(len(data_rows))]
#Create a list of y values by extracting the second element from each tuple in data_rows
y = [row[1] for row in data_rows]

#Open the file 'data_values.txt' in write mode
with open('data_values.txt', 'w') as f:
	#Write x and y values into the file 'data_values.txt' line by line, separated by a comma
	for x_val, y_val in zip(x,y):
		f.write("{}, {}\n".format(x_val, y_val))

#Close the database connection
con.close()
