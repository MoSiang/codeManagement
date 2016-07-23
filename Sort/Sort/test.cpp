#include"Sort.h"
#include<time.h>
#include<windows.h>

void TestInsertSort()
{
	int array[] = {2,5,6,9,1,3,4,7,8,0};
	InsertSort(array,sizeof(array)/sizeof(array[0]));
	for(int i = 0; i<sizeof(array)/sizeof(array[0]); i++)
	{
		cout<<array[i] <<" " ;
	}
	cout <<endl;
}
void TestShellSort()
{
	int array[] = {2,5,6,9,1,3,4,7,8,0};
	ShellSort(array,sizeof(array)/sizeof(array[0]));
	for(int i = 0; i<sizeof(array)/sizeof(array[0]); i++)
	{
		cout<<array[i] <<" " ;
	}
	cout <<endl;
}
void TestSelectSort()
{
	int array[] = {2,5,6,9,1,3,4,7,8,0};
	SelectSort(array,sizeof(array)/sizeof(array[0]));
	for(int i = 0; i<sizeof(array)/sizeof(array[0]); i++)
	{
		cout<<array[i] <<" " ;
	}
	cout <<endl;
}
void TestSelectSortOP1()
{
	int array1[] = {2,5,6,9,1,3,4,7,8,0};
	int array2[] = {2,5,6,9,1,3,4,7,0,8};
	SelectSortOP1(array1,sizeof(array1)/sizeof(array1[0]));
	for(int i = 0; i<sizeof(array1)/sizeof(array1[0]); i++)
	{
		cout<<array1[i] <<" " ;
	}
	cout <<endl;

	SelectSortOP1(array2,sizeof(array2)/sizeof(array2[0]));
	for(int i = 0; i<sizeof(array2)/sizeof(array2[0]); i++)
	{
		cout<<array2[i] <<" " ;
	}
	cout <<endl;
}
void TestSelectSortOP2()
{
	int array1[] = {2,5,6,9,1,3,4,7,8,0};
	int array2[] = {2,5,6,9,1,3,4,7,0,8};
	SelectSortOP2(array1,sizeof(array1)/sizeof(array1[0]));
	for(int i = 0; i<sizeof(array1)/sizeof(array1[0]); i++)
	{
		cout<<array1[i] <<" " ;
	}
	cout <<endl;

	SelectSortOP2(array2,sizeof(array2)/sizeof(array2[0]));
	for(int i = 0; i<sizeof(array2)/sizeof(array2[0]); i++)
	{
		cout<<array2[i] <<" " ;
	}
	cout <<endl;
}
void TestHeapSort()
{
	int array[] = {2,5,6,9,1,3,4,7,8,0};
	HeapSort(array,sizeof(array)/sizeof(array[0]));
	for(int i = 0; i<sizeof(array)/sizeof(array[0]); i++)
	{
		cout<<array[i] <<" " ;
	}
	cout <<endl;
}
void TestBubbleSort()
{
	int array[] = {2,5,6,9,1,3,4,7,8,0};
	BubbleSort(array,sizeof(array)/sizeof(array[0]));
	for(int i = 0; i<sizeof(array)/sizeof(array[0]); i++)
	{
		cout<<array[i] <<" " ;
	}
	cout <<endl;
}
void TestQuickSort()
{
	int array[] = {2,5,6,9,1,3,4,7,0,8};
	QuickSort(array,0,sizeof(array)/sizeof(array[0])-1);
	for(int i = 0; i<sizeof(array)/sizeof(array[0]); i++)
	{
		cout<<array[i] <<" " ;
	}
	cout <<endl;
}
void TestQuickSort_OP()
{
	const int N = 10000000;
	int* a = new int[N];
	srand(time(0));
	for(int i = 0; i<N; i++)
	{
		a[i] = rand()%N;
	}
	int begin = GetTickCount();
	QuickSort_OP(a, 0, N-1);
	int end = GetTickCount();
	cout << "花费的时间："<<end - begin <<endl;
}
void TestQuickSort_NONR()
{
	int array[] = {2,5,6,9,1,3,4,7,0,8};
	QuickSort_NONR(array,0,sizeof(array)/sizeof(array[0])-1);
	for(int i = 0; i<sizeof(array)/sizeof(array[0]); i++)
	{
		cout<<array[i] <<" " ;
	}
	cout <<endl;
}

void TestMergeSort()
{
	int array[] = {2,5,6,9,1,3,4,7,0,8};
	MergeSort(array,sizeof(array)/sizeof(array[0]));
	for(int i = 0; i<sizeof(array)/sizeof(array[0]); i++)
	{
		cout<<array[i] <<" " ;
	}
	cout <<endl;
}

void TestLSDSort()
{
	int array[] = {2,5,6,9,1,3,4,7,0,8};
	LSDSort(array,sizeof(array)/sizeof(array[0]));
	for(int i = 0; i<sizeof(array)/sizeof(array[0]); i++)
	{
		cout<<array[i] <<" " ;
	}
	cout <<endl;
}
void TestCountSort()
{
	int array[] = {2,5,6,9,1,3,4,7,0,8};
	CountSort(array,sizeof(array)/sizeof(array[0]));
	for(int i = 0; i<sizeof(array)/sizeof(array[0]); i++)
	{
		cout<<array[i] <<" " ;
	}
	cout <<endl;
}
int main()
{
	//TestInsertSort();
	//TestShellSort();
	//TestSelectSort();
	//TestSelectSortOP1();
	//TestSelectSortOP2();
	//TestHeapSort();
	//TestBubbleSort();
	//TestQuickSort();
	//TestQuickSort_OP();
	//TestQuickSort_NONR();
	//TestMergeSort();
	//TestLSDSort();
	TestCountSort();
	getchar();
	return 0;
}