#ifndef CSVPARSER_H
#define CSVPARSER_H 1

#include <cstring>
#include <fstream>
#include <stdio.h>
#include <vector>

class CSVParser{
protected:
	bool eol = false;
	char* pos;
	std::vector<char> buffer;
public:
	bool is_eol();
	bool Open(const char* fileName);
	const char* GetNextValue();
	const char* GetNextLine();
};

#endif // CSVPARSER_H
