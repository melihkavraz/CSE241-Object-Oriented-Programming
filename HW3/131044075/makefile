all: main

main: main.o CPU.o CPUProgram.o
	g++ main.o CPU.o CPUProgram.o -o exe

main.o: main.cpp CPU.h
	g++ -std=c++11 -c main.cpp

CPU.o: CPU.cpp CPU.h
	g++ -std=c++11 -c CPU.cpp

CPUProgram.o: CPUProgram.cpp CPUProgram.h
	g++ -std=c++11 -c CPUProgram.cpp

clean:
	rm -rf main.o CPU.o CPUProgram.o exe
