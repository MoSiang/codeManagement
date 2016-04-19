#include"Matrix.hpp"

//void TestSymmetricMatrix()
//{
//	int array[5][5] = 
//	{
//		{0,1,2,3,4},
//		{1,0,1,2,3},
//		{2,1,0,1,2},
//		{3,2,1,0,1},
//		{4,3,2,1,0}
//	};
//	SymmetricMatrix<int> sm((int*)array,5);
//	sm.Display();
//}


void TestSparseMatrix()
{
	int array[6][5]=
	{
		{1,0,3,0,5},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{2,0,4,0,6},
		{0,0,0,0,0},
		{0,0,0,0,0}
	};
	SparseMatrix<int> sm1((int*)array,6,5,0);
	sm1.Display();
	SparseMatrix<int> sm2 = sm1.Transport();
	sm2.Display();
	SparseMatrix<int> sm3 = sm1.FastTransport();
	sm3.Display();
}
int main()
{
	//TestSymmetricMatrix ();
	TestSparseMatrix();

	getchar();
	return 0;
}