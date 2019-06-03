#include "TTabRecord.h"

TDatValue * TTabRecord :: GetCopy()
{
	TDatValue *tmp = new TTabRecord (Key, pValue);
	return tmp;
}