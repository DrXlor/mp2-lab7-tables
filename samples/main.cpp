#include "TBalTree.h"
#include "TMarks.h"
#include <iostream>
#include <fstream>
#include "Application.h"

using namespace std;

int main()
{
	TTable **grps = new TTable*[2];
	TBalanceTree grupp1;
	TListHash grupp2;
	grps[0] = &grupp1;
	grps[1] = &grupp2;

	ReadFromFile("gr1.txt", grps[0]);	
	ReadFromFile("gr2.txt", grps[1]);
	
	//-------------------------------------------------------------------------------
	cout << "Group 1" << endl;
	Print(grps[0]);
	cout << "Group 2" << endl;
	Print(grps[1]);
	
	//-------------------------------------------------------------------------------
	cout << "Excellent in 1 group = " << GetExcellent(grps[0])<< endl;
	cout << "Excellent in 2 group = " << GetExcellent(grps[1]) << endl;
	cout << "Excellent in all group = " << GetExcellentAllGroup(grps , 2) << endl <<endl;
	
	//-------------------------------------------------------------------------------
	cout << "Average mark by Prog in 1 group = "<< AverMarkGroupBySub(grps[0], "Prog") <<endl;
	cout << "Average mark by Prog in 2 group = " << AverMarkGroupBySub(grps[1], "Prog") << endl;
	cout << "Average mark by Prog in all group = " << AverMarkAllGroupBySub(grps , 2, "Prog") <<endl<< endl;
	
	//-------------------------------------------------------------------------------
	cout << "Average mark by all sub in 1 group = " << AverMarkGroup(grps[0]) << endl;
	cout << "Average mark by all sub in 2 group = " << AverMarkGroup(grps[1]) << endl;
	cout << "Excellent in all group = " << AverMarkAllGroup(grps , 2) << endl <<endl;

	return 0;
}
