import numpy as np

a = 3.0
N = 20.0

x = np.ones(N)
y = np.full(N, 4)

z = a * x + y

with open("output_python.txt", "w") as file:
	file.write(f"z = {z}")