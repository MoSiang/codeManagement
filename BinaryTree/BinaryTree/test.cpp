#include"BinaryTree.hpp"

void Test()
{
	int array1[10] = {1,2,3,'#','#',4,'#','#',5,6};
	BinaryTree<int> bt1(array1,10,'#');

	cout << "ǰ�����" <<endl;
	bt1.PrevOrder();

	cout << "�������" <<endl;
	bt1.InOrder();

	cout << "�������" <<endl;
	bt1.PosOrder();

	/*cout << "�������" <<endl;
	bt1.LevelOrder();*/

	cout << "����Ҷ�ӽڵ���" <<endl;
	cout << bt1.LeafSize() <<endl;

	cout << "�����ܽڵ���" <<endl;
	cout << bt1.Size() <<endl;

	cout << "�������" <<endl;
	cout << bt1.Depth() <<endl;

	cout << "��������" <<endl;
	BinaryTree<int> bt2(bt1);
	cout << "ǰ�����" <<endl;
	bt2.PrevOrder();

	cout << "��ֵ" <<endl;
	BinaryTree<int> bt3 = bt1;
	cout << "ǰ�����" <<endl;
	bt3.PrevOrder();

	cout << "�ǵݹ�ǰ�����" <<endl;
	bt1.PrevOrder();

	cout << "�ǵݹ��������" <<endl;
	bt1.InOrder();

	cout << "�ǵݹ�������" <<endl;
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