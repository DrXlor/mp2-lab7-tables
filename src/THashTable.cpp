#include "THashTable.h"

unsigned long THashTable :: HashFunc (const TKey key)
{
	unsigned long hashval =0;
	int Len = key.size();
	for(int i=0; i< Len; i++)
		hashval = (hashval << 3) + key[i];
	return hashval;
}