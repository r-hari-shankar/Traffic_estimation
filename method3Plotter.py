from matplotlib import colors
import matplotlib.pyplot as plt
import matplotlib as mpl
import itertools

mpl.rc("lines", linewidth = 2)
plt.figure(figsize=(10,10))

file1 = open("baseline.txt", "r")

baseline = []
xvalues = []

for line in file1:
    a = line.split()
    baseline.append(float(a[1]))

for i in range(len(baseline)):
    xvalues.append(1*(i+1)/15)

file1.close()

plt.figure(0)
plt.plot(xvalues, baseline, label = "1 core", color = 'orange')

utility = []
runtime = []

for j in range(2,9):
    file1 = open("m2c" + str(j) + ".txt", "r")
    yvalues = []
    util = 0
    i = 0
    for line in file1:
        a = line.split()
        if(len(a) != 2):
            runtime.append(float(a[-1]))
            break
        util += abs(float(a[1]) - baseline[i])
        i += 1
        yvalues.append(float(a[1]))
    
    utility.append(util/i)
    plt.figure(0)
    plt.plot(xvalues, yvalues, label = str(j)+" core")
    file1.close()

plt.figure(0)
plt.legend()
plt.savefig("method3Plots.png")
plt.show()

plt.figure(1)
fig, axs = plt.subplots(3, figsize = (15,15))
fig.suptitle("Graphs for method 3")
axs[1].plot([2,3,4,5,6,7,8], utility)
axs[1].set(ylabel= 'utility', xlabel= 'parameter')
axs[1].set_title("Parameter-utility graph")
axs[2].plot([2,3,4,5,6,7,8], runtime)
axs[2].set(ylabel= 'runtime', xlabel= 'parameter')
axs[2].set_title("Parameter-Runtime graph")
lists = sorted(itertools.izip(*[runtime, utility]))
runtime, utility = list(itertools.izip(*lists))
axs[0].plot(runtime, utility)
axs[0].set(ylabel = "utility", xlabel= "runtime")
plt.savefig("m3_runtime-utilPlot.png")
plt.show()






