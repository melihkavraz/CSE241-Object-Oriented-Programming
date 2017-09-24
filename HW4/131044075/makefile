all: main

main: main.o CPU.o CPUProgram.o Memory.o Computer.o
	g++ main.o CPU.o CPUProgram.o Memory.o Computer.o -o exe

main.o: main.cpp CPU.h
	g++ -std=c++11 -c main.cpp

CPU.o: CPU.cpp CPU.h
	g++ -std=c++11 -c CPU.cpp

CPUProgram.o: CPUProgram.cpp CPUProgram.h
	g++ -std=c++11 -c CPUProgram.cpp

Memory.o: Memory.cpp Memory.h
	g++ -std=c++11 -c Memory.cpp

Computer.o: Computer.cpp Computer.h
	g++ -std=c++11 -c Computer.cpp

clean:
	rm -rf main.o CPU.o CPUProgram.o Memory.o Computer.o exe
