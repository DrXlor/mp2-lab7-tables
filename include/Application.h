#include <iostream>
#include <fstream>
#include "TMarks.h"


//template <typename Tab>
void ReadFromFile(std::string fileName, TTable *&tab)
{
	fstream file;
	file.open(fileName);
	if(!file.is_open())
		cout << "Error! File not open!";
	int numD, numS, *mark;
	std::string *dis, fName, lName;

	file >> numD;
	dis = new std::string[numD];
	mark = new int[numD];
	for(int i=0; i<numD; i++)
			file>>dis[i];
	TMarks::SetDis(dis, numD);
	delete[] dis;

	file >> numS;
	for(int i=0; i<numS; i++)
	{
		file >> fName;
		file >> lName;
		for(int j=0; j<numD; j++)
			file >> mark[j];

		tab->InsRecord(fName + " " + lName,( new TMarks(mark, numD)));		
	}
}

void Print(TTable *&tab)
{
	int i = 0;

	while (i++ < 20)
		cout << " ";

	for (int i = 0; i < TMarks::GetNum(); i++)
		cout <<((TMarks*)tab->GetValuePTR())->GetName(i)<<" ";
	cout << endl;	

	for (tab->Reset(); !tab->IsTabEnded(); tab->GoNext())
	{
		cout << tab->GetKey();
		for (int i = 0; i < 19 - tab->GetKey().size(); i++) cout << " ";
		cout << *(TMarks*)(tab->GetValuePTR()) << endl;
	}
	cout << endl;
}

void AverMarkStude(TTable *&tab)
{
	for (tab->Reset(); !tab->IsTabEnded(); tab->GoNext())
		cout  << tab->GetKey() << "	 " << static_cast<TMarks*>(tab->GetValuePTR())->AvrMark() << endl;
}

double AverMarkGroup(TTable *&tab)
{
	double avr = 0;
	for (tab->Reset(); !tab->IsTabEnded();tab->GoNext())
		avr += ((TMarks*)tab->GetValuePTR())->AvrMark();
	avr /= tab->GetDataCount();

	return avr;
}

void MarkBySub(TTable *&tab, std::string dis)
{
	for (tab->Reset(); !tab->IsTabEnded(); tab->GoNext())
		cout  << tab->GetKey() << "	 " << ((TMarks*)tab->GetValuePTR())->GetMarkByName(dis) << endl;
}

int GetExcellent(TTable *&tab)
{
	int count = 0;
	for (tab->Reset(); !tab->IsTabEnded(); tab->GoNext())
		count += ((TMarks*)tab->GetValuePTR())->ItExcellentMark();
	return count;
}

double AverMarkGroupBySub(TTable *&tab, std::string dis)
{
	double avr = 0;
	for (tab->Reset(); !tab->IsTabEnded(); tab->GoNext())
		avr += ((TMarks*)tab->GetValuePTR())->GetMarkByName(dis);
	avr /= tab->GetDataCount();

	return avr;
}

double AverMarkAllGroup( TTable** tab , int count )
{
	double avr = 0;
	for(int i=0; i< count; i++)
		avr += AverMarkGroup(tab[i]);
	avr /= count;
	
	return avr;
}

double AverMarkAllGroupBySub(TTable** tab , int count, std::string dis)
{
	double avr = 0;
	for(int i=0; i< count; i++)
		avr += AverMarkGroupBySub(tab[i], dis);
	avr /= count;

	return avr;
}

int GetExcellentAllGroup( TTable** tab , int count)
{
	int num = 0;
	for(int i=0; i< count; i++)
		num += GetExcellent(tab[i]);

	return num;
}
