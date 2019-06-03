#include "TTreeTab.h"
#include <cstring>

int TTreeTable::IsFull() const 
{	
	return 0;
}

PTDatValue TTreeTable :: FindRecord (TKey k)
{
	PTTreeNode pNode = pRoot;
	ppRef = &pRoot;
	Efficiency =0;
	while(pNode != nullptr)
	{
		Efficiency++;
		if(pNode->Key == k) 
			break;
		if(pNode->Key < k) 
			ppRef = &pNode->pRight;
		else 
			ppRef = &pNode->pLeft;
		pNode = *ppRef;
	}
	if(pNode == nullptr)
		SetRetCode(TabNoRec);
	else
		SetRetCode(TabOK);
	return (pNode == nullptr) ? nullptr : pNode->pValue;
}

void TTreeTable::InsRecord(TKey k, PTDatValue pVal)
{
	if(IsFull()) 
		SetRetCode(TabFull);
	else if(FindRecord(k) != nullptr) 
		SetRetCode (TabRecDbl);
	else
	{	
		SetRetCode (TabOK);
		*ppRef = new TTreeNode(k, pVal);
		DataCount++;
	}
}

void TTreeTable :: DelRecord(TKey k)
{
	if(IsEmpty())
		SetRetCode(TabEmpty);
	else if(FindRecord(k) == nullptr)
			SetRetCode(TabNoRec);
	else
	{
		PTTreeNode pNode = *ppRef;
		if(pNode->pRight == nullptr && pNode->pLeft == nullptr)
			*ppRef = nullptr;
		else if( pNode->pRight == nullptr)
		{
			pNode->Key =  pNode->pLeft->Key;
			pNode->pValue = pNode->pLeft->pValue;
			pNode->pLeft=nullptr;
		}
		else if(pNode->pLeft == nullptr)
		{
			pNode->Key =  pNode->pRight->Key;
			pNode->pValue = pNode->pRight->pValue;
			pNode->pRight=nullptr;
		}
		else 
		{
			PTTreeNode min = pNode->pLeft;
			PTTreeNode minParent = pNode;
			while(min->pRight != nullptr)
			{
				minParent = min;
				min = min->pRight;
			}
			if(minParent != pNode)
			{	
				minParent->pRight = min->pLeft;	
				pNode->Key = min->Key;
				pNode->pValue = min->pValue;
				pNode = min;
			}
			else
			{
				pNode->Key =  min->Key;
				pNode->pValue = min->pValue;
				pNode->pLeft = min->pRight;
				min = nullptr;
			}
		}
		DataCount--;
	}
}

TKey TTreeTable::GetKey(void) const
{
	return (pCurrent == nullptr) ? nullptr : pCurrent->Key;
}

PTDatValue TTreeTable ::GetValuePTR(void) const
{
	return (pCurrent == nullptr) ? nullptr : pCurrent->pValue;
}

int TTreeTable :: Reset(void)
{
	PTTreeNode pNode = pCurrent = pRoot;
	while(!St.empty())
		St.pop();
	CurrPos =0;
	while(pNode!= nullptr)
	{
		St.push(pNode);
		pCurrent = pNode;
		pNode =pNode->GetLeft();
	}
	SetRetCode(TabOK);
	return IsTabEnded();
}

int TTreeTable :: IsTabEnded(void) const 
{
	return CurrPos >= DataCount;
}

int TTreeTable :: GoNext(void) 
{
	PTTreeNode pNode;
	if(!IsTabEnded() && (pCurrent != nullptr))
	{
		pNode = pCurrent = pCurrent->GetRight();
		St.pop();
		while(pNode != nullptr)
		{
			St.push(pNode);
			pCurrent = pNode;
			pNode = pNode->GetLeft();
		}
		if((pCurrent == nullptr ) && !St.empty())
			pCurrent = St.top();
		CurrPos++;
	}
	return IsTabEnded();
}

void TTreeTable :: PutValues(PTTreeNode pNode, int Level)
{
	if((pNode != nullptr) && (pos < 20))
	{
		PutValues(pNode->pLeft, Level+1);
		tk[pos] = pNode->Key;
		tl[pos] = Level;
		pos++;
		PutValues(pNode->pRight, Level+1);
	}
}

void TTreeTable :: DeleteTreeTab(PTTreeNode pNode)
{
	if(pNode != nullptr)
	{
		DeleteTreeTab(pNode->pLeft);
		DeleteTreeTab(pNode->pRight);
		delete pNode;
	}
}