#include"BinaryTree.hpp"

void Test()
{
	int array1[10] = {1,2,3,'#','#',4,'#','#',5,6};
	BinaryTree<int> bt1(array1,10,'#');

	cout << "前序遍历" <<endl;
	bt1.PrevOrder();

	cout << "中序遍历" <<endl;
	bt1.InOrder();

	cout << "后序遍历" <<endl;
	bt1.PosOrder();

	/*cout << "层序遍历" <<endl;
	bt1.LevelOrder();*/

	cout << "树的叶子节点数" <<endl;
	cout << bt1.LeafSize() <<endl;

	cout << "树的总节点数" <<endl;
	cout << bt1.Size() <<endl;

	cout << "树的深度" <<endl;
	cout << bt1.Depth() <<endl;

	cout << "拷贝构造" <<endl;
	BinaryTree<int> bt2(bt1);
	cout << "前序遍历" <<endl;
	bt2.PrevOrder();

	cout << "赋值" <<endl;
	BinaryTree<int> bt3 = bt1;
	cout << "前序遍历" <<endl;
	bt3.PrevOrder();

	cout << "非递归前序遍历" <<endl;
	bt1.PrevOrder();

	cout << "非递归中序遍历" <<endl;
	bt1.InOrder();

	cout << "非递归后序遍历" <<endl;
	bt1.PosOrder();

	cout << bt1.Find(3)->_data <<endl;
	cout << bt1.GetKLevel(2)<<endl;
}
int main()
{
	Test();
	getchar();
	return 0;
}