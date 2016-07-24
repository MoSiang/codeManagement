#pragma once

#include<iostream>
#include<cassert>

using namespace std;

const int N = 10000;
const int K = 100;
void _AdjustDown(int topk[],int size,int parent)
{
	assert(topk);
	int child = parent*2+1;
	while(child < size)
	{
		if(child+1 < size &&
			topk[child+1] > topk[child])
		{
			++child;
		}
		if(topk[child] > topk[parent])
		{
			swap(topk[child],topk[parent]);
			child = parent;
			parent = child*2+1;
		}
		else
		{
			break;
		}
	}
}
void GetTopK(int a[],int topk[])
{
	assert(K<N);
	for(int i = 0; i<K; i++)
	{
		topk[i] = a[i];
	}
	//½¨¶Ñ
	for(int i = (K-2)/2; i>=0; i--)
	{
		_AdjustDown(topk,K,i);
	}
	for(int i = K; i<N; i++)
	{
		if(a[i] > topk[0])
		{
			topk[0] = a[i];
			_AdjustDown(topk,K,0);
		}
	}
	for(int i = 0; i<K; i++)
	{
		cout<<topk[i] << " ";
	}
	cout <<endl;
}
