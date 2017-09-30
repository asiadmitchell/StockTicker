// do not change this file

#pragma once

#include <ostream>

using namespace std;

class date
{
public:
	typedef enum {INVALID, JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE,
				  JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER}
	Month;

	date(Month month, int day, int year);
	date(const date& date);					// copy constructor
	date(void);								// default constructor
	~date(void);

	friend ostream& operator<<(ostream& out, const date& d);

private:
	Month	month;
	int		day;
	int		year;
};
