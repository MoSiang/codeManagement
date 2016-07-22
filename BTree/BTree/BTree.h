#pragma once

#include <iostream>

using namespace std;

template<class K, int M>
struct BTreeNode
{
	BTreeNode()
	:_parent(NULL)
	, _size(0)
	{
		for (size_t i = 0; i < M; i++)
		{
			_keys[i] = 0;
			_subs[i] = NULL;
		}
		_subs[M] = NULL;
	}

	K _keys[M];                         //只存储m-1个值，多给一个方便分裂
	BTreeNode<K, M>* _subs[M + 1];
	BTreeNode<K, M>* _parent;
	size_t _size;                       //key值的多少
};

template <class K, class V>
struct Pair
{
	Pair(const K& key, const V& value)
	:_first(key)
	,_second(value)
	{}

	K _first;
	V _second;
};

template<class K, int M = 3>
class BTree
{
	typedef BTreeNode<K, M> Node;
public:
	BTree()
		:_root(NULL)
	{}
	Pair<Node*, int> Find(const K& key)
	{
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			size_t i = 0;
			for (; i < cur->_size; i++)
			{
				if (cur->_keys[i] == key)
				{
					return Pair<Node*, int>(cur, i);
				}
				else if (cur->_keys[i] < key)
				{
					break;
				}
			}
			parent = cur;
			cur = cur->_subs[i];
		}
		return Pair<Node*, int>(parent, -1);
	}

	bool Insert(const K& key)
	{
		if (_root == NULL)
		{
			_root = new Node;
			_root->_keys[0] = key;
			_root->_size++;
			return true;
		}

		Pair<Node*, int> ret = Find(key);
		if (ret._second != -1)
		{
			return false;
		}

		Node* cur = ret._first;
		K newKey = key;
		Node* sub = NULL;
		while (1)
		{
			_InsertKey(cur, newKey, sub);
			if (cur->_size < M)
			{
				return true;
			}

			int div = M / 2;
			size_t index = 0;
			Node* tmp = new Node;
			for (size_t i = div + 1; i < cur->_size; ++i)
			{
				tmp->_keys[index] = cur->_keys[i];
				++index;
				tmp->_size++;
				cur->_size--;
			}

			index = 0;
			for (size_t i = div + 1; i < cur->_size + 1; ++i)
			{
				tmp->_subs[index] = cur->_subs[i];
				if (tmp->_subs[index])
				{
					tmp->_subs[index]->_parent = tmp;
				}
				++index;
			}
			newKey = cur->_keys[div];
			cur->_size--;
			if (cur->_parent == NULL)
			{
				_root = new Node;
				_root->_keys[0] = newKey;
				_root->_subs[0] = cur;
				_root->_subs[1] = tmp;

				cur->_parent = _root;
				tmp->_parent = _root;
				_root->_size = 1;
				return true;
			}
			cur = cur->_parent;
			tmp = cur;
		}
	}

	void Inorder()
	{
		_Inorder(_root);
	}
protected:
	void _InsertKey(Node* cur, const K& key, Node* sub)
	{
		int end = cur->_size - 1;
		while (end >= 0)
		{
			if (cur->_keys[end] > key)
			{
				cur->_keys[end + 1] = cur->_keys[end];
				cur->_subs[end + 2] = cur->_subs[end + 1];
				--end;
			}
			else
			{
				break;
			}
		}
		cur->_keys[end + 1] = key;
		cur->_subs[end + 2] = sub;
		if (sub)
		{
			sub->_parent = cur;
		}
		cur->_size++;
	}

	void _Inorder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		size_t i = 0;
		for (; i < root->_size; ++i)
		{
			_Inorder(root->_subs[i]);
			cout << root->_keys[i]<<" ";
		}
		_Inorder(root->_subs[i]);
	}
protected:
	Node* _root;
};