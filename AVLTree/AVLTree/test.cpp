#include"AVLTree.h"
#include<iostream>

using namespace std;

void TestAVLTree()
{
	AVLTree<int, int> t;
	//int a[] = { 8, 1, 3, 6, 7, 4, 2, 9, 5 };
	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 9, 14 , 15};//Á½¸ö9
	int a[] = {4,2, 6, 1, 3, 5, 15, 7, 16, 14};
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		cout << t.Insert(a[i], i) << " ";
	}
	cout << endl;

	t.InOrder();
}
int main()
{
	TestAVLTree();
	getchar();
	return 0;
}