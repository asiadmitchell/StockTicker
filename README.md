# StockTicker
### Hash table implementation to store stock and mutual fund information

This data structure will quickly allow users to find out the following information about a stock or mutual fund:

*ticker symbol (e.g., IBM for International Business Machines)
*stock or fund name (e.g. International Business Machines)
*share price (e.g. 25.73) (stored as an int in cents, then converted to dollars)
*Date of that share price (e.g. May, 23, 1967)

Linear probing is used to handle collisions when inserting a new item. The hash table is treated as a circular array.

An attempt to insert a stock into the hash table can fail for one of two reasons:

..1. The stock is already in the hash table
..2. The hash table is full (i.e. no more empty slots)


"Failure to insert" is indYour code will need to handle this condition by indicating failure when requested to insert a stock which is already there, or for which there is not room.


