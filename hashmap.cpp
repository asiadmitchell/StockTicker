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

#include "hashmap.h"

hashmap::hashmap(int capacity) :
	nStocks(0),
	capacity(capacity),
	slots(new slot[capacity])
{
	for (int i = 0; i < capacity; i++)
	{
		slots[i].slotState = slot::empty;
	}
}

hashmap::~hashmap(void)
{
	if (slots)
	{
		delete [] slots;
		slots = NULL;
	}
	
}

bool hashmap::get(char const * const symbol, stock& s,
				  unsigned int& symbolHash, unsigned int& hashIndex,
				  unsigned int& usedIndex, unsigned int& chainLgth)
	 const
{
	int ctr = 0;
	int chain = 0;
	int index = hashStr(symbol);
	index %= capacity;
	int next = index;
	while (ctr <= capacity)
	{
		if (slots[next].slotState == slot::full)
		{
			if (strcmp(symbol, slots[next].slotStock.getSymbol()) == 0)
			{
				s = slots[next].slotStock;
				symbolHash = hashStr(symbol);
				hashIndex = index;
				usedIndex = next;
				ctr = 0;
				while (index != next)
				{
					chain++;
					next = prevIndex(next);
				}
				chainLgth = chain + 1;
				return true;
			}
			else
			{
				next = nextIndex(next);
				ctr++;
			}
		}
		else
		{
			next = nextIndex(next);
			ctr++;
		}
	}
	return false;
}

bool hashmap::put(const stock& s,
				  unsigned int& symbolHash, unsigned int& hashIndex,
				  unsigned int& usedIndex, unsigned int& chainLgth)
{
	stock test;
	if (get(s.getSymbol(), test, symbolHash, hashIndex, usedIndex, chainLgth) == true)
	{
		return false;
	}
	else
	{
		int ctr = 0;
		int chain = 0;
		int index = hashStr(s.getSymbol());
		index %= capacity;
		
		int next = index;
		while (ctr <= capacity)
		{
			if (slots[next].slotState == slot::empty || slots[next].slotState == slot::deleted)
			{
				slots[next].slotStock = s;
				symbolHash = hashStr(slots[next].slotStock.getSymbol());
				nStocks++;
				hashIndex = index;
				usedIndex = next;
				slots[next].slotState = slot::full;
				ctr = 0;
				while (index != next)
				{
					chain++;
					next = prevIndex(next);
				}
				chainLgth = chain + 1;
				return true;
			}
			else
			{
				next = nextIndex(next);
				ctr++;
			}
		}
		return false;
	}
}

bool hashmap::remove(char const * const symbol, stock& s,
					 unsigned int& symbolHash, unsigned int& hashIndex,
					 unsigned int& usedIndex, unsigned int& chainLgth)
{
	int ctr = 0;
	int chain = 0;
	int index = hashStr(symbol);
	index %= capacity;
	
	int next = index;
	while (ctr <= capacity)
	{
		if (slots[next].slotState == slot::full)
		{
			if (strcmp(symbol, slots[next].slotStock.getSymbol()) == 0)
			{
				s = slots[next].slotStock;
				nStocks--;
				symbolHash = hashStr(symbol);
				hashIndex = index;
				usedIndex = next;
				slots[next].slotState = slot::deleted;
				ctr = 0;
				while (index != next)
				{
					chain++;
					next = prevIndex(next);
				}
				chainLgth = chain + 1;
				return true;
			}
			else
			{
				next = nextIndex(next);
				ctr++;
			}
		}
		else
		{
			next = nextIndex(next);
			ctr++;
		}
	}
	return false;
}

unsigned int hashmap::hashStr(char const * const str)
{
	// Hash string according to the formula in java.lang.String.hashCode():
	//
	//   s[0]*(31^(n-1)) + s[1]*(31^(n-2)) + ... + s[n-1]
	//
	// s is the array of characters, n is the number of characters in the string,
	// and 31^n means 31 to the nth power.
	//
	// This function is declared static because its result depends
	// only on the characters in the string. You will need to apply
	// the modulo operator to the result of this function to generate
	// the required table index. The place to do this is in the functions
	// that call this function.
	//
	// You can and should do this computation entirely with integers. In other
	// words, there is no need to use floating point values. In particular, you
	// should not use the pow() function from <math.h> in this lab.
	int hash = 0;
	int i = 0;
	for (i; i < strlen(str); i++)
	{
		hash = (31 * hash) + str[i];
	}
	return hash;
}

ostream& operator<<(ostream& out, const hashmap& h)
{
	int i = 0;
	if (h.nStocks == 0)
	{
		out << "no stocks" << endl;
	}
	else
	{
		stock::displayHeaders(out);
		for (i; i < h.capacity; i++)
		{
			if (h.slots[i].slotState == h.slot::full)
			{
				out << h.slots[i].slotStock << endl;
			}
		}
	}
	return out;
}

int hashmap::nextIndex(int index) const
{
	if (index == capacity-1)
	{
		return (0);
	}
	else
	{
		return (index + 1);
	}
}

int hashmap::prevIndex(int index) const
{
	if (index == 0)
	{
		return (capacity-1);
	}
	else
	{
		return (index - 1);
	}
}

bool hashmap::slotEmpty(int index) const
{
	if (slots[index].slotState == slot::empty || slots[index].slotState == slot::deleted)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void hashmap::setSlotEmpty(int index)
{
	slots[index].slotState = slot::empty;
}
