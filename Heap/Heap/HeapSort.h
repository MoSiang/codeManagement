#pragma once

#include<iostream>
#include<cassert>

using namespace std;
void _AdjustDown(int a[], int n,int parent)
{
	int child = parent*2+1;
	while(child < n)
	{
		if(child + 1 < n &&
			a[child+1] > a[child])
		{
			++child;
		}
		if(a[child] > a[parent])
		{
			swap(a[child],a[parent]);
			parent = child;
			child = parent * 2 +1;
		}
		else
		{
			break;
		}
	}
}
void HeapSort(int a[],int n)
{
	assert(a);
	for(int i = (n-2)/2; i>=0; i--)
	{
		_AdjustDown(a,n,i);
	}
	for(int i = n-1; i>=0; i--)
	{
		int tmp = a[0];
		a[0] = a[i];
		a[i] = tmp;
		_AdjustDown(a,i,0);
	}

}
