#ifndef _TREETAB_H
#define _TREETAB_H

#include<stack>
#include"TTable.h"
#include"TTreeNode.h"

class  TTreeTable: public TTable 
{
	protected: 
		PTTreeNode pRoot;
		PTTreeNode *ppRef;
		PTTreeNode pCurrent;
		int CurrPos;
		stack<PTTreeNode> St;
		void DeleteTreeTab (PTTreeNode pNode);
	public:
		TTreeTable(): TTable(){CurrPos=0; pRoot=pCurrent=nullptr; ppRef=nullptr;}   
		~TTreeTable(){DeleteTreeTab (pRoot);}

		virtual int IsFull ( ) const ;

		virtual PTDatValue FindRecord (TKey k);
		virtual void InsRecord (TKey k, PTDatValue pVal );
		virtual void DelRecord (TKey k);

		virtual TKey GetKey (void) const;
		virtual PTDatValue GetValuePTR (void) const;
		virtual int Reset (void); 
		virtual int IsTabEnded (void) const;
		virtual int GoNext (void) ;

	protected: 
		string tk[20];
		int tl[20], pos;
		void PutValues(PTTreeNode pNode, int Level);
};
#endif