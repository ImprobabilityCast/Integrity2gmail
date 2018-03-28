OBJS = main.o CSVParser.o
CXXFLAGS = -Wall -shared-libgcc -std=c++11

toCSVgmail.exe : $(OBJS) CSVParser.h
	g++ -o toCSVgmail.exe $(OBJS)
main.o : main.cpp CSVParser.cpp CSVParser.h
	g++ $(CXXFLAGS) -c main.cpp
CSVParser.o : CSVParser.cpp CSVParser.h
	g++ $(CXXFLAGS) -c CSVParser.cpp

.PHONY: clean

clean :
	rm -vf $(OBJS)
