
CC = g++
CFLAGS = `pkg-config --cflags opencv4`
LIBS = `pkg-config --libs opencv4`

all :
	$(CC) modifierFunctions.cpp -o modifier.out bgEditor.cpp -o bgEditor.out method3.cpp -o m3.out -pthread -std=c++11 `pkg-config --cflags --libs opencv4`
	$(CC) modifierFunctions.cpp -o modifier.out bgEditor.cpp -o bgEditor.out method1.cpp -o m1.out -pthread -std=c++11 `pkg-config --cflags --libs opencv4`
	$(CC) modifierFunctions.cpp -o modifier.out bgEditor.cpp -o bgEditor.out method2.cpp -o m2.out -pthread -std=c++11 `pkg-config --cflags --libs opencv4`
	$(CC) modifierFunctions.cpp -o modifier.out bgEditor.cpp -o bgEditor.out method4.cpp -o m4.out -pthread -std=c++11 `pkg-config --cflags --libs opencv4`

one:
    $(CC) modifierFunctions.cpp -o modifier.out bgEditor.cpp -o bgEditor.out method1.cpp -o m1.out -pthread -std=c++11 `pkg-config --cflags --libs opencv4`

two:
	$(CC) modifierFunctions.cpp -o modifier.out bgEditor.cpp -o bgEditor.out method2.cpp -o m2.out -pthread -std=c++11 `pkg-config --cflags --libs opencv4`

three:
	$(CC) modifierFunctions.cpp -o modifier.out bgEditor.cpp -o bgEditor.out method3.cpp -o m3.out -pthread -std=c++11 `pkg-config --cflags --libs opencv4`

four:
	$(CC) modifierFunctions.cpp -o modifier.out bgEditor.cpp -o bgEditor.out method4.cpp -o m4.out -pthread -std=c++11 `pkg-config --cflags --libs opencv4`

clean  :
	$(RM) *.out 

