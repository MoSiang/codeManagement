#include "BTree.h"
#include <iostream>

using namespace std;

void TestBTree()
{
	int a[] = {53, 75,139,49,145,36,101};
	BTree<int, 3> t;
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		t.Insert(a[i]);
	}

	t.Inorder();
}
int main()
{
	TestBTree();
	getchar();
	return 0;
}