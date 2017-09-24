all: main

main: _mainTester.o CPU.o CPUProgram.o Memory.o Computer.o 
	g++ _mainTester.o CPU.o CPUProgram.o Memory.o Computer.o -o exe

_mainTester.o: _mainTester.cpp requiredIncs.h
	g++ -std=c++11 -c _mainTester.cpp

CPU.o: CPU.cpp CPU.h
	g++ -std=c++11 -c CPU.cpp

CPUProgram.o: CPUProgram.cpp CPUProgram.h
	g++ -std=c++11 -c CPUProgram.cpp

Memory.o: Memory.cpp Memory.h
	g++ -std=c++11 -c Memory.cpp

Computer.o: Computer.cpp Computer.h
	g++ -std=c++11 -c Computer.cpp

clean:
	rm -rf _mainTester.o CPU.o CPUProgram.o Memory.o Computer.o exe
