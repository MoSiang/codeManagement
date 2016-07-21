#include"BSTree.h"

void TestTree()
{
	int array[] = {5,3,4,1,7,8,2,6,0,9};
	BSTree<int, int> t;
	for(size_t i = 0; i<sizeof(array)/sizeof(array[0]); i++)
	{
		t.Insert(array[i],i);
	}
	cout <<endl;

	//t.InOrder();

	//cout << t.Find(6)->_key << ":" << t.Find(6)->_value << endl;
	//cout << t.Find(10)->_key << ":" << t.Find(6)->_value << endl;

	/*t.Remove(5);
	t.InOrder();
	t.Remove(4);
	t.InOrder();
	t.Remove(3);
	t.InOrder();
	t.Remove(2);
	t.InOrder();
	t.Remove(1);
	t.InOrder();
	t.Remove(0);
	t.InOrder();
	t.Remove(6);
	t.InOrder();
	t.Remove(7);
	t.InOrder();
	t.Remove(8);
	t.InOrder();
	t.Remove(9);
	t.InOrder();*/


	//t.InsertR(10,3);
	//t.InOrder();

	//cout << t.FindR(7)->_key <<endl;
	//cout << t.FindR(22)->_key <<endl;

	t.RemoveR(9);
	t.InOrder();
}
int main()
{
	TestTree();
	getchar();
	return 0;
}