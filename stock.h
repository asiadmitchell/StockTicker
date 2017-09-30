// do not change this file except to add private members

#pragma once

#include "date.h"

using namespace std;

class stock
{
public:
	stock(char const * const symbol, char const * const name, int sharePrice, date priceDate);
		// sharePrice is given as a number of CENTS
	stock(const stock& s);						// copy constructor
	stock(void);								// default constructor
	char const * const getSymbol(void) const;
	stock& operator=(const stock& s);
	stock& operator=(stock const * const s);
	~stock(void);

	// display column headers
	static void displayHeaders(ostream& out);	// display the headers when this instance is printed

	// prints share price as DOLLARS
	// (e.g. 2483 would print out as 24.83 and 200 would print out as 2.00)
	friend ostream& operator<<(ostream& out, const stock& s);

	friend class hashmap;

private:
	char * symbol;
	char * name;
	int sharePrice;
	date priceDate;
};
