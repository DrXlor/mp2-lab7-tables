#ifndef _TREENODE_H
#define _TREENODE_H
#include <iostream>
#include"TTabRecord.h"

class  TTreeNode;
typedef  TTreeNode *PTTreeNode;

class  TTreeNode: public TTabRecord {
	protected: 
		PTTreeNode pLeft, pRight;
	public:
		TTreeNode(TKey k="", PTDatValue pVal=nullptr, PTTreeNode pL=nullptr, 
		PTTreeNode pR=nullptr ): TTabRecord(k,pVal), pLeft(pL), pRight(pR) {};
		PTTreeNode GetLeft(void) const{return pLeft;} 
		PTTreeNode GetRight(void) const {return pRight;}
		virtual TDatValue * GetCopy();
		
	friend class TTreeTable;
	friend class TBalanceTree;
};
#endif