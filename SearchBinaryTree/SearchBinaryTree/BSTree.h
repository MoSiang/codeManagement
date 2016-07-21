#pragma once

#include<iostream>

using namespace std;

template<class K, class V>
struct BSTreeNode
{
	BSTreeNode(const K& key, const V& value)
		:_left(NULL)
		,_right(NULL)
		,_key(key)
		,_value(value)
	{}
	BSTreeNode<K,V>* _left;
	BSTreeNode<K,V>* _right;

	K _key;
	V _value;
};
template<class K, class V>
class BSTree
{
	typedef BSTreeNode<K, V> Node;
public:
	BSTree()
		:_root(NULL)
	{}

	~BSTree()
	{
		_Destory(_root);
		_root = NULL;
	}
	void _Destory(Node* root)
	{
		if(root == NULL)
			return;

		_Destory(root->_left);
		_Destory(root->_right);

		delete root;
	}

	bool Insert(const K& key, const V& value)
	{
		if(_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}

		Node* parent = NULL;
		Node* cur = _root;
		while(cur)
		{
			if(cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if(cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		if(key > parent->_key)
		{
			parent->_right = new Node(key, value);
			return true;
		}
		else
		{
			parent->_left = new Node(key, value);
			return true;
		}
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	void _InOrder(Node* root)
	{
		if(root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

	Node* Find(const K& key)
	{
		if(_root == NULL)
			return NULL;
		Node* cur = _root;
		while(cur)
		{
			if(cur->_key > key)
				cur = cur->_left;
			else if(cur->_key < key)
				cur = cur->_right;
			else
				return cur;
		}
		return NULL;
	}

	bool Remove(const K& key)
	{
		Node* parent = NULL;
		Node* cur = _root;

		while(cur)
		{
			if(cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if(cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
				break;
		}

		if(cur == NULL)
		{
			return false;
		}

		Node* del = NULL;
		if(cur->_left == NULL)
		{
			del = cur;
			if(parent == NULL)
			{
				_root = cur->_right;
			}
			else
			{
				if(parent->_left == cur)
					parent->_left = cur->_right;
				else
					parent->_right = cur->_right;
			}
		}
		else if(cur->_right == NULL)
		{
			del = cur;
			if(parent == NULL)
			{
				_root = cur->_left;
			}
			else
			{
				if(parent->_left == cur)
					parent->_left = cur->_left;
				else
					parent->_right = cur->_left;
			}
		}
		else
		{
			//parent = cur;
			Node* firstLeft = cur->_right;
			while(firstLeft->_left)
			{
				parent = firstLeft;
				firstLeft = firstLeft->_left;
			}

			del = firstLeft;
			cur->_key = firstLeft->_key;
			cur->_value = firstLeft->_value;

			if(parent->_left == firstLeft)
				parent->_left = firstLeft->_right;
			else
				parent->_right = firstLeft->_right;
		}
		delete del;
		return true;
	}

	bool InsertR(const K& key, const V& value)
	{
		return _InsertR(_root, key, value);
	}
	bool _InsertR(Node*& root, const K& key, const V& value)
	{
		if(root == NULL)
		{
			root = new Node(key, value);
			return true;
		}

		if(root->_key > key)
			return _InsertR(root->_left, key, value);
		else if(root->_key < key)
			return _InsertR(root->_right, key, value);
		else
			return false;
	}

	Node* FindR(const K& key)
	{
		return _FindR(_root, key);
	}
	Node* _FindR(Node* root, const K& key)
	{
		if(root == NULL)
			return NULL;

		if(root->_key > key)
			return _FindR(root->_left, key);
		else if(root->_key < key)
			return _FindR(root->_right, key);
		else
			return root;
	}

	bool RemoveR(const K& key)
	{
		return _RemoveR(_root, key);
	}
	bool _RemoveR(Node*& root, const K& key)
	{
		if(root == NULL)
			return false;

		if(root->_key > key)
			return _RemoveR(root->_left, key);
		else if(root->_key < key)
			return _RemoveR(root->_right, key);
		else
		{
			Node* del = root;
			if(root->_left == NULL)
				root = root->_right;
			else if(root->_right == NULL)
				root = root->_left;
			else
			{
				Node* firstLeft = root->_right;
				while(firstLeft)
				{
					firstLeft = firstLeft->_left;
				}
				swap(firstLeft->_key, root->_key);
				swap(firstLeft->_value, root->_value);

				return _RemoveR(root->_right, key);
			}
			delete del;
		}
		return true;
	}
private:
	Node* _root;
};