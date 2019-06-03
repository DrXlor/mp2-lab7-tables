#include "TMarks.h"
#include <iostream>
#include <string>


std::string* TMarks::name = nullptr;
int TMarks::num = 0;


TMarks::TMarks(int * _marks, int numM)
{
	if(_marks == nullptr)
		throw std::string( "Error! Mark");
	if(numM < 0)
		throw std::string ("Error Num!");

	mark = new int[numM];
	for(int i=0; i<numM; i++)
		mark[i] = _marks[i];
}

void TMarks::SetDis(std::string *_name, int _num) 
{
	delete[] name;
	num = _num;
	name = new std::string[num];
	for(int i=0; i<num; i++)
		name[i] = _name[i];
}

int& TMarks::operator[](int pos)
{
	if(pos<-1 || pos > num)
		throw  std::string( "Error! Pos");
	return mark[pos];
}

TDatValue * TMarks::GetCopy()
{
	return new TMarks(mark, num);
}

int TMarks::GetMarkByName(string _name)
{
	int pos=0;
	while (_name != name[pos])
		pos++;

	return mark[pos];
}

double TMarks::AvrMark()
{
	double avr = 0;
	for (int i = 0; i < num; i++)
		avr += mark[i];
	avr /= num;
	return avr;
}

int TMarks::ItExcellentMark()
{
	int flag = 1;
	for(int i=0; i<num; i++)
		if (mark[i] != 5)
		{
			flag = 0;
			break;
		}
	return flag;
}

std::string TMarks::GetName (int pos)
{
	if(pos<-1 || pos > num)
		throw  std::string( "Error! Pos");
	return name[pos];
}
