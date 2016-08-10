#include"RBTree.h"

#include<iostream>

using namespace std;

void TestRBTreeNode()
{

	int a[] = {5, 3, 9, 2, 1};
	RBTree<int, int> t;
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		t.Insert(a[i], i);
	}

	cout << t.CheckRBTree() << endl;

	cout << t[2] << endl;
	cout << t[5] << endl;
	cout << t[9] << endl;
}
int main()
{
	TestRBTreeNode();
	getchar();
	return 0;
}