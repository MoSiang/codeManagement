#pragma once

#include<iostream>

#include<vector>
#include<cassert>

using namespace std;

template<class T>
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
		//����
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
		size_t child = parent*2+1;
		while(child < _a.size())
		{
			//ѡ�����Һ����нϴ��
			if(child+1 < _a.size() &&
				_a[child] < _a[child+1])
			{
				++child;
			}
			//������ӱȸ��״��򽻻������¼�����
			if(_a[child] > _a[parent])
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
		size_t parent = (child-1)/2;
		while(child > 0)
		{
			if(_a[child] > _a[parent])
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
	//ʱ�临�Ӷ�o(lgN)
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