#ifndef __SCANTAB_H
#define __SCANTAB_H

#include "TArrayTable.h"

class  TScanTable: public TArrayTable {
	public:
		TScanTable(int Size=TabMaxSize): TArrayTable(Size){};
		virtual PTDatValue FindRecord (TKey k) ;
		virtual void InsRecord (TKey k, PTDatValue pVal = nullptr ) ;
		virtual void DelRecord (TKey k) ;
};
#endif