#include "DatLink.h"

void TDatLink::SetDatValue(PTDatValue pVal)
{
	pValue=pVal;
}

PTDatValue TDatLink::GetDatValue()
{
	return pValue;
}

PTDatLink TDatLink::GetNextDatLink()
{
	return (PTDatLink)pNext;
}