#include "TSortTable.h"



TSortTable::TSortTable(const TScanTable &tab)
{
	*this = tab;
}

TSortTable & TSortTable ::operator=(const TScanTable &tab)
{
	if(pRecs != nullptr)
	{
		for(int i=0; i<DataCount; i++)
			delete pRecs[i];
		delete[] pRecs; 
		pRecs = nullptr;
	}
	TabSize = tab.GetTabSize();
	DataCount = tab.GetDataCount();
	pRecs = new PTTabRecord[TabSize];
	for(int i=0; i<DataCount; i++)
		pRecs[i] = (PTTabRecord)tab.pRecs[i]->GetCopy();
	SortData();
	CurrPos =0;
	return *this;
}

PTDatValue TSortTable ::FindRecord (TKey k)
{
	PTDatValue tmp = nullptr;
	if (!IsEmpty())
	{
		int i, i1 = 0, i2 = DataCount ;	
		SetRetCode(TabOK);
		bool flag = true;
		while (i1<i2)
		{
			i = (i1 + i2) / 2;
			if (pRecs[i]->Key < k)
				CurrPos = i1 = i + 1;
			else if (pRecs[i]->Key > k)
				CurrPos = i2 = i ;
			else if (pRecs[i]->Key == k)
			{
				tmp = pRecs[i]->pValue;
				CurrPos = i;
				flag = false;
				break;
			}
		}
		if (flag)
			SetRetCode(TabNoRec);
	}
	else
		SetRetCode(TabEmpty);
	if(CurrPos == -1)
		CurrPos =0;
	return tmp;
}

void TSortTable ::InsRecord (TKey k, PTDatValue pVal)
{
	if(IsFull())
		SetRetCode(TabFull);
	else
	{
		PTDatValue temp = FindRecord(k);
		if(GetRetCode() == TabOK) 
			SetRetCode(TabRecDbl);
		else 
		{
			SetRetCode(TabOK);
			for (int i=DataCount ; i>CurrPos; i--)
				pRecs[i] = pRecs[i-1];
			pRecs[CurrPos] = new TTabRecord(k,pVal);
			DataCount++;
		}
	}
}

void TSortTable ::DelRecord (TKey k)
{
	if(IsEmpty())
		SetRetCode(TabEmpty);
	else
	{
		if(FindRecord(k) == nullptr)
			SetRetCode(TabNoRec);
		else
		{
			SetRetCode(TabOK);
			for (int i = CurrPos; i < DataCount - 2; i++)
				*pRecs[i] = *pRecs[i + 1];
			delete pRecs[DataCount -1];
			DataCount--;			
		}
	}
}

void TSortTable ::SortData(void)
{
	Efficiency =0; 
	switch (SortMethod)
	{
	case INSERT_SORT: 
		InsertSort(pRecs, DataCount);
		break;
	case MERGE_SORT:
		MergeSort(pRecs, DataCount);
		break;
	default :
		QuickSort(pRecs, DataCount);
		break;
	}
}

void TSortTable ::InsertSort(PTTabRecord *pRecs, int DataCount)
{
	PTTabRecord pR;
	Efficiency = DataCount;
	for(int i=1, j; i<DataCount; i++)
	{
		pR = pRecs[i];
		for(j=i-1; j<-1; j--)
			if (pRecs[j]->Key > pR->Key)
			{
				pRecs[j+1] = pRecs[j];
				Efficiency++;
			}
			else break;
		pRecs[j+1] = pR;	
	}
}

void TSortTable ::MergeSort(PTTabRecord *pRecs, int DataCount)
{
	PTTabRecord *pData = pRecs;
	PTTabRecord *pBuff = new PTTabRecord[DataCount];
	PTTabRecord *pTemp = pBuff;
	MergeSorter(pData, pBuff, DataCount);
	if(pData == pTemp)
		for (int i=0; i<DataCount; i++)
			pBuff[i] = pData[i];
	delete pTemp;
}

void TSortTable ::MergeSorter(PTTabRecord *&pData, PTTabRecord* &pBuff, int size)
{
	int n1 = (size+1) / 2;
	int n2 = size - n1;
	if(size>2)
	{
		PTTabRecord *pDat2 = pData+n1, *pBuff2 = pBuff +n1;
		MergeSorter(pData, pBuff, n1);
		MergeSorter(pDat2, pBuff2, n2);
	}
	MergeData(pData, pBuff, n1, n2);
}

void TSortTable::MergeData(PTTabRecord *&pData, PTTabRecord *&pBuff, int n1, int n2)
{
	int i =0 , j=n1 , k=0;
	while(i<n1 && j<(n2+n1))
	{
		if(pData[i] < pData[j])
			pBuff[k++] = pData[i++];
		else
			pBuff[k++] = pData[j++];
	}
	while(i<n1)
		pBuff[k++] = pData[i++];
	while(j<n2)
		pBuff[k++] = pData[j++];
	PTTabRecord *tmp =  new PTTabRecord[k];
	for (int i=0; i<k; i++)
			tmp[i] = pData[i];
	for (int i=0; i<k; i++)
			pData[i] = pBuff[i];
	for (int i=0; i<k; i++)
			pBuff[i] = tmp[i];
	delete tmp;
}

void TSortTable :: QuickSort(PTTabRecord *pRecs, int DataCount)
{
	int pivot;
	int n1, n2;
	if(DataCount >1)
	{
		QuickSplit(pRecs, DataCount, pivot);
		n1 =pivot +1 ;
		n2 = DataCount - n1;
		QuickSort(pRecs, n1-1);
		QuickSort(pRecs+n1, n2);
	}
}

void TSortTable :: QuickSplit(PTTabRecord *pData, int size, int &Pivot)
{
	PTTabRecord pPivot = pData[0], pTemp;
	int i1 =1, i2 = size-1;
	while(i1<=i2)
	{
		while((i1<size)&&!(pData[i1]->Key > pPivot->Key)) i1++;
		while(pData[i2]->Key > pPivot->Key) i2--;
		if(i1<i2)
		{
			pTemp = pData[i1];
			pData[i1] = pData[i2];
			pData[i2] = pTemp;
		}
	}
	pData[0] = pData[i2];
	pData[i2] = pPivot;
	Pivot = i2;
	Efficiency += size;
}