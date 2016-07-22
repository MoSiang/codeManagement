#pragma once

#include <iostream>

using namespace std;

enum Color
{
	RED,
	BLACK,
};

template <class K, class V>
struct RBTreeNode
{
	RBTreeNode(const K& key, const V& value)
	:_left(NULL)
	, _right(NULL)
	, _parent(NULL)
	, _key(key)
	, _value(value)
	, _col(RED)
	{}
	RBTreeNode* _left;
	RBTreeNode* _right;
	RBTreeNode* _parent;
	K _key;
	V _value;
	Color _col;
};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{}
	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			_root->_col = BLACK;
			return true;
		}

		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		
		cur = new Node(key, value);
		if (parent->_key > key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}

		while (cur != _root && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				if (uncle && uncle->_col == RED)
				{
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_right)
					{
						RotateL(parent);
						swap(cur, parent);
					}
					parent->_col = BLACK;
					grandfather->_col = RED;
					RotateR(grandfather);
				}
			}
			else
			{
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_col == RED)
				{

					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(cur, parent);
					}
					parent->_col = BLACK;
					grandfather->_col = RED;
					RotateL(grandfather);
				}
			}
		}

		_root->_col = BLACK;
		return true;
	}
	
	bool CheckRBTree()
	{
		if (_root && _root->_col == RED)
		{
			return false;
		}

		int NodeNum = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
			{
				++NodeNum;
			}
			cur = cur->_left;
		}

		int count = 0;
		return _CheckRBTree(_root, NodeNum, count);
	}
	protected:
		void RotateL(Node* parent)
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;

			parent->_right = subRL;
			if (subRL)
			{
				subRL->_parent = parent;
			}

			subR->_left = parent;
			Node* ppNode = parent->_parent;
			parent->_parent = subR;

			if (ppNode == NULL)
			{
				_root = subR;
			}
			else
			{
				if (ppNode->_left == parent)
				{
					ppNode->_left = subR;
				}
				else
				{
					ppNode->_right = subR;
				}
			}
			subR->_parent = ppNode;
		}
		void RotateR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;

			parent->_left = subLR;
			if (subLR)
			{
				subLR->_parent = parent;
			}

			subL->_right = parent;
			Node* ppNode = parent->_parent;
			parent->_parent = subL;

			if (ppNode == NULL)
			{
				_root = subL;
			}
			else
			{
				if (ppNode->_left == parent)
				{
					ppNode->_left = subL;
				}
				else
				{
					ppNode->_right = subL;
				}
			}
			subL->_parent = ppNode;
		}
		bool _CheckRBTree(Node* root, int NodeNum, int count)
		{
			if (root == NULL)
			{
				return true;
			}

			Node* parent = root->_parent;
			if (root->_col == RED && parent && parent->_col == RED)
			{
				cout << "违反规则三" << root->_key << endl;
				return false;
			}

			if (root->_col == BLACK)
			{
				count++;
			}
			if (root->_left == NULL && root->_right == NULL && NodeNum != count)
			{
				cout << "违反规则四" << root->_key << endl;
				return false;
			}

			return _CheckRBTree(root->_left, NodeNum, count)
				&& _CheckRBTree(root->_right,NodeNum, count);
		}
protected:
	Node* _root;
};