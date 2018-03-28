#include "CSVParser.h"

bool CSVParser::Open(const char* fileName) {
	std::ifstream ifile (fileName);
	if (!ifile.is_open())
		return false;
	buffer = std::vector<char>(	(std::istreambuf_iterator<char>(ifile)),
								std::istreambuf_iterator<char>()	);
	buffer.push_back('\0');
	pos = strtok(buffer.data(), "\r\n");
	return true;
}

bool CSVParser::is_eol() { return eol; }

const char* CSVParser::GetNextValue() {
	if (eol) return NULL;
	char* endPos, *tmp;
	if (*pos == '"') {
		tmp = pos;
		while (true) {
			tmp = strchr(tmp+1, '"');
			if (tmp == NULL) {
				printf("Parsing Error: Expected '\"'");
				return NULL;
			}
			// check to see if quote is escaped
			if (*(tmp-1) == '\\') tmp++;
			else break;
		}
		endPos = strchr(tmp, ',');
	} else
		endPos = strchr(pos, ',');
	// if it's the last value return the value and set pos to nulPos
	if (endPos == NULL) {
		eol = true;
		return pos;
	}
	*endPos = '\0';
	char* str = pos;
	pos = endPos+1;
	return str;
}

const char* CSVParser::GetNextLine() {
	pos = strtok(NULL, "\r\n");
	eol = (pos == NULL);
	return pos;	
}
