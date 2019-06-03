#ifndef _ARRAHASH_H
#define _ARRAHASH_H

#include "THashTable.h"

#define TabMaxSize 40
#define TabHashStep 3

class  TArrayHash : public THashTable 
{
	protected:
		PTTabRecord *pRecs;
		int TabSize;      
		int HashStep;      
		int FreePos;       
		int CurrPos;       
		PTTabRecord pMark;  
		int GetNextPos(int pos){return (pos+HashStep)%TabSize;};
		
	public:
		TArrayHash(int Size= TabMaxSize, int Step= TabHashStep); 
		~TArrayHash();

		virtual int IsFull ( ) const {return DataCount >= TabSize;} 	

		virtual TKey GetKey (void) const;
		virtual PTDatValue GetValuePTR (void) const;

		virtual PTDatValue FindRecord (TKey k); 
		virtual void InsRecord (TKey k, PTDatValue pVal ); 
		virtual void DelRecord (TKey k);     

		virtual int Reset (void); 
		virtual int IsTabEnded (void) const;
		virtual int GoNext (void) ; 
};
#endif