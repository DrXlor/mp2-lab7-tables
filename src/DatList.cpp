#include "DatList.h"

TDatList::TDatList()
{
	pFirst = pLast = pStop = nullptr;
	ListLen=0;
	Reset();
}

PTDatLink TDatList::GetLink (PTDatValue pVal, PTDatLink pLink)
{
	PTDatLink tmp = new TDatLink(pVal, pLink);
	if(tmp == nullptr)
		SetRetCode(ListNoMem);
	SetRetCode(ListOK);
	return tmp;		
}

void TDatList :: DelLink (PTDatLink pLink)
{
	if(pLink != nullptr)
	{
		if (pLink->pValue != nullptr)
			delete pLink->pValue;
		delete pLink;
	}
	SetRetCode(ListOK);
}

PTDatValue TDatList::GetDatValue (  ) const
{
	return pCurrLink->pValue;
}
 
int TDatList::SetCurrentPos ( int pos )
{
	Reset();
	for(int i=0; i<pos; i++, GoNext() )
	SetRetCode(ListOK);
	return RetCode;
}

int TDatList::GetCurrentPos ( void ) const
{
	return CurrPos;
} 

int TDatList::Reset ( void )
{
	pPrevLink = pStop;
	if(IsEmpty())
	{
		pCurrLink = pStop;
		CurrPos =-1;
		SetRetCode (ListEmpty);
	}
	else
	{
		pCurrLink = pFirst;
		CurrPos =0;
		SetRetCode(ListOK);
	}
	return RetCode;
}

int TDatList::IsListEnded ( void ) const
{
	return pCurrLink == pStop;
}

int TDatList:: GoNext ( void )
{
	if (pCurrLink == pStop)
		 SetRetCode(ListNoPos);
	else 
	{
		SetRetCode(ListOK);
		pPrevLink = pCurrLink;
		pCurrLink = pCurrLink->GetNextDatLink();
		CurrPos++;
	}
	return RetCode;
}

void TDatList::InsFirst ( PTDatValue pVal)
{
	PTDatLink tmp = GetLink(pVal,pFirst);
	if (tmp == nullptr)
		SetRetCode(ListNoMem);
	else
	{
		pFirst = tmp;

		ListLen++;
		if (ListLen == 1)
		{
			pLast = tmp;
			Reset();
		}
		else if(CurrPos == 0 ) 
			pCurrLink = tmp;
		else 
			CurrPos++;
		SetRetCode(ListOK);
	}
}

void TDatList::InsLast ( PTDatValue pVal)
{
	PTDatLink tmp = GetLink (pVal,pStop);
	if (tmp == nullptr)
		SetRetCode(ListNoMem);
	else
	{
		if (pLast != nullptr)
			pLast->SetNextLink(tmp);
		pLast = tmp;
		ListLen++;
		if(ListLen==1)
		{
			pFirst = tmp;
			Reset();
		}
		if(IsListEnded())
			pCurrLink = tmp;
		SetRetCode(ListOK);
	}
}

void TDatList::InsCurrent( PTDatValue pVal)
{
	if(IsEmpty() || (pCurrLink == pFirst) ) 
		InsFirst(pVal);
	else if(IsListEnded()) 
		InsLast(pVal);
	else if (pPrevLink == pStop)
		SetRetCode(ListNoPos);
		else 
		{
			PTDatLink  tmp = GetLink(pVal,pCurrLink);
			if(tmp == nullptr)
				SetRetCode(ListNoMem);
			else 
			{
				pCurrLink = tmp;
				pPrevLink->SetNextLink(tmp);
				ListLen++;
				SetRetCode(ListOK);
			}
		}	
}

void TDatList::DelFirst ( void )
{
	if(IsEmpty())
		SetRetCode(ListEmpty);
	else
	{
		PTDatLink tmp = pFirst;
		pFirst = pFirst->GetNextDatLink();
		DelLink(tmp);
		ListLen--;
		if(IsEmpty())
		{
			pLast=pStop;
			Reset();
		}
		else if(CurrPos ==0)
			pCurrLink = pFirst;
			else if(CurrPos == 1) pPrevLink = pStop;
		if (CurrPos > 0) CurrPos--;
		SetRetCode(ListOK);
	}
}

void TDatList:: DelCurrent( void )
{
	if (pCurrLink == pStop) 
		SetRetCode(ListNoPos);
	else if(pCurrLink == pFirst) 
		DelFirst();
	else if(pCurrLink == pLast)
		{
			pLast = pPrevLink;
			pPrevLink->SetNextLink(pCurrLink);
			pCurrLink = pStop;
			ListLen--;
			SetRetCode(ListOK);
		}
	else
	{
		PTDatLink tmp = pCurrLink;
		pCurrLink = pCurrLink->GetNextDatLink();
		pPrevLink->SetNextLink(pCurrLink);
		DelLink(tmp);
		ListLen--;
		SetRetCode(ListOK);
	}
}

void TDatList::DelList ( void )
{
	while(!IsEmpty())
		DelFirst();
	pFirst=pLast = pPrevLink = pCurrLink = pStop;
	CurrPos = -1;
}


