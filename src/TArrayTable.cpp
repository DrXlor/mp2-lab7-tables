#include "TArrayTable.h"

TKey TArrayTable :: GetKey (TDataPos mode) const
{
	int pos =-1;
	if(!IsEmpty())
	{
		switch (mode)
		{
			case FIRST_POS: pos=0; break;
			case LAST_POS: pos = DataCount-1; break;
			default: pos = CurrPos; break;
		}
	}
	return (pos == -1 ) ? std::string("") : pRecs[pos]->Key;
}

PTDatValue TArrayTable :: GetValuePTR (TDataPos mode) const
{
	int pos =-1;
	if(!IsEmpty())
	{
		switch (mode)
		{
			case FIRST_POS: pos=0; break;
			case LAST_POS: pos = DataCount-1; break;
			default: pos = CurrPos; break;
		}
	}
	return (pos == -1) ? nullptr : pRecs[pos]->pValue;
}

int TArrayTable::Reset()
{
	CurrPos =0;
	return IsTabEnded();
}

int TArrayTable :: IsTabEnded() const
{
	return CurrPos >= DataCount;
}

int TArrayTable :: GoNext()
{
	if(!IsTabEnded())
		CurrPos++;
	return IsTabEnded();
}

int TArrayTable :: SetCurrentPos(int pos)
{
	CurrPos = ((pos > -1) && (pos < DataCount)) ? pos : 0; 
	return IsTabEnded();
}