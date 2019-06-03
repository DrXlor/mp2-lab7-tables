#include<math.h>
#include<conio.h>

#include"TBalTree.h"

void TBalanceTree :: InsRecord(TKey k, PTDatValue pVal)
{
	if (IsFull()) 
		SetRetCode (TabFull);
	else 
		InsBalanceTree((PTBalanceNode&)pRoot, k, pVal);
}

void TBalanceTree ::DelRecord(TKey k)
{
	if (IsEmpty()) 
		SetRetCode (TabEmpty);
	else 
		DelBalanceTree((PTBalanceNode&)pRoot, k, (PTBalanceNode&)pRoot);
}

int TBalanceTree :: DelBalanceTree(PTBalanceNode &pNode, TKey k, PTBalanceNode& pParent)
{
	int HeighIndex = HeightOK;
	if(FindRecord(k) == nullptr)
		SetRetCode(TabNoRec);
	else
	{
		if(k < pNode->Key)
		{
			if(DelBalanceTree((PTBalanceNode&)pNode->pLeft, k, pNode) == HeightOK)
				HeighIndex = RightTreeBalancing(pNode);
		}
		else if(k > pNode->Key)
		{
			if(DelBalanceTree((PTBalanceNode&)pNode->pRight, k, pNode) == HeightOK)
				HeighIndex = LeftTreeBalancing(pNode);
		}
		else
		{
			if(pNode->pLeft == nullptr && pNode->pRight == nullptr)
			{
				if(pParent->pLeft == pNode)
					pParent->pLeft = nullptr;
				else
					pParent->pRight = nullptr;
				pNode = nullptr;
				HeighIndex = HeightOK;
			}
			else if(pNode->pLeft == nullptr)
			{
				if (pParent->pLeft == pNode)
					pParent->pLeft = pNode->pRight;
				else
					pParent->pRight = pNode->pRight;
				pNode->pRight = nullptr;
				HeighIndex = HeightOK;
			}
			else if(pNode->pRight == nullptr)
			{
				if(pParent->pLeft == pNode)
					pParent->pLeft = pNode->pLeft;
				else
					pParent->pRight = pNode->pLeft;
				pNode->pLeft= nullptr;
				HeighIndex = HeightOK;
			}
			else
			{
				PTBalanceNode max = (PTBalanceNode)pNode->pRight;
				while(max->pLeft != nullptr)
					max= (PTBalanceNode)max->pLeft;
				pNode->Key = max->Key;
				pNode->pValue = max->pValue;					
				max->Key = k;
				DelBalanceTree((PTBalanceNode&)pNode->pRight, k, pNode);					
				HeighIndex = LeftTreeBalancing(pNode);
				max = nullptr;
			}			
			DataCount--;
		}
	}
	return HeighIndex;
}

int TBalanceTree ::InsBalanceTree(PTBalanceNode &pNode, TKey k, PTDatValue pVal)
{
	int HeighIndex = HeightOK;
	if(pNode == nullptr ) 
	{
		SetRetCode(TabOK);
		pNode = new TBalanceNode(k, pVal);
		HeighIndex = HeightInc;
		DataCount++;
	}
	else if(k < pNode->GetKey())
	{
		if(InsBalanceTree( (PTBalanceNode&)pNode->pLeft, k, pVal) == HeightInc)
			HeighIndex = LeftTreeBalancing(pNode);
	}
	else if(k > pNode->GetKey())
	{
		if(InsBalanceTree( (PTBalanceNode&)pNode->pRight, k, pVal) == HeightInc)
			HeighIndex = RightTreeBalancing(pNode);
	}
	else 
	{
		SetRetCode(TabRecDbl);
		HeighIndex = HeightOK;
	}
	return HeighIndex;
}

int TBalanceTree ::LeftTreeBalancing(PTBalanceNode &pNode)
{
	int HeighIndex = HeightOK;
	switch (pNode->GetBalance())
	{
	case BalRight: pNode->SetBalance(BalOK); HeighIndex = HeightOK; break;
	case BalOK: pNode->SetBalance(BalLeft); HeighIndex = HeightInc; break;
	case BalLeft : 
		PTBalanceNode p1, p2;
		p1 = PTBalanceNode(pNode->pLeft);
		if(p1->GetBalance() == BalLeft)
		{
			pNode->pLeft = p1->pRight;
			p1->pRight  = pNode;
			pNode->SetBalance(BalOK);
			pNode = p1;
		}
		else 
		{
			p2 = PTBalanceNode(p1->pRight);
			p1->pRight = p2->pLeft;
			p2->pLeft = p1;
			pNode->pLeft = p2->pRight;
			p2->pRight = pNode;
			if(p2->GetBalance() == BalLeft) 
				pNode->SetBalance(BalRight);
			else
				pNode->SetBalance(BalOK);
			if(p2->GetBalance() == BalRight) 
				p1->SetBalance(BalLeft);
			else p1->SetBalance(BalOK);
			pNode = p2;
			if (pNode == pRoot)
				pRoot = p2;
		}
		pNode->SetBalance(BalOK);
		HeighIndex = HeightOK;
	}
	return HeighIndex;
}

int TBalanceTree :: RightTreeBalancing(PTBalanceNode &pNode)
{
	int HeighIndex = HeightOK;
	switch (pNode->GetBalance())
	{
	case BalLeft: pNode->SetBalance(BalOK); HeighIndex = HeightOK; break;
	case BalOK: pNode->SetBalance(BalRight); HeighIndex = HeightInc; break;
	case BalRight: 
		PTBalanceNode p1, p2;
		p1 = PTBalanceNode(pNode->pRight);
		if(p1->GetBalance() == BalRight)
		{
			pNode->pRight = p1->pLeft;
			p1->pLeft  = pNode;
			pNode->SetBalance(BalOK);
			pNode = p1;
			if (pNode == pRoot)
				pRoot = p1;
		}
		else 
		{
			p2 = PTBalanceNode(p1->pLeft);
			p1->pLeft = p2->pRight;
			p2->pRight = p1;
			pNode->pRight = p2->pLeft;
			p2->pLeft = pNode;
			if(p2->GetBalance() == BalRight) 
				pNode->SetBalance(BalLeft);
			else
				pNode->SetBalance(BalOK);
			if(p2->GetBalance() == BalLeft) 
				p1->SetBalance(BalRight);
			else p1->SetBalance(BalOK);
			pNode = p2;
			if (pNode == pRoot)
				pRoot = p2;
		}
		pNode->SetBalance(BalOK);
		HeighIndex = HeightOK;
	}
	
	return HeighIndex;
}