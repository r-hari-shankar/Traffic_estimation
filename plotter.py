import matplotlib.pyplot as plt


file = open("out.txt", "r")
xvalues = []
y1values = [] 
y2values = []

for line in file:
    a = line.split()
    y1values.append(a[1])
    y2values.append(a[2])

for i in range(len(y1values)):
    xvalues.append(1*(i+1)/15)

plt.plot(xvalues, y1values, label = "queue density")
plt.plot(xvalues, y2values, label = "dynamic density")
plt.xlabel("time")
plt.ylabel("densities")
plt.legend()
plt.show()
