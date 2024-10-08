// set compiler flat to enable use of strcpy
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdint>

using namespace std;

#ifndef PERSONAL
#define PERSONAL

class Personal {
public:
	Personal();
	Personal(char*, char*, char*, int, int32_t);
	void writeToFile(fstream&) const;
	void writeNullToFile(fstream&) const;
	void readFromFile(fstream&);
	void readKey();
	int size() const {
		return 9 + nameLen + cityLen + sizeof(year)+sizeof(salary);
	}
	bool isNull() {
		return isdigit(SSN[0]) == 0;
	}
	bool operator==(const Personal& pr) const {
		return strncmp(pr.SSN, SSN, 9) == 0;
	}
protected:
	const int nameLen, cityLen;
	char SSN[9], *name, *city;
	int year;
	int32_t salary;
	ostream& writeLegibly(ostream&);
	friend ostream& operator<<(ostream& out, Personal& pr) {
		return pr.writeLegibly(out);
	}
	istream& readFromConsole(istream&);
	friend istream& operator>>(istream& in, Personal& pr) {
		return pr.readFromConsole(in);
	}
};

#endif
