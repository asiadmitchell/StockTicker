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

#include <iomanip>
#include "stock.h"

stock::stock(char const * const symbol, char const * const name, int sharePrice, date priceDate) :
	symbol(NULL),
	name(NULL),
	sharePrice(sharePrice),
	priceDate(priceDate)
{
	this->symbol = new char[strlen(symbol)+1];
	strcpy(this->symbol, symbol);
	this->name = new char[strlen(name)+1];
	strcpy(this->name, name);
}

stock::stock(const stock& s) :
	symbol(NULL),
	name(NULL),
	sharePrice(s.sharePrice),
	priceDate(s.priceDate)
{
	symbol = new char[strlen(s.symbol)+1];
	strcpy(symbol, s.symbol);
	name = new char[strlen(s.name)+1];
	strcpy(name, s.name);
}

stock::stock(void) :
	symbol(NULL),
	name(NULL),
	sharePrice(0),
	priceDate(date::date())
{
}

char const * const stock::getSymbol(void) const
{
	return(symbol);
}

stock& stock::operator=(const stock& s)
{
	if (this == &s)
	{
		return *this;
	}
	else
	{
		if (symbol)
		{
			delete [] symbol;
		}
		if (name)
		{
			delete [] name;
		}
		symbol = new char[strlen(s.symbol)+1];
		strcpy(symbol, s.symbol);
		name = new char[strlen(s.name)+1];
		strcpy(name, s.name);
		sharePrice = s.sharePrice;
		priceDate = s.priceDate; 
		return *this;
	}
}

stock& stock::operator=(stock const * const s)
{
	if (this == s)
	{
		return *this;
	}
	else
	{
		symbol = s->symbol;
		name = s->name;
		sharePrice = s->sharePrice;
		priceDate = s->priceDate;
		return *this;
	}
}

stock::~stock(void)
{
	if (symbol)
	{
		delete [] symbol;
	}
	if (name)
	{
		delete [] name;
	} 
}

// write the fixed headers to the output stream:
//
//  symbol  name                                      price   date
//  ------  ----                                      -----   ----
void stock::displayHeaders(ostream& out)
{
	out << setw(8) << "symbol";
	out << setw(40) << "name";
	out << setw(8) << "price";
	out << "date" << endl;
	out << setw(8) << "------";
	out << setw(40) << "----";
	out << setw(8) << "-----";
	out << "----" << endl;
}

// prints share price as DOLLARS
// (e.g. 2483 would print out as 24.83 and 200 would print out as 2.00)
ostream& operator<<(ostream& out, const stock& s)
{	
	out << setw(8) << s.symbol;
	out << setw(40) << s.name;
	out << setw(2) << right << s.sharePrice/100 << ".";
	if (s.sharePrice%100 >= 10)
	{
		out << setw(5) << left << s.sharePrice%100;
	}
	else
	{
		out << left << "0" << setw(4) << s.sharePrice%100;
	}
	out << s.priceDate;
	
	return out;
}
