#ifndef _TTABLE_H
#define _TTABLE_H

#include<iostream>
#include"TTabRecord.h"
#include"tdatacom.h"

using namespace std;

#define TabOK 0
#define TabEmpty -101
#define TabFull -102
#define TabNoRec -103 
#define TabRecDbl -104
#define TabNoMem -105

class TTable : public TDataCom
{
	protected:
		int DataCount;
		int Efficiency;
	public:
		TTable () {DataCount =0; Efficiency =0;}
		virtual ~TTable() {};

		int GetDataCount ( ) const {return DataCount;}  
		int GetEfficiency ( ) const {return Efficiency;} 
		int IsEmpty ( ) const {return DataCount == 0;}  
		virtual int IsFull ( ) const =0;     
		

		virtual PTDatValue FindRecord (TKey k) =0; 
		virtual void InsRecord (TKey k, PTDatValue pVal ) =0; 
		virtual void DelRecord (TKey k) =0;       

		virtual int Reset (void) =0;
		virtual int IsTabEnded (void) const=0;
		virtual int GoNext (void) =0;

		virtual TKey GetKey(void) const=0;
		virtual PTDatValue GetValuePTR(void) const=0;
		
		friend ostream & operator<<(ostream &os, TTable &tab)
		{
			cout <<"Table"<<endl;
			for(tab.Reset();!tab.IsTabEnded();tab.GoNext())
			{
				os << "Name: " << tab.GetKey() ;
			}
			return os;
		}
	
};
#endif