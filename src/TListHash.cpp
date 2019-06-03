#include "TListHash.h"

TListHash ::TListHash (int Size) : THashTable()
{
	if (Size <= 0)
		throw std::string("Error size");
	pList = new PTDatList[Size];
	TabSize = Size;
	CurrList =0;
	for(int i=0; i<TabSize; i++)
		pList[i] = new TDatList();
}

TListHash :: ~TListHash()
{
	if (pList != nullptr)
	{
		for (int i = 0; i < TabSize; i++)
			delete pList[i];
		delete[] pList;
	}
}

int TListHash :: IsFull() const
{
	//PTDatLink pLink = new TDatLink();
	//int tmp = (pLink == nullptr);
	//delete pLink;
	return 0;
}

PTDatValue TListHash :: FindRecord (TKey k)
{
	PTDatValue pValue = nullptr;
	if (!IsEmpty())
	{
		CurrList = HashFunc(k) % TabSize;
		PTDatList pL = pList[CurrList];
		Efficiency = 0;
		for (pL->Reset(); !pL->IsListEnded(); pL->GoNext())
			if (PTTabRecord(pL->GetDatValue())->Key == k)
			{
				pValue = PTTabRecord(pL->GetDatValue())->pValue;
				break;
			}
		Efficiency = pL->GetCurrentPos() + 1;
		if (pValue == nullptr)
			SetRetCode(TabNoRec);
		else 
			SetRetCode(TabOK);
	}
	else
		SetRetCode(TabEmpty);
	return pValue;
}

void TListHash :: InsRecord (TKey k, PTDatValue pVal)
{
	if (!IsFull())
	{
		if (FindRecord(k) != nullptr)
			SetRetCode(TabRecDbl);
		else
		{
			CurrList = HashFunc(k) % TabSize;
			pList[CurrList]->InsFirst(new TTabRecord(k, pVal));
			DataCount++;
			SetRetCode(TabOK);
		}
	}
	else
		SetRetCode(TabFull);

}

void TListHash :: DelRecord (TKey k)
{
	if (!IsEmpty())
	{
		PTDatValue tmp = FindRecord(k);
		if (tmp == nullptr)
			SetRetCode(TabNoRec);
		else
		{
			pList[CurrList]->DelCurrent();
			DataCount--;
			SetRetCode(TabOK);
		}
	}
	else
		SetRetCode(TabEmpty);
}

int TListHash ::Reset(void)
{
	CurrList =0;
	while (pList[CurrList]->IsEmpty() && !IsTabEnded())
		CurrList++;
	pList[CurrList]->Reset();
	return IsTabEnded();
}

int TListHash :: IsTabEnded(void) const
{
	return CurrList >= TabSize-1;
}

int TListHash :: GoNext (void)
{
	if (!IsTabEnded())
	{
		if (!(pList[CurrList]->IsListEnded()))
			pList[CurrList]->GoNext();
		if (pList[CurrList]->IsListEnded())
		{
			while (++CurrList && !IsTabEnded())
				if (!pList[CurrList]->IsEmpty())
				{
					pList[CurrList]->Reset();
					break;
				}
		}
	}
	return IsTabEnded();

}

TKey TListHash :: GetKey(void) const 
{
	if((CurrList <0) || IsTabEnded() || pList[CurrList]->IsListEnded())
		return std::string("");
	PTTabRecord pRec =  PTTabRecord(pList[CurrList]->GetDatValue());
	return (pRec == nullptr )?  std::string("") : pRec->Key;
}

PTDatValue TListHash :: GetValuePTR(void) const
{
	if((CurrList <0) || IsTabEnded())
		return nullptr;
	PTTabRecord pRec =  PTTabRecord(pList[CurrList]->GetDatValue());
	return(pRec == nullptr)? nullptr : pRec->pValue;
}