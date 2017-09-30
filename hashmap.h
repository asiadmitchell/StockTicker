#pragma once

#include "stock.h"

class hashmap
{
public:
	hashmap(int capacity);
	~hashmap(void);

	// Gets the stock associated with the provided stock symbol from the hashmap,
	// returns true if successful, false if not.
	//
	// Additional data returned:
	//		symbolHash:	result of applying hashStr() to stock symbol
	//		hashIndex:	array index produced by applying the modulo operator
	//						to the hash value produced by hashStr()
	//		usedIndex:	array index where the stock was actually found
	//		chainLgth:	length of the linear probe chain to the stock
	bool get(char const * const symbol, stock& s,
			 unsigned int& symbolHash, unsigned int& hashIndex,
			 unsigned int& usedIndex, unsigned int& chainLgth)
			 const;

	// Adds the stock to the hashmap, returns true if successful,
	// false if not (if the symbol is already present as a key or
	// if the hash table was already full).
	//
	// Additional data returned:
	//		symbolHash:	result of applying hashStr() to stock symbol
	//		hashIndex:	array index produced by applying the modulo operator
	//						to the hash value produced by hashStr()
	//		usedIndex:	array index where the stock will actually be stored
	//		chainLgth:	length of the linear probe chain to the stock
	bool put(const stock& s,
			 unsigned int& symbolHash, unsigned int& hashIndex,
			 unsigned int& usedIndex, unsigned int& chainLgth);

	// Removes the stock associated with the provided symbol from the hashmap,
	// returns true if successful, false if not (if the symbol is not present as a key).
	// Returns a copy of the stock in s.
	//
	// Additional data returned:
	//		symbolHash:	result of applying hashStr() to stock symbol
	//		hashIndex:	array index produced by applying the modulo operator
	//						to the hash value produced by hashStr()
	//		usedIndex:	array index where the stock was actually found
	//		chainLgth:	length of the linear probe chain to the stock
	bool remove(char const * const symbol, stock &s,
				unsigned int& symbolHash, unsigned int& hashIndex,
				unsigned int& usedIndex, unsigned int& chainLgth);

	friend ostream& operator<<(ostream& out, const hashmap& h);

private:
	static unsigned int hashStr(char const * const symbol);		// hashing function

	struct slot
	{
		enum state {empty, deleted, full};

		stock	slotStock;
		state	slotState;
	};

	slot	*slots;
	int		capacity;
	int		nStocks;

	int		nextIndex(int index) const;
	int		prevIndex(int index) const;
	bool	slotEmpty(int index) const;
	void	setSlotEmpty(int index);
};
