import matplotlib.pyplot as plt
import numpy as np

#Load the data from the text file. The data is expected to be in a format where values are separated by commas.
data = np.loadtxt('data_values.txt', delimiter = ',')

#The data is assumed to be in two columns. The first column (index 0) represents the x-values and the second column (index 1) represents the y-values.
x = data[:, 0]
y = data[:, 1]

#drawing plot
plt.plot(x, y)

plt.xlabel('saved order')
plt.ylabel('saved number')
plt.title('Graph from txt file')

plt.show()
