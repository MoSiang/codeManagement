#pragma once

#include<iostream>

using namespace std;

template<class K,class V>
struct AVLTreeNode
{
	AVLTreeNode(const K& key, const V& value)
	:_parent(NULL)
	,_left(NULL)
	, _right(NULL)
	, _key(key)
	, _value(value)
	, _bf(0)
	{}
	AVLTreeNode<K, V>* _parent;
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	K _key;
	V _value;
	int _bf;
};
template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}

	~AVLTree()
	{
		_Destory(_root);
	}
public:
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}

		Node* cur = _root;
		Node* parent = NULL;
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

		//检查树的平衡
		//更新平衡因子，不满足平衡条件时进行旋转
		while (parent)
		{
			if (cur == parent->_left)
			{
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}
			
			if (parent->_bf == 0)
			{
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = cur->_parent;
			}
			else //abs(_bf)>1,进行旋转
			{
				if (cur->_bf == 1)
				{
					if (parent->_bf == 2)
					{
						RotateL(parent);
					}
					else
					{
						RotateLR(parent);
					}
				}
				else
				{
					if (parent->_bf == -2)
					{
						RotateR(parent);
					}
					else
					{
						RotateRL(parent);
					}
				}
				break;
			}

		}
		return true;
	}
	bool IsBalance()
	{
		return _IsBalance(_root);
	}
protected:
	void _Destory(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		_Destory(root->_left);
		_Destory(root->_right);

		delete root;
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;//parent->_left = subRL是错误的
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
		parent->_bf = subR->_bf = 0;
	}
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;//parent->_right = subRL是错误的
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
		parent->_bf = subL->_bf = 0;
	}
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		if (bf == -1)
		{
			subL->_bf = 0;
			parent->_bf = 1;
		}
		else if (bf == 1)
		{
			subL->_bf = -1;
			parent->_bf = 0;
		}
	}
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateR(parent->_right);
		RotateL(parent);
		
		if (bf == -1)
		{
			subR->_bf = 1;
			parent->_bf = 0;
		}
		else if (bf == 1)
		{
			subR->_bf = 0;
			parent->_bf = -1;
		}
	}

	int _Height(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		int left = _Height(root->_left);
		int right = _Height(root->_right);

		return left > right ? left + 1 : right + 1;
	}
	bool _IsBalance(Node* root)
	{
		if (root == NULL)
		{
			return true;
		}

		int left = _Height(root->_left);
		int right = _Height(root->_right);

		if (left - right != root->_bf || abs(left - right) > 1)
		{
			cout << "结点的平衡因子异常" << endl;
			cout << root->_key << ":" << root->_value << endl;
			return false;
		}
		return _IsBalance(root->_left && root->_right);
	}
private:
	Node* _root;
};