// enable Visual C++ memory leak checking
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#ifdef _DEBUG
#include <ostream>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "date.h"

date::date(Month month, int day, int year) :
	month(month),
	day(day),
	year(year)
{
}

date::date(const date& date) :
	month(date.month),
	day(date.day),
	year(date.year)
{
}

date::date() :
	month(INVALID),
	day(0),
	year(0)
{
}

date::~date(void)
{ 
}

ostream& operator<<(ostream& out, const date& d)
{
	char month[10];
	switch (d.month)
	{
		case 1: 
			strcpy(month, "January");
			break;
		case 2: 
			strcpy(month,"February");
			break;
		case 3: 
			strcpy(month, "March");
			break;
		case 4: 
			strcpy(month, "April");
			break;
		case 5: 
			strcpy(month, "May");
			break;
		case 6: 
			strcpy(month, "June");
			break;
		case 7: 
			strcpy(month, "July");
			break;
		case 8: 
			strcpy(month, "August");
			break;
		case 9: 
			strcpy(month, "September");
			break;
		case 10: 
			strcpy(month, "October");
			break;
		case 11: 
			strcpy(month, "November");
			break;
		case 12: 
			strcpy(month, "December");
			break;
		default:
			strcpy(month, "Invalid");
			break;
	}
	out << month << " " << d.day << ", " << d.year;
	return out;
}
