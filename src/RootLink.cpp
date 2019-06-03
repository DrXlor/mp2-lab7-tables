
#include "RootLink.h"


TRootLink::TRootLink(PTRootLink pN)
{
	pNext = pN;
}

PTRootLink TRootLink::GetNextLink()
{
	return pNext;
}

void TRootLink::SetNextLink(PTRootLink pLink)
{
	pNext = pLink;
}

void TRootLink::InsNextLink(PTRootLink pLink)
{
	PTRootLink p = pNext;
	pNext = pLink;
	if(pLink != nullptr) 
		pLink->pNext =p;
}
