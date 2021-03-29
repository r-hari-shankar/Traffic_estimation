import matplotlib.pyplot as plt
import itertools

fig, axs = plt.subplots(3, figsize = (25,25))
fig.suptitle("Graphs for method 1")

file = open("method1.txt", "r")

param = []
util = []
runtime = []

for line in file:
    a = line.split()
    param.append(int(a[0]))
    util.append(float(a[1]))
    runtime.append(float(a[2]))

file.close()

axs[1].plot(param, util)
axs[1].set(ylabel= 'utility', xlabel= 'parameter')
axs[1].set_title("Parameter-utility graph")
axs[2].plot(param, runtime)
axs[2].set(ylabel= 'runtime', xlabel= 'parameter')
axs[2].set_title("Parameter-Runtime graph")

lists = sorted(itertools.izip(*[runtime, util]))
runtime, util = list(itertools.izip(*lists))

axs[0].plot(runtime, util)
axs[0].set(ylabel= 'utility', xlabel= 'runtime')
axs[0].set_title("utility-Runtime graph")

plt.savefig("m1.png")

