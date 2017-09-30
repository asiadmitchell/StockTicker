// do not change anything in this file except to make it print out
// your own name instead of "Your Name"

// enable Visual C++ memory leak checking
#ifdef _DEBUG
#include <ostream>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include <iostream>
#include <iomanip>
#include "hashmap.h"

using namespace std;

hashmap		hm(13);

static void printStocks(void)
{
	cout << endl
		 << "----------------------------------------------------------------------------"
		 << endl << endl
		 << hm				// print the contents of the hashmap
		 << endl
		 << "----------------------------------------------------------------------------"
		 << endl << endl;
}

static void printAdditional(unsigned int symbolHash, unsigned int hashIndex,
							unsigned int usedIndex, unsigned int chainLgth)
{
	cout << "(hc 0x"
		 << right
		 << hex << setfill('0')
		 << uppercase << setw(8) << symbolHash
		 << dec << setfill(' ')
		 << ", hi "		<< setw(2) << hashIndex
		 << ", ui "		<< setw(2) << usedIndex
		 << ", cl "		<< setw(2) << chainLgth
		 << ")" 
		 << left << endl;
}

static void searchStock(char *symbol)
{
	unsigned int	usedIndex, hashIndex, symbolHash, chainLgth;
	stock	s;
	if (hm.get(symbol, s, symbolHash, hashIndex, usedIndex, chainLgth)) {
		cout << "found " << left << setw(8) << symbol;
		printAdditional(symbolHash, hashIndex, usedIndex, chainLgth);
		}
	else
		cout << symbol << " not found" << endl;
}

static void addStock(const stock& s)
{
	unsigned int	usedIndex, hashIndex, symbolHash, chainLgth;

	if (hm.put(s, symbolHash, hashIndex, usedIndex, chainLgth)) {
		cout << "added " << left << setw(8) << s.getSymbol();
		printAdditional(symbolHash, hashIndex, usedIndex, chainLgth);
		}
	else
		cout << s.getSymbol() << " not added" << endl;
}

static void removeStock(char *symbol)
{
	unsigned int	usedIndex, hashIndex, symbolHash, chainLgth;
	stock	s;

	if (hm.remove(symbol, s, symbolHash, hashIndex, usedIndex, chainLgth)) {
		cout << "removed " << left << setw(6) << symbol;
		printAdditional(symbolHash, hashIndex, usedIndex, chainLgth);
		}
	else
		cout << symbol << " not removed" << endl;
}

int main(void)
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	cout << "CS260 - Lab3 - Asia Mitchell" << endl;

	printStocks();
	searchStock("IBM");
	addStock(stock("IBM", "International Business Machines", 2573, date(date::MAY, 23, 1967)));
	printStocks();
	searchStock("IBM");
	removeStock("IBM");
	searchStock("IBM");
	removeStock("IBM");
	addStock(stock("MLT", "MLT Software, Inc.", 800, date(date::APRIL, 18, 1988)));
	addStock(stock("IBM", "International Business Machines", 2573, date(date::MAY, 23, 1967)));
	addStock(stock("XRX", "Xerox", 1892, date(date::JUNE, 1, 1980)));
	addStock(stock("US:BA", "Boeing", 6407, date(date::DECEMBER, 14, 1993)));
	addStock(stock("GD", "General Dynamics", 7281, date(date::OCTOBER, 24, 2006)));
	addStock(stock("AAPL", "Apple Computer, Inc.", 2308, date(date::MAY, 1, 1980)));
	addStock(stock("AAPL", "Apple Computer, Inc.", 2308, date(date::MAY, 1, 1980)));
	addStock(stock("GE", "General Electric", 1948, date(date::MARCH, 22, 1987)));
	addStock(stock("ATT", "American Telephone & Telegraph", 20, date(date::MAY, 10, 1998)));
	printStocks();
	searchStock("ATT");
	removeStock("AAPL");
	removeStock("AAPL");
	searchStock("ATT");
	removeStock("US:BA");
	searchStock("GE");
	removeStock("GE");
	searchStock("ATT");
	addStock(stock("AAPL", "Apple Computer, Inc.", 2308, date(date::MAY, 1, 1980)));
	addStock(stock("GE", "General Electric", 1948, date(date::MARCH, 22, 1987)));
	addStock(stock("US:BA", "Boeing", 6407, date(date::DECEMBER, 14, 1993)));
	printStocks();

	return 0;
}