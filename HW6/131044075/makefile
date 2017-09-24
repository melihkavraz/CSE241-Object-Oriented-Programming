all: main

main: _mainTester.o CPU.o CPUProgramDyn.o Memory.o Computer.o 
	g++ _mainTester.o CPU.o CPUProgramDyn.o Memory.o Computer.o -o exe

_mainTester.o: _mainTester.cpp requiredIncs.h
	g++ -std=c++11 -c _mainTester.cpp

CPU.o: CPU.cpp CPU.h
	g++ -std=c++11 -c CPU.cpp

CPUProgramDyn.o: CPUProgramDyn.cpp CPUProgramDyn.h
	g++ -std=c++11 -c CPUProgramDyn.cpp

Memory.o: Memory.cpp Memory.h
	g++ -std=c++11 -c Memory.cpp

Computer.o: Computer.cpp Computer.h
	g++ -std=c++11 -c Computer.cpp

clean:
	rm -rf _mainTester.o CPU.o CPUProgramDyn.o Memory.o Computer.o exe
