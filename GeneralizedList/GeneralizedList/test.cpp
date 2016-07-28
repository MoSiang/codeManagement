#include"GeneralizedList.h"

void Test()
{
	GeneralizedList g("(1,(2,3),6,7,7)");
	g.Print();

	cout << "size:" <<endl;
	cout<< g.Size() <<endl;

	cout << "depth:" <<endl;
	cout << g.Depth() <<endl;

	cout<< "拷贝构造后:" <<endl;
	GeneralizedList g1(g);
	g1.Print();

	cout << "赋值后:"<<endl;
	GeneralizedList g2 = g;
	g2.Print();
}
int main()
{
	Test();
	getchar();
	return 0;
}