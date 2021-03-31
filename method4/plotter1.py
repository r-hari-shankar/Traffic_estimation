import matplotlib.pyplot as plt


file = open("core_runtime.txt", "r")
xvalues = []
y1values = [] 
y2values = []

for line in file:
    a = line.split()
    xvalues.append(int(a[0]))
    y1values.append(int(a[1]))
    #y2values.append(a[2])

plt.plot(xvalues, y1values, label = "num of thread vs runtime")
#plt.plot(xvalues, y2values, label = "dynamic density")
plt.xlabel("Number of threads")
plt.ylabel("runtime")
plt.legend()
plt.savefig("threadvsruntime.png")
plt.show()