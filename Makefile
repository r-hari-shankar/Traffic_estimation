
CC = g++
CFLAGS = `pkg-config --cflags opencv4`
LIBS = `pkg-config --libs opencv4`

all : driverCode.cpp
	$(CC) modifierFunctions.cpp -o modifier.out driverCode.cpp -o traffic_estimation.out -pthread -std=c++11 `pkg-config --cflags --libs opencv4`

clean  :
	$(RM) *.out 

