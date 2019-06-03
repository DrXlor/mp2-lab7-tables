#include <gtest/gtest.h>
#include "TBalTree.h"
#include "TArrayHash.h"
#include "TListHash.h"
#include "TScanTable.h"
#include "TSortTable.h"


TEST(TScanTable, can_create)
{
	TScanTable *tab;

	ASSERT_NO_THROW(tab = new TScanTable(50));
}

TEST(TScanTable, can_create_with_negative_lenght)
{
	TScanTable *tab;

	ASSERT_NO_THROW(tab = new TScanTable(-50));
}

TEST(TScanTable, can_chek_full_return_fasle)
{
	TScanTable tab(5);

	EXPECT_EQ(0, tab.IsFull());
}

TEST(TScanTable, can_chek_full_return_true)
{
	TScanTable tab(5);
	for (int i = 0; i < 5; i++)
	{
		tab.InsRecord("", (PTDatValue)i);
	}
	EXPECT_EQ(1, tab.IsFull());
}

TEST(TScanTable, can_finnd_rec)
{
	TScanTable tab(5);
	
	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("2", (PTDatValue)2);
	tab.InsRecord("3", (PTDatValue)3);

	EXPECT_EQ((PTDatValue)2, tab.FindRecord("2"));
}

TEST(TScanTable, can_finnd_rec_that_is_not)
{
	TScanTable tab(5);

	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("2", (PTDatValue)2);
	tab.InsRecord("3", (PTDatValue)3);

	EXPECT_EQ(nullptr, tab.FindRecord("5"));
}

TEST(TScanTable, can_finnd_rec_if_tab_empty)
{
	TScanTable tab(5);
	tab.FindRecord("2");

	EXPECT_EQ(TabNoRec, tab.GetRetCode());
}

TEST(TScanTable, can_del_if_tab_empty)
{
	TScanTable tab(5);

	tab.DelRecord("1");

	EXPECT_EQ(TabEmpty, tab.GetRetCode());
}

TEST(TScanTable, can_del_rec_that_is_not)
{
	TScanTable tab(5);

	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("2", (PTDatValue)2);
	tab.InsRecord("3", (PTDatValue)3);

	tab.DelRecord("5");

	EXPECT_EQ(TabNoRec, tab.GetRetCode());
}

TEST(TScanTable, can_del_rec)
{
	TScanTable tab(5);

	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("2", (PTDatValue)2);
	tab.InsRecord("3", (PTDatValue)3);

	tab.DelRecord("1");

	EXPECT_EQ(TabOK, tab.GetRetCode());
}

TEST(TScanTable, can_del_rec_chek_DataCount)
{
	TScanTable tab(5);

	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("2", (PTDatValue)2);
	tab.InsRecord("3", (PTDatValue)3);

	tab.DelRecord("2");

	EXPECT_EQ(2, tab.GetDataCount());
}

TEST(TScanTable, can_ins_rec_chek_DataCount)
{
	TScanTable tab(5);

	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("3", (PTDatValue)3);

	tab.InsRecord("2");

	EXPECT_EQ(3, tab.GetDataCount());
}

TEST(TScanTable, can_ins_rec_if_tab_full)
{
	TScanTable tab(3);

	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("2", (PTDatValue)2);
	tab.InsRecord("3", (PTDatValue)3);

	tab.InsRecord("6");

	EXPECT_EQ(TabFull, tab.GetRetCode());
}

TEST(TScanTable, can_ins_rec_if_rec_dbl)
{
	TScanTable tab(5);

	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("2", (PTDatValue)2);
	tab.InsRecord("3", (PTDatValue)3);

	tab.InsRecord("3");

	EXPECT_EQ(TabRecDbl, tab.GetRetCode());
}

TEST(TScanTable, can_ins_rec)
{
	TScanTable tab(5);

	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("2", (PTDatValue)2);
	tab.InsRecord("3", (PTDatValue)3);

	EXPECT_EQ(TabOK, tab.GetRetCode());
}

TEST(TScanTable, can_chek_empty_return_true)
{
	TScanTable tab(5);

	EXPECT_EQ(1, tab.IsEmpty());
}

TEST(TScanTable, can_chek_empty_return_false)
{
	TScanTable tab(5);
	for (int i = 0; i < 5; i++)
	{
		tab.InsRecord("", (PTDatValue)i);
	}
	EXPECT_EQ(0, tab.IsEmpty());
}

TEST(TScanTable, can_get_key_first_pos)
{
	TScanTable tab(5);

	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("2", (PTDatValue)2);

	EXPECT_EQ("1", tab.GetKey(FIRST_POS));
}

TEST(TScanTable, can_get_key_last_pos)
{
	TScanTable tab(5);

	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("2", (PTDatValue)2);

	EXPECT_EQ("2", tab.GetKey(LAST_POS));
}

TEST(TScanTable, can_get_key_current_pos)
{
	TScanTable tab(5);

	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("2", (PTDatValue)2);
	tab.InsRecord("3", (PTDatValue)3);

	tab.SetCurrentPos(1);
	EXPECT_EQ("2", tab.GetKey(CURRENT_POS));
}

TEST(TScanTable, can_get_key)
{
	TScanTable tab(5);

	tab.InsRecord("1", (PTDatValue)1);

	EXPECT_EQ("1", tab.GetKey());
}

TEST(TScanTable, can_get_value)
{
	TScanTable tab(5);

	tab.InsRecord("1", (PTDatValue)1);

	EXPECT_EQ((PTDatValue)1, tab.GetValuePTR());
}

TEST(TScanTable, can_get_value_first_pos)
{
	TScanTable tab(5);

	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("2", (PTDatValue)2);
	tab.InsRecord("3", (PTDatValue)3);

	EXPECT_EQ((PTDatValue)1, tab.GetValuePTR(FIRST_POS));
}

TEST(TScanTable, can_get_value_last_pos)
{
	TScanTable tab(5);

	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("2", (PTDatValue)2);
	tab.InsRecord("3", (PTDatValue)3);

	EXPECT_EQ((PTDatValue)3, tab.GetValuePTR(LAST_POS));
}

TEST(TScanTable, can_get_value_curr_pos)
{
	TScanTable tab(5);

	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("2", (PTDatValue)2);
	tab.InsRecord("3", (PTDatValue)3);
	tab.SetCurrentPos(1);

	EXPECT_EQ((PTDatValue)2, tab.GetValuePTR(CURRENT_POS));
}

TEST(TScanTable, can_get_size)
{
	TScanTable tab(5);

	EXPECT_EQ(5, tab.GetTabSize());
}

TEST(TScanTable, can_reset)
{
	TScanTable tab(5);
	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("2", (PTDatValue)2);
	tab.InsRecord("3", (PTDatValue)3);
	tab.SetCurrentPos(1);

	tab.Reset();

	EXPECT_EQ(0, tab.GetCurrentPos());
}

TEST(TScanTable, can_go_next)
{
	TScanTable tab(5);
	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("2", (PTDatValue)2);
	tab.InsRecord("3", (PTDatValue)3);

	tab.GoNext();

	EXPECT_EQ(1, tab.GetCurrentPos());
}

TEST(TScanTable, can_go_next_if_is_end_tab)
{
	TScanTable tab(5);
	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("2", (PTDatValue)2);
	tab.InsRecord("3", (PTDatValue)3);
	tab.GoNext();
	tab.GoNext();
	tab.GoNext();

	tab.GoNext();

	EXPECT_EQ(3, tab.GetCurrentPos());
}

TEST(TScanTable, can_check_end_tab_return_true)
{
	TScanTable tab(5);
	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("2", (PTDatValue)2);
	tab.InsRecord("3", (PTDatValue)3);
	tab.GoNext();
	tab.GoNext();
	tab.GoNext();

	EXPECT_EQ(1, tab.IsTabEnded());
}

TEST(TScanTable, can_check_end_tab_return_false)
{
	TScanTable tab(5);
	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("2", (PTDatValue)2);
	tab.InsRecord("3", (PTDatValue)3);
	tab.GoNext();

	EXPECT_EQ(0, tab.IsTabEnded());
}

//TSortTable

TEST(TSortTable, can_create)
{
	TSortTable *tab;

	ASSERT_NO_THROW(tab = new TSortTable(50));
}

TEST(TSortTable, chek_operator_equal)
{
	TSortTable tabSort;
	TScanTable tab(5);
	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("2", (PTDatValue)2);
	tab.InsRecord("3", (PTDatValue)3);

	bool flag= true;
	tabSort = tab;
	for (tab.Reset(), tabSort.Reset(); tab.IsTabEnded(),
		tabSort.IsTabEnded(); tab.GoNext(), tabSort.GoNext())
		if (tab.GetKey() != tabSort.GetKey() ||
			tab.GetValuePTR() == tabSort.GetValuePTR())
			flag = false;

	EXPECT_EQ(true, flag);
}

TEST(TSortTable, can_ins_rec)
{
	TSortTable tab(5);

	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("2", (PTDatValue)2);
	tab.InsRecord("3", (PTDatValue)3);

	EXPECT_EQ(TabOK, tab.GetRetCode());
}

TEST(TSortTable, can_ins_rec_and_chek_sort)
{
	TSortTable tab(5);

	
	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("3", (PTDatValue)3);
	tab.InsRecord("4", (PTDatValue)4);
	tab.InsRecord("2", (PTDatValue)2);

	tab.SetCurrentPos(3);

	EXPECT_EQ("4", tab.GetKey());
}

TEST(TSortTable, can_ins_rec_and_heek_datacount)
{
	TSortTable tab(5);


	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("3", (PTDatValue)3);
	tab.InsRecord("4", (PTDatValue)4);
	tab.InsRecord("2", (PTDatValue)2);

	EXPECT_EQ(4, tab.GetDataCount());
}

TEST(TSortTable, can_del_rec)
{
	TSortTable tab(5);

	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("3", (PTDatValue)3);
	tab.InsRecord("4", (PTDatValue)4);
	tab.InsRecord("2", (PTDatValue)2);

	tab.DelRecord("2");

	EXPECT_EQ(TabOK, tab.GetRetCode());
}

TEST(TSortTable, can_ins_after_del_rec)
{
	TSortTable tab(5);

	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("3", (PTDatValue)3);
	tab.InsRecord("4", (PTDatValue)4);
	tab.InsRecord("2", (PTDatValue)2);

	tab.DelRecord("2");

	tab.InsRecord("2", (PTDatValue)4);
	tab.InsRecord("8", (PTDatValue)2);


	EXPECT_EQ(TabOK, tab.GetRetCode());
}

TEST(TSortTable, can_del_rec_and_chek_datacount)
{
	TSortTable tab(5);
	
	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("3", (PTDatValue)3);
	tab.InsRecord("4", (PTDatValue)4);
	tab.InsRecord("2", (PTDatValue)2);

	tab.DelRecord("4");

	EXPECT_EQ(3, tab.GetDataCount());
}

TEST(TSortTable, can_del_rec_whose_is_not)
{
	TSortTable tab(5);

	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("3", (PTDatValue)3);
	tab.InsRecord("4", (PTDatValue)4);
	tab.InsRecord("2", (PTDatValue)2);

	tab.DelRecord("5");

	EXPECT_EQ(TabNoRec, tab.GetRetCode());
}

TEST(TSortTable, can_del_rec_if_tab_empty)
{
	TSortTable tab(5);
	
	tab.DelRecord("5");

	EXPECT_EQ(TabEmpty, tab.GetRetCode());
}

TEST(TSortTable, chek_sort_merge)
{
	TSortTable tabSort(5);

	TScanTable tab(5);

	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("5", (PTDatValue)5);
	tab.InsRecord("3", (PTDatValue)3);
	tab.InsRecord("4", (PTDatValue)4);
	tab.InsRecord("2", (PTDatValue)2);

	tabSort.SetSortMethod(MERGE_SORT);
	tabSort = tab;
	int i = 1;
	bool flag = true;
	for (tabSort.Reset(); tabSort.IsTabEnded(); tabSort.GoNext(), i++)
		if (tabSort.GetValuePTR() != (PTDatValue)i)
			flag = false;

	EXPECT_EQ(true, flag);
}

TEST(TSortTable, chek_sort_quick)
{
	TSortTable tabSort(5);

	TScanTable tab(5);

	tab.InsRecord("1", (PTDatValue)1);
	tab.InsRecord("5", (PTDatValue)5);
	tab.InsRecord("3", (PTDatValue)3);
	tab.InsRecord("4", (PTDatValue)4);
	tab.InsRecord("2", (PTDatValue)2);

	tabSort.SetSortMethod(QUICK_SORT);
	tabSort = tab;
	int i = 1;
	bool flag = true;
	for (tabSort.Reset(); tabSort.IsTabEnded(); tabSort.GoNext(), i++)
		if (tabSort.GetValuePTR() != (PTDatValue)i)
			flag = false;

	EXPECT_EQ(true, flag);
}

//TTreeTable

TEST(TTreeTable, can_create)
{
	TTreeTable *tab;
	
	ASSERT_NO_THROW(tab = new TTreeTable());
}

TEST(TTreeTable, can_insert_rec)
{
	TTreeTable *tab;

	tab = new TTreeTable();

	tab->InsRecord("1", (PTDatValue)1);
	tab->InsRecord("2", (PTDatValue)1);
	tab->InsRecord("3", (PTDatValue)1);
	tab->Reset();
	tab->GoNext();
	
	EXPECT_EQ("2", tab->GetKey());
}

TEST(TTreeTable, can_insert_rec_if_rec_dbl)
{
	TTreeTable *tab;

	tab = new TTreeTable();

	tab->InsRecord("1", (PTDatValue)1);
	tab->InsRecord("2", (PTDatValue)1);
	tab->InsRecord("2", (PTDatValue)1);
	
	EXPECT_EQ(TabRecDbl, tab->GetRetCode());
}

TEST(TTreeTable, can_del_rec_if_no_rec)
{
	TTreeTable *tab;

	tab = new TTreeTable();

	tab->InsRecord("1", (PTDatValue)1);
	tab->InsRecord("2", (PTDatValue)1);
	tab->InsRecord("3", (PTDatValue)1);

	
	tab->DelRecord("5");
	
	EXPECT_EQ(3, tab->GetDataCount());
}

TEST(TTreeTable, can_del_rec)
{
	TTreeTable *tab;

	tab = new TTreeTable();

	tab->InsRecord("1", (PTDatValue)1);
	tab->InsRecord("2", (PTDatValue)1);
	tab->InsRecord("3", (PTDatValue)1);
	
	tab->DelRecord("3");
		
	EXPECT_EQ(nullptr, tab->FindRecord("3"));
}

TEST(TTreeTable, can_del_rec_if_tab_empty)
{
	TTreeTable *tab;

	tab = new TTreeTable();
	
	tab->DelRecord("3");
		
	EXPECT_EQ(TabEmpty, tab->GetRetCode());
}

TEST(TTreeTable, can_del_root)
{
	TTreeTable *tab;

	tab = new TTreeTable();

	tab->InsRecord("2", (PTDatValue)1);
	tab->InsRecord("1", (PTDatValue)1);
	tab->InsRecord("3", (PTDatValue)1);
	
	tab->DelRecord("2");
	tab->Reset();
	tab->GoNext();
		
	EXPECT_EQ("3", tab->GetKey());
}

TEST(TTreeTable, can_del_rec_with_two_child)
{
	TTreeTable *tab;

	tab = new TTreeTable();
	
	tab->InsRecord("10", (PTDatValue)1);
	tab->InsRecord("13", (PTDatValue)1);
	tab->InsRecord("11", (PTDatValue)1);
	tab->InsRecord("12", (PTDatValue)1);
	tab->InsRecord("1", (PTDatValue)1);
	tab->InsRecord("25", (PTDatValue)1);
	
	tab->DelRecord("13");

	EXPECT_EQ(nullptr, tab->FindRecord("13"));
}

TEST(TTreeTable, can_del_rec_with_two_child_chek_order)
{
	TTreeTable *tab;

	tab = new TTreeTable();

	tab->InsRecord("10", (PTDatValue)1);
	tab->InsRecord("13", (PTDatValue)1);
	tab->InsRecord("11", (PTDatValue)1);
	tab->InsRecord("12", (PTDatValue)1);
	tab->InsRecord("1", (PTDatValue)1);
	tab->InsRecord("25", (PTDatValue)1);

	tab->DelRecord("13");
	tab->Reset(); //1
	tab->GoNext();//10
	tab->GoNext(); //11
	tab->GoNext();//12
	tab->GoNext();//25

	EXPECT_EQ("25", tab->GetKey());
}

TEST(TTreeTable, can_del_rec_with_one_left_child)
{
	TTreeTable *tab;

	tab = new TTreeTable();

	tab->InsRecord("10", (PTDatValue)1);
	tab->InsRecord("13", (PTDatValue)1);
	tab->InsRecord("11", (PTDatValue)1);
	tab->InsRecord("12", (PTDatValue)1);
	tab->InsRecord("1", (PTDatValue)1);
	tab->InsRecord("0", (PTDatValue)1);
	tab->InsRecord("25", (PTDatValue)1);

	tab->DelRecord("1");

	EXPECT_EQ(nullptr, tab->FindRecord("1"));
}

TEST(TTreeTable, can_del_rec_with_one_left_cild_chek_order)
{
	TTreeTable *tab;

	tab = new TTreeTable();

	tab->InsRecord("10", (PTDatValue)1);
	tab->InsRecord("13", (PTDatValue)1);
	tab->InsRecord("11", (PTDatValue)1);
	tab->InsRecord("12", (PTDatValue)1);
	tab->InsRecord("1", (PTDatValue)1);
	tab->InsRecord("25", (PTDatValue)1);
	tab->InsRecord("20", (PTDatValue)1);

	tab->DelRecord("25");
	tab->Reset();//1
	tab->GoNext();//10
	tab->GoNext();//11
	tab->GoNext();//12
	tab->GoNext();//13
	tab->GoNext();// 20	

	EXPECT_EQ("20", tab->GetKey());
}

TEST(TTreeTable, can_del_rec_with_one_right_child)
{
	TTreeTable *tab;

	tab = new TTreeTable();

	tab->InsRecord("10", (PTDatValue)1);
	tab->InsRecord("13", (PTDatValue)1);
	tab->InsRecord("11", (PTDatValue)1);
	tab->InsRecord("12", (PTDatValue)1);
	tab->InsRecord("1", (PTDatValue)1);
	tab->InsRecord("0", (PTDatValue)1);
	tab->InsRecord("25", (PTDatValue)1);

	tab->DelRecord("11");

	EXPECT_EQ(nullptr, tab->FindRecord("11"));
}

TEST(TTreeTable, can_del_rec_with_one_right_child_chek_order)
{
	TTreeTable *tab;

	tab = new TTreeTable();

	tab->InsRecord("10", (PTDatValue)1);
	tab->InsRecord("13", (PTDatValue)1);
	tab->InsRecord("11", (PTDatValue)1);
	tab->InsRecord("12", (PTDatValue)1);
	tab->InsRecord("1", (PTDatValue)1);
	tab->InsRecord("25", (PTDatValue)1);
	tab->InsRecord("20", (PTDatValue)1);

	tab->DelRecord("11");
	tab->Reset();//1
	tab->GoNext();//10
	tab->GoNext();//���� 11 ����� 12

	EXPECT_EQ("12", tab->GetKey());
}

TEST(TTreeTable, can_ins_after_del)
{
	TTreeTable *tab;

	tab = new TTreeTable();

	tab->InsRecord("10", (PTDatValue)1);
	tab->InsRecord("16", (PTDatValue)1);
	tab->InsRecord("12", (PTDatValue)1);
	tab->InsRecord("15", (PTDatValue)1);
	tab->InsRecord("1", (PTDatValue)1);
	tab->InsRecord("25", (PTDatValue)1);
	tab->InsRecord("20", (PTDatValue)1);

	tab->DelRecord("12");
	tab->InsRecord("11", (PTDatValue)1);
	tab->Reset();//1
	tab->GoNext();//10
	tab->GoNext();//���� 12 ����� 11

	EXPECT_EQ("11", tab->GetKey());
}

//TBallTree

TEST(TBalanceTree, can_create)
{
	TBalanceTree *tab;
	
	ASSERT_NO_THROW(tab = new TBalanceTree());
}

TEST(TBalanceTree, can_insert_rec)
{
	TBalanceTree *tab = new TBalanceTree();

	tab->InsRecord("1", (PTDatValue)1);
	tab->Reset();

	EXPECT_EQ("1", tab->GetKey());
}

TEST(TBalanceTree, can_not_del_rec_if_tab_empty)
{
	TBalanceTree *tab = new TBalanceTree();

	tab->DelRecord("1");

	EXPECT_EQ(TabEmpty,tab->GetRetCode());
}

TEST(TBalanceTree, can_del_rec_without_child_chek_order)
{
	TBalanceTree *tab = new TBalanceTree();

	tab->InsRecord("3", (PTDatValue)1);
	tab->InsRecord("2", (PTDatValue)1);
	tab->InsRecord("1", (PTDatValue)1);
	tab->InsRecord("6", (PTDatValue)1);
	tab->InsRecord("7", (PTDatValue)1);
	tab->InsRecord("4", (PTDatValue)1);
	tab->InsRecord("5", (PTDatValue)1);

	tab->DelRecord("1");
	tab->Reset();//���� 1����� 2	

	EXPECT_EQ("2", tab->GetKey());
}

TEST(TBalanceTree, can_del_rec_without_child)
{
	TBalanceTree *tab = new TBalanceTree();

	tab->InsRecord("1", (PTDatValue)1);
	tab->InsRecord("2", (PTDatValue)1);
	tab->InsRecord("3", (PTDatValue)1);
	tab->InsRecord("4", (PTDatValue)1);
	tab->InsRecord("5", (PTDatValue)1);
	tab->InsRecord("6", (PTDatValue)1);
	tab->InsRecord("7", (PTDatValue)1);

	tab->DelRecord("1");

	EXPECT_EQ(nullptr, tab->FindRecord("1"));
}

TEST(TBalanceTree, can_del_rec_with_one_left_child_chek_order)
{
	TBalanceTree *tab = new TBalanceTree();

	tab->InsRecord("3", (PTDatValue)1);
	tab->InsRecord("2", (PTDatValue)1);
	tab->InsRecord("1", (PTDatValue)1);
	tab->InsRecord("6", (PTDatValue)1);
	tab->InsRecord("7", (PTDatValue)1);
	tab->InsRecord("4", (PTDatValue)1);
	tab->InsRecord("5", (PTDatValue)1);

	tab->DelRecord("2");
	tab->Reset();//1
	tab->GoNext();//3


	EXPECT_EQ("3", tab->GetKey());
}

TEST(TBalanceTree, can_del_rec_with_one_left_child)
{
	TBalanceTree *tab = new TBalanceTree();

	tab->InsRecord("3", (PTDatValue)1);
	tab->InsRecord("2", (PTDatValue)1);
	tab->InsRecord("1", (PTDatValue)1);
	tab->InsRecord("6", (PTDatValue)1);
	tab->InsRecord("7", (PTDatValue)1);
	tab->InsRecord("4", (PTDatValue)1);
	tab->InsRecord("5", (PTDatValue)1);

	tab->DelRecord("2");

	EXPECT_EQ(nullptr, tab->FindRecord("2"));
}

TEST(TBalanceTree, can_del_rec_with_one_right_child_chek_order)
{
	TBalanceTree *tab = new TBalanceTree();

	tab->InsRecord("3", (PTDatValue)1);
	tab->InsRecord("2", (PTDatValue)1);
	tab->InsRecord("1", (PTDatValue)1);
	tab->InsRecord("6", (PTDatValue)1);
	tab->InsRecord("7", (PTDatValue)1);
	tab->InsRecord("4", (PTDatValue)1);
	tab->InsRecord("5", (PTDatValue)1);

	tab->DelRecord("4");
	tab->Reset();//1
	tab->GoNext();//2
	tab->GoNext();//3
	tab->GoNext();//5

	EXPECT_EQ("5", tab->GetKey());
}

TEST(TBalanceTree, can_del_rec_with_one_right_child)
{
	TBalanceTree *tab = new TBalanceTree();

	tab->InsRecord("3", (PTDatValue)1);
	tab->InsRecord("2", (PTDatValue)1);
	tab->InsRecord("1", (PTDatValue)1);
	tab->InsRecord("6", (PTDatValue)1);
	tab->InsRecord("7", (PTDatValue)1);
	tab->InsRecord("4", (PTDatValue)1);
	tab->InsRecord("5", (PTDatValue)1);

	tab->DelRecord("4");

	EXPECT_EQ(nullptr, tab->FindRecord("4"));
}

//TArrayHach

TEST(TArrayHash, can_create_default)
{
	TArrayHash *tab;

	ASSERT_NO_THROW(tab = new TArrayHash());
}

TEST(TArrayHash, can_create_with_incorrect_size)
{
	TArrayHash *tab;

	ASSERT_ANY_THROW(tab = new TArrayHash(-1));
}

TEST(TArrayHash, can_create_with_step_larger_size)
{
	TArrayHash *tab;

	ASSERT_ANY_THROW(tab = new TArrayHash(10, 15));
}

TEST(TArrayHash, can_create_with_incorrect_step)
{
	TArrayHash *tab;

	ASSERT_ANY_THROW(tab = new TArrayHash(10, 1));
}

TEST(TArrayHash, can_ins_rec)
{
	TArrayHash tab(10, 3);

	tab.InsRecord("Petrov",(PTDatValue)1);

	EXPECT_EQ(tab.FindRecord("Petrov"),(PTDatValue)1);
}

TEST(TArrayHash, can_ins_rec_dbl)
{
	TArrayHash tab(10, 3);

	tab.InsRecord("Petrov", (PTDatValue)1);
	tab.InsRecord("Petrov", (PTDatValue)1);

	EXPECT_EQ(TabRecDbl, tab.GetRetCode());
}

TEST(TArrayHash, can_not_ins_rec_if_tab_full)
{
	TArrayHash tab(3, 2);

	tab.InsRecord("Petrov", (PTDatValue)1);
	tab.InsRecord("Vetrov", (PTDatValue)2);
	tab.InsRecord("Ivanov", (PTDatValue)3);
	tab.InsRecord("Pupkin", (PTDatValue)3);

	EXPECT_EQ(tab.FindRecord("Pupkin"), nullptr);
}

TEST(TArrayHash, chek_empty_after_del_all_rec)
{
	TArrayHash tab(5,2);

	tab.InsRecord("Petrov", (PTDatValue)1);
	tab.InsRecord("Petrov1", (PTDatValue)1);
	tab.InsRecord("Petrov2", (PTDatValue)1);
	tab.InsRecord("Petrov3", (PTDatValue)1);
	tab.InsRecord("Petrov4", (PTDatValue)1);

	tab.DelRecord("Petrov");
	tab.DelRecord("Petrov1");
	tab.DelRecord("Petrov2");
	tab.DelRecord("Petrov3");
	tab.DelRecord("Petrov4");

	EXPECT_EQ(true, tab.IsEmpty());
}

TEST(TArrayHash, chek_full_after_ins_all_rec)
{
	TArrayHash tab(5, 2);

	tab.InsRecord("Petrov", (PTDatValue)1);
	tab.InsRecord("Petrov1", (PTDatValue)1);
	tab.InsRecord("Petrov2", (PTDatValue)1);
	tab.InsRecord("Petrov3", (PTDatValue)1);
	tab.InsRecord("Petrov4", (PTDatValue)1);

	EXPECT_EQ(true, tab.IsFull());
}

TEST(TArrayHash, can_not_del_if_tab_empty)
{
	TArrayHash tab(5, 2);

	tab.DelRecord("Petrov");

	EXPECT_EQ(TabEmpty, tab.GetRetCode());
}

TEST(TArrayHash, can_not_find_if_tab_empty)
{
	TArrayHash tab(5, 2);

	tab.FindRecord("Petrov");

	EXPECT_EQ(TabEmpty, tab.GetRetCode());
}

TEST(TArrayHash, chek_ended_tab)
{
	TArrayHash tab(5, 2);

	tab.InsRecord("Petrov", (PTDatValue)1);
	tab.InsRecord("Ivanov", (PTDatValue)2);
	tab.InsRecord("Vetrov", (PTDatValue)1);
	tab.InsRecord("Pupkin", (PTDatValue)2);
	tab.InsRecord("Sorin", (PTDatValue)2);

	tab.Reset();//Petrov
	tab.GoNext();//Ivanov
	tab.GoNext();//Vetrov
	tab.GoNext();//Pupkin
	tab.GoNext();//Sorin
	tab.GoNext();

	EXPECT_EQ(tab.IsTabEnded(), true );
}

//TListHas

TEST(TListHash, can_create_default)
{
	TListHash *tab;

	ASSERT_NO_THROW(tab = new TListHash());
}

TEST(TListHash, can_not_create_with_negative_size)
{
	TListHash *tab;

	ASSERT_ANY_THROW(tab = new TListHash(-5));
}

TEST(TListHash, can_create)
{
	TListHash *tab;
	
	ASSERT_NO_THROW(tab = new TListHash(5));
}

TEST(TListHash, can_ins_rec)
{
	TListHash tab(5);

	tab.InsRecord("Petrov", (PTDatValue)1);

	EXPECT_EQ(tab.FindRecord("Petrov"), (PTDatValue)1);
}

TEST(TListHash, can_ins_rec_dbl)
{
	TListHash tab(5);

	tab.InsRecord("Petrov", (PTDatValue)1);
	tab.InsRecord("Petrov", (PTDatValue)1);

	EXPECT_EQ(TabRecDbl, tab.GetRetCode());
}

TEST(TListHash, can_find_rec)
{
	TListHash tab(5);

	tab.InsRecord("Petrov", (PTDatValue)1);
	tab.InsRecord("Ivanov", (PTDatValue)2);

	EXPECT_EQ(tab.FindRecord("Petrov"), (PTDatValue)1);
}

TEST(TListHash, can_del_rec)
{
	TListHash tab(5);

	tab.InsRecord("Petrov", (PTDatValue)1);
	tab.InsRecord("Ivanov", (PTDatValue)2);

	tab.DelRecord("Petrov");

	EXPECT_EQ(tab.FindRecord("Petrov"), nullptr);
}

TEST(TListHash, can_del_rec_whose_no)
{
	TListHash tab(5);

	tab.InsRecord("Petrov", (PTDatValue)1);
	tab.InsRecord("Ivanov", (PTDatValue)2);

	tab.DelRecord("Vetrov");

	EXPECT_EQ(TabNoRec, tab.GetRetCode());
}

TEST(TListHash, can_del_rec_if_tab_empty)
{
	TListHash tab(5);	

	tab.DelRecord("Vetrov");

	EXPECT_EQ(TabEmpty, tab.GetRetCode());
}

TEST(TListHash, check_tab_empty_after_del)
{
	TListHash tab(5);

	tab.InsRecord("Petrov", (PTDatValue)1);
	tab.InsRecord("Ivanov", (PTDatValue)2);
	tab.InsRecord("Vetrov", (PTDatValue)1);
	tab.InsRecord("Pupkin", (PTDatValue)2);

	tab.DelRecord("Vetrov");
	tab.DelRecord("Ivanov");
	tab.DelRecord("Petrov");
	tab.DelRecord("Pupkin");

	EXPECT_EQ(true, tab.IsEmpty());
}

TEST(TListHash, can_not_find_if_tab_empty)
{
	TListHash tab(5);

	tab.FindRecord("");

	EXPECT_EQ(tab.GetRetCode(), TabEmpty);
}

TEST(TListHash, check_ended_tab)
{
	TListHash tab(5);

	tab.InsRecord("Petrov", (PTDatValue)1);
	tab.InsRecord("Ivanov", (PTDatValue)2);
	tab.InsRecord("Vetrov", (PTDatValue)1);
	tab.InsRecord("Pupkin", (PTDatValue)2);
	tab.InsRecord("Sorin", (PTDatValue)2);

	tab.Reset();//Petrov
	tab.GoNext();//Ivanov
	tab.GoNext();//Vetrov
	tab.GoNext();//Pupkin
	tab.GoNext();//Sorin
	tab.GoNext();

	EXPECT_EQ(tab.IsTabEnded(), true);

}