all: main

main: _mainTester.o BigramDyn.o BigramMap.o 
	g++ _mainTester.o BigramDyn.o BigramMap.o  -o exe

_mainTester.o: _mainTester.cpp 
	g++ -std=c++11 -c _mainTester.cpp

Bigram.o: _mainTester.cpp Bigram.h
	g++ -std=c++11 -c _mainTester.cpp

BigramDyn.o: BigramDyn.cpp BigramDyn.h
	g++ -std=c++11 -c BigramDyn.cpp

BigramMap.o: BigramMap.cpp BigramMap.h
	g++ -std=c++11 -c BigramMap.cpp

clean:
	rm -rf _mainTester.o BigramDyn.o BigramMap.o Bigram.o exe
