/*
Integrity    Google
name (f l) = Name (l, f)
First Name = Given Name
           = Additional Name (mid initial)
Last Name  = Family Name
lable      = Notes
E-mail Address = E-mail 1 - Value
*/

#include "CSVParser.h"

//#define DEBUG 1

void printHelp() {
	printf("toCSVgmail v1.0.1 March 2018\n"
	"Converts an address book exported as a CSV file from integrity.com\n"
	"(an obscure Internet provider) to the format expected by gmail for\n"
    "importing address books. The output file will be called 'gmail.csv'\n\n"
	"Usage:\ttoCSVgmail FILE\n\n"
	"FILE:\tRequired.  The file to convert.\n\n"
	);
}

int main(int argc, char* argv[]) {
	if (argc != 2 || 0 == strcmp(argv[1], "--help")) {
		printHelp();
		return 0;
	}
    
	CSVParser parser;
	const char* header = "Name,Given Name,Additional Name,Family Name,"
		"Yomi Name,Given Name Yomi,Additional Name Yomi,"
		"Family Name Yomi,Name Prefix,Name Suffix,Initials,Nickname,"
		"Short Name,Maiden Name,Birthday,Gender,Location,"
		"Billing Information,Directory Server,Mileage,Occupation,Hobby,"
		"Sensitivity,Priority,Subject,Notes,Group Membership,"
		"E-mail 1 - Type,E-mail 1 - Value";

	if (!parser.Open(argv[1])) {
		printf("Could not open file: %s", argv[1]);
		return 2;
	}
	std::ofstream ofile ("gmail.csv");
	if (!ofile.is_open()) {
		printf("Could not save file");
		return 3;
	}
	ofile.write(header, strlen(header));
	ofile.write("\n", 1);
#ifdef DEBUG
	printf("%s\n", header);
#endif
	while (parser.GetNextLine() != NULL) {
		for(int i=0; i<5; i++) {
			const char* ptr = parser.GetNextValue();
			if (ptr == NULL)
				break;
#ifdef DEBUG
			if (i == 3) printf(",");
#endif
			if (i == 3) ofile.write(",", 1);
			if (i == 4) {
				const char* infoLabel = parser.GetNextValue();
#ifdef DEBUG
				printf(",,,,,,,,,,,,,,,,,,,,,,%s,* My Contacts,* ,%s",
						infoLabel, ptr);
#endif
				const char* str = ",,,,,,,,,,,,,,,,,,,,,,";
				ofile.write(str, strlen(str));
				ofile.write(infoLabel, strlen(infoLabel));
				str = ",* My Contacts,* ,";
				ofile.write(str, strlen(str));
				ofile.write(ptr, strlen(ptr));
				break;
			}
			// this is to make sure lines don't end with commas
#ifdef DEBUG
			if (i > 1) printf(",");
			if (i != 0) printf("%s", ptr);
#endif
			if (i > 1) ofile.write(",", 1);
			if (i != 0) ofile.write(ptr, strlen(ptr));
		}
#ifdef DEBUG
		printf("\n");
#endif
		ofile.write("\n", 1);
	}
	return 0;
}
