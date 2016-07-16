#pragma once

#include<iostream>
#include<stack>

using namespace std;

enum PointerTag
{
	THREAD,
	LINK,
};

template<typename T>
struct BinaryTreeThdNode
{
	BinaryTreeThdNode(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
		,_leftTag(LINK)
		,_rightTag(LINK)
	{}
	T _data;
	BinaryTreeThdNode<T>* _left;//左孩子
	BinaryTreeThdNode<T>* _right;//右孩子
	PointerTag _leftTag;//左孩子线索标志
	PointerTag _rightTag;//右孩子线索标志
};

template<typename T>
class BinaryTreeThd
{
	typedef BinaryTreeThdNode<T> Node;
public:
	BinaryTreeThd()
		:_root(NULL)
	{}
	BinaryTreeThd(T* a, size_t size, const T& invalid)
	{
		size_t index = 0;
		_root = _CreateTree(a, size, index, invalid);
	}
	void PrevOrderThding()
	{
		Node* prev = NULL;
		_PrevOrderThding(_root,prev);
	}
	void PrevOrderThd()
	{
		Node* cur = _root;
		while(cur)
		{
			while(cur->_leftTag == LINK)
			{
				cout << cur->_data << " ";
				cur = cur->_left;
			}
			cout << cur->_data << " ";

			while(cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				cout << cur->_data << " ";
			}
			if(cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}
			else
			{
				cur = cur->_right;
			}
		}
	}
	void InOrderThding()
	{
		Node* prev = NULL;
		_InOrderThding(_root,prev);
	}
	void InOrderThd()
	{
		Node* cur = _root;
		while(cur)
		{
			while(cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}
			cout << cur->_data <<" ";
			while(cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				cout << cur->_data <<" ";
			}
			cur = cur->_right;
		}
	}
protected:
	Node* _CreateTree(const T*a, size_t size, size_t& index, const T& invalid )
	{
		Node* root = NULL;
		if((index < size) && (a[index] != invalid))
		{
			root = new Node(a[index]);
			root->_left = _CreateTree(a,size,++index,invalid);
			root->_right = _CreateTree(a,size,++index,invalid);
		}
		return root;
	}
	void _PrevOrderThding(Node* root,Node*& prev)
	{
		Node* cur = root;
		if(cur == NULL)
		{
			return;
		}

		if(cur->_left == NULL)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}
		if(prev && prev->_right == NULL)
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}
		prev = cur;

		if(cur->_leftTag == LINK)
		{
			_PrevOrderThding(cur->_left,prev);
		}
		if(cur->_rightTag == LINK)
		{
		    _PrevOrderThding(cur->_right,prev);
		}
	}
	void _InOrderThding(Node* root,Node*& prev)
	{
		Node* cur = root;
		if(cur == NULL)
		{
			return;
		}


		_InOrderThding(cur->_left,prev);


		if(cur->_left == NULL)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}

		if(prev && prev->_right == NULL)
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}
		prev = cur;

	   _InOrderThding(cur->_right,prev);
	
	}
 protected:
	Node* _root;
};