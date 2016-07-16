#include"BinaryTreeThd.hpp"

void Test()
{
	int array1[10] = {1,2,3,'#','#',4,'#','#',5,6};
	int array2[15] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8};

	//BinaryTreeThd<int> bt1(array1,10,'#');
	//bt1.InOrderThding();
	//bt1.InOrderThd();
	//bt1.PrevOrderThding();
	//bt1.PrevOrderThd();

	BinaryTreeThd<int> bt2(array2,15,'#');
	//bt2.InOrderThding();
	//bt2.InOrderThd();
	bt2.PrevOrderThding();
	bt2.PrevOrderThd();
}
int main()
{
	Test();
	getchar();
	return 0;
}