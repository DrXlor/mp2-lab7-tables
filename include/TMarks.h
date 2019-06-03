#ifndef _MARKS_H
#define _MARKS_H
#include <iostream>
#include "TDatValue.h"

using namespace std;

class TMarks : public TDatValue
{
	int *mark;
public:
	static std::string * name;
	static int num;

	TMarks(int * _marks, int num);
	static void SetDis(std::string *_name, int _num);
	int & operator[](int pos);
	TDatValue * GetCopy();
	int GetMarkByName(string _name);
	static int GetNum(){return num;}
	double AvrMark();
	int ItExcellentMark();
	static std::string GetName(int pos);
	friend ostream & operator<<(ostream &os, TMarks &tab)
	{
		for (int i=0; i<tab.GetNum(); i++)
		{
			os << tab[i] <<"     ";
		}
		return os;
	}

	~TMarks(){delete mark;}
};
#endif