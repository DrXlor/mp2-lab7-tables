#include "TTreeNode.h"

TDatValue * TTreeNode ::GetCopy()
{
	TTreeNode *tmp = new TTreeNode(Key, pValue, nullptr, nullptr);
	return tmp;
}