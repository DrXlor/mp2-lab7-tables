#ifndef __ARRAYTAB_H
#define __ARRAYTAB_H

#include "TTable.h"

#define TabMaxSize 40

enum TDataPos {FIRST_POS, CURRENT_POS, LAST_POS};

class  TArrayTable : public TTable 
{
	protected:
		PTTabRecord *pRecs;
		int TabSize;      
		int CurrPos; 
	public:
		TArrayTable(int Size=TabMaxSize)
		{
			if(Size <=0)
				Size = TabMaxSize;
			pRecs = new PTTabRecord[Size];
			for (int i=0; i<Size; i++) 
				pRecs[i] = nullptr;
			TabSize = Size; 
			DataCount = CurrPos =0;
			
		}
		~TArrayTable()
		{
			for (int i=0; i<DataCount; i++)
				delete pRecs[i];
			delete[] pRecs;
		}                

		virtual int IsFull ( ) const { return DataCount >= TabSize;} 
		int GetTabSize( ) const {return TabSize;} 
		
		virtual TKey GetKey (void) const{return GetKey(CURRENT_POS);}
		virtual PTDatValue GetValuePTR (void) const {return GetValuePTR(CURRENT_POS);}
		virtual TKey GetKey (TDataPos mode) const;
		 virtual PTDatValue GetValuePTR (TDataPos mode) const;
		
		virtual PTDatValue FindRecord (TKey k) =0; 
		virtual void InsRecord (TKey k, PTDatValue pVal ) =0;
		virtual void DelRecord (TKey k) =0;   
	  
		virtual int Reset (void);  
		virtual int IsTabEnded (void) const;
		virtual int GoNext (void) ; 
		
		virtual int SetCurrentPos (int pos);
		int GetCurrentPos (void) const {return CurrPos;} 
		
		friend TSortTable;
};
#endif