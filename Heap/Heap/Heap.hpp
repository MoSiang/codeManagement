#pragma once

#include<iostream>
#include<vector>
#include<cassert>

using namespace std;

template<class T>
struct Greater
{
	bool operator()(const T& l, const T&r)
	{
		return l > r;
	}
};
template<class T>
struct Less
{
	bool operator()(const T& l, const T&r)
	{
		return l < r;
	}
};

template<class T,class Compare = Greater<T>>
class Heap
{
public:
	Heap()
	{}
	Heap(const T*a,size_t size)
	{
		assert(a);
		for(size_t i=0; i<size; i++)
		{
			_a.push_back(a[i]);
		}
		//建堆
		for(int i=(_a.size()-2)/2; i>=0; i--)
		{
			_AdjustDown(i);
		}
	}

	void push(const T& x)
	{
		_a.push_back(x);
		_AdjustUp(_a.size()-1);
	}
	void pop()
	{
		assert(!_a.empty());
		swap(_a[0],_a[size-1]);
		_a.pop_back();
		_AdjustDown(0);
	}
protected:
	void _AdjustDown(size_t parent)
	{
		Compare com;
		size_t child = parent*2+1;
		while(child < _a.size())
		{
			//选出左右孩子中较大的
			if(child+1 < _a.size() &&
				com(_a[child+1],_a[child]))
			{
				++child;
			}
			//如果孩子比父亲大，则交换并向下继续走
			if(com(_a[child], _a[parent]))
			{
				swap(_a[child],_a[parent]);
				parent = child;
				child = parent*2+1;
			}
			else
			{
				break;
			}
		}
	}
	void _AdjustUp(size_t child)
	{
		Compare com;
		size_t parent = (child-1)/2;
		while(child > 0)
		{
			if(com(_a[child], _a[parent]))
			{
				swap(_a[child],_a[parent]);
				child  = parent;
				parent = (child-1)/2;
			}
			else
			{
				break;
			}
		}
	}
protected:
	vector<T> _a;
};

 
template<class T>
class PrioryQueue
{
public:
	//时间复杂度o(lgN)
	void push(const T& x)
	{
		h.push(x);
	}
	void pop()
	{
		h.pop();
	}
private:
	Heap<T> h;
};