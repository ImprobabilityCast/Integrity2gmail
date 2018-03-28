OBJS = main.o CSVParser.o
CXXFLAGS = -Wall -shared-libgcc -std=c++11

Integrity2gmail.exe : $(OBJS) CSVParser.h
	g++ -o Integrity2gmail.exe $(OBJS)
main.o : main.cpp CSVParser.cpp CSVParser.h
	g++ $(CXXFLAGS) -c main.cpp
CSVParser.o : CSVParser.cpp CSVParser.h
	g++ $(CXXFLAGS) -c CSVParser.cpp

.PHONY: clean

clean :
	rm -vf $(OBJS)
