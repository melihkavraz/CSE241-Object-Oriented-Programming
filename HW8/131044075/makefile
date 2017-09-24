JFLAGS = -g
JC = javac
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
	Bigram.java \
	BigramDyn.java \
	BigramMap.java \
	myExceptions.java\
	Pair.java\
	_mainTester.java 


classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class
