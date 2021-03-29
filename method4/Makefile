
CC = g++
CFLAGS = `pkg-config --cflags opencv4`
LIBS = `pkg-config --libs opencv4`

all : video.cpp
	$(CC) modifierFunctions.cpp -o modifier.out bgEditor.cpp -o bgEditor.out video.cpp -o traffic_density.out -pthread -std=c++11 `pkg-config --cflags --libs opencv4`

plot : 
	python3 plotter.py
clean  :
	$(RM) *.out 

