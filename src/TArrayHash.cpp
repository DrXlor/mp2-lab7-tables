#include "TArrayHash.h"
#include<string>

TArrayHash :: TArrayHash (int Size, int Step) : THashTable()
{
	if (Size <= 0 || Step <= 1 || Step >= Size)
		throw std::string("Error Size or Step!");

	pRecs = new PTTabRecord[Size];
	for (int i = 0; i < Size; i++)
	{
		pRecs[i] = nullptr;
	}
	TabSize = Size;
	HashStep = Step;
	
	pMark = new TTabRecord(std::string("deleted"), nullptr);
}

TArrayHash :: ~TArrayHash()
{
	if (pRecs != nullptr)
	{
		for (int i = 0; i < TabSize; i++)
			if ((pRecs[i] != nullptr) && (pRecs[i] != pMark))
				delete pRecs[i];
		delete[] pRecs;
	}
	delete pMark;
}

PTDatValue TArrayHash :: FindRecord(TKey k)
{
		PTDatValue pValue = nullptr;
		if (!IsEmpty())
		{
			FreePos = -1;
			Efficiency = 0;
			CurrPos = HashFunc(k) % TabSize;
			for (int i = 0; i < TabSize; i++)
			{
				Efficiency++;
				if (pRecs[CurrPos] == nullptr)
					break;
				else if (pRecs[CurrPos] == pMark)
				{
					if (FreePos == -1)
						FreePos = CurrPos;
				}
				else if (pRecs[CurrPos]->Key == k)
				{
					pValue = pRecs[CurrPos]->pValue;
					break;
				}
				CurrPos = GetNextPos(CurrPos);
			}
			if (pValue == nullptr)
				SetRetCode(TabNoRec);
			else
				SetRetCode(TabOK);
		}
		else
			SetRetCode(TabEmpty);
	
	return pValue;
}

void TArrayHash ::InsRecord (TKey k, PTDatValue pVal)
{
	if (IsFull())
		SetRetCode(TabFull);
	else
	{
		FreePos = -1;
		CurrPos = HashFunc(k) % TabSize;
		for (int i = 0; i < TabSize; i++)
		{
			if (pRecs[CurrPos] != nullptr && pRecs[CurrPos]->Key == k)
			{
				SetRetCode(TabRecDbl);
				break;
			}
			else if (pRecs[CurrPos] == pMark && FreePos < 0)
				FreePos = CurrPos;
			else if (pRecs[CurrPos] == nullptr && FreePos < 0)
			{
				pRecs[CurrPos] = new TTabRecord(k, pVal);
				DataCount++;
				SetRetCode(TabOK);
				break;
			}
			else if (pRecs[CurrPos] == nullptr && FreePos > -1)
			{
				pRecs[FreePos] = new TTabRecord(k, pVal);
				DataCount++;
				SetRetCode(TabOK);
				break;
			}
			CurrPos = GetNextPos(CurrPos);
			SetRetCode(TabNoMem);
		}
		
	}
}

void TArrayHash :: DelRecord (TKey k)
{
	if (!IsEmpty())
	{
		PTDatValue tmp = FindRecord(k);
		if (tmp == nullptr)
			SetRetCode(TabNoRec);
		else
		{
			if (pRecs[CurrPos]->pValue != nullptr)
				pRecs[CurrPos]->pValue = nullptr;
			delete pRecs[CurrPos];
			pRecs[CurrPos] = pMark;
			DataCount--;
			SetRetCode(TabOK);
		}
	}
	else
		SetRetCode(TabEmpty);
}

int TArrayHash :: Reset (void)
{
	CurrPos = 0;
	if (!IsTabEnded())
	{
		while (CurrPos < TabSize)
		{
			if ((pRecs[CurrPos] != nullptr) && (pRecs[CurrPos] != pMark))
				break;
			CurrPos++;
		}
	}
	return IsTabEnded();

}

int TArrayHash :: IsTabEnded(void) const
{
	return CurrPos >= TabSize;
}

int TArrayHash :: GoNext (void)
{
	if(!IsTabEnded())
	{
		while(++CurrPos <= TabSize)
			if((pRecs[CurrPos]!=nullptr)&&(pRecs[CurrPos]!=pMark)) 
				break;
	}
	return IsTabEnded();
}

TKey TArrayHash ::GetKey(void) const
{
	return ( (CurrPos < 0 )||( CurrPos >= TabSize)) ? std::string("") : pRecs[CurrPos]->Key;
}

PTDatValue TArrayHash :: GetValuePTR(void) const
{
	return ( (CurrPos < 0)||(CurrPos >= TabSize)) ? nullptr : pRecs[CurrPos]->pValue;
}




