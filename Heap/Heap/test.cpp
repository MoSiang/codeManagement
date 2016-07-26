#include"Heap.hpp"
//#include"RedPacket.h"
//#include<time.h>
//#include"HeapSort.h"

void TestHeap()
{
	int a[] = {10,11,13,12,16,18,15,17,14,19};
	Heap<int> h(a,sizeof(a)/sizeof(a[0]));
	h.push(25);
}
//void TestRedPacket()
//{
//	int a[N],topk[K];
//	srand(time(0));
//	for(int i = 0; i < N; i++)
//	{
//		a[i] = rand()%10000;
//	}
//	for(int i = N-K; i<N; i++)
//	{
//		a[i] = 10000+i;
//	}
//	GetTopK(a,topk);
//}
//void TestHeapSort()
//{
//	int a[] = {6,9,2,7,1,3,8,5,4};
//	HeapSort(a,sizeof(a)/sizeof(a[0]));
//	for(int i =0; i<sizeof(a)/sizeof(a[0]); i++)
//	{
//		cout<<a[i]<< " ";
//	}
//	cout <<endl;
//}
int main()
{
	TestHeap();
	//TestRedPacket();
	//TestHeapSort();
	getchar();
	return 0;
}