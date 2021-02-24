
CC = g++
CFLAGS = `pkg-config --cflags opencv4`
LIBS = `pkg-config --libs opencv4`

driver : driverCode.cpp
	g++ driverCode.cpp -o ImageCropper.out -pthread -std=c++11 `pkg-config --cflags --libs opencv4`

