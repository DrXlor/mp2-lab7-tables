#ifndef __DATLINK_H
#define __DATLINK_H
#include "RootLink.h"

class TDatLink;

typedef TDatLink *PTDatLink;

class TDatLink : public TRootLink
{
	protected:
		PTDatValue pValue;
		
	public:
		TDatLink (PTDatValue pVal = nullptr, PTRootLink pN = nullptr):TRootLink(pN)
		{pValue = pVal;}
		
		void SetDatValue (PTDatValue pVal);
		PTDatValue GetDatValue ();
		PTDatLink GetNextDatLink ();

		friend class TDatList;
};
#endif