#pragma once

#include<iostream>
#include<queue>
#include<stack>

using namespace std;

template<typename T>
struct BinaryTreeNode
{
	BinaryTreeNode(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
	{}
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
};

template<typename T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(T* a,size_t size,size_t invalid)
	{
		size_t index = 0;
		_root = _CreateBinaryTree(a,size,index,invalid);
	}
	BinaryTree(const BinaryTree& bt)
	{
		_root = _Copy(bt._root);
	}
	BinaryTree& operator=(BinaryTree bt)
	{
		swap(_root,bt._root);
		return *this;
	}
	/*~BinaryTree()
	{
		_Destory(_root);
		_root = NULL;
	}*/
public:
	//递归实现：

	//前序遍历
	void PrevOrder()
	{
		_PrevOrder(_root);
		cout <<endl;
	}
	//中序遍历
	void InOrder()
	{
		_InOrder(_root);
		cout <<endl;
	}
	//后序遍历
	void PosOrder()
	{
		_PosOrder(_root);
		cout <<endl;
	}
	//层序遍历
	void LevelOrder()
	{
		_LevelOrder(_root);
		cout <<endl;
	}
	size_t Size()
	{
		return _Size(_root);
	}
	size_t Depth()
	{
		return _Depth(_root);
	}
	//叶子个数
	size_t LeafSize()
	{
		return _LeafSize(_root);
	}

	//非递归实现：

	void PrevOrder_NotRecursion()
	{
		_PrevOrderRecursion(_root);
	}
	void InOrder_NotRecursion()
	{
		_InOrderRecursion(_root);
	}
	void PosOrder_NotRecursion()
	{
		_PosOrderRecursion(_root);
	}
	Node* Find(const T& x)
	{
		return _Find(_root,x);
	}
	/*size_t GetKLevel(size_t k)
	{
		return _GetKLevel(_root,k);
	}*/
	size_t GetKLevel(size_t k)
	{
		size_t size = 0;
		size_t level = 1;
		_GetKLevel(_root,k,size,level);
	}
protected:
	Node* _CreateBinaryTree(const T* a,size_t size,size_t &index,const T& invalid )
	{
		Node* root = NULL;
		if((index < size) && (a[index] != invalid))
		{
			root = new BinaryTreeNode<T>(a[index]);
			root->_left = _CreateBinaryTree(a,size,++index,invalid);
			root->_right = _CreateBinaryTree(a,size,++index,invalid);
		}
		return root;
	}
	Node* _Copy(Node* root)
	{
		if(root == NULL)
		{
			return NULL;
		}
		Node* newRoot = new BinaryTreeNode<T>(root->_data);
		newRoot->_left = _Copy(root->_left);
		newRoot->_right = _Copy(root->_right);
		return root;
	}
	/*void _Destory(Node* root)
	{
		if(root == NULL)
		{
			return;
		}
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
	}*/
	void _PrevOrder(Node* root)
	{
		if(root == NULL)
		{
			return;
		}
		cout << root->_data << " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}
	void _InOrder(Node* root)
	{
		if(root == NULL)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_data << " ";
		_InOrder(root->_right);
	}
	void _PosOrder(Node* root)
	{
		if(root == NULL)
		{
			return;
		}
		_PosOrder(root->_left);
		_PosOrder(root->_right);
		cout << root->_data << " ";
	}
	void _LevelOrder(Node* root)
	{
		queue<Node*> q;
		if(root)
		{
			q.push(root);
		}
		while(!q.empty())
		{
			Node* front = q.front();
			cout << front->_data << " ";
			if(front->_left != NULL)
			{
				q.push(front->_left);
			}
			if(front->_right != NULL)
			{
				q.push(front->_right);
			}
		}

	}
	size_t _Size(Node* root)
	{
		if(root == NULL)
		{
			return 0;
		}
		return _Size(root->_left) + _Size(root->_right) + 1;
	}
	size_t _Depth(Node* root)
	{
		 if(root == NULL)
		 {
			 return 0;
		 }
		 int left = _Depth(root->_left);
		 int right = _Depth(root->_right);
		 return left > right ? left+1 : right+1;
	}
	size_t _LeafSize(Node* root)
	{
		if(root == NULL)
		{
			return 0;
		}
		else if(root->_left == NULL && root->_right ==NULL)
		{
			return 1;
		}
		 _LeafSize(root->_left);
		 _LeafSize(root->_right);
		return _LeafSize(root->_left) + _LeafSize(root->_right);
	}
	void PrevOrder_NotRecursion(Node* root)
	{
		stack<Node*> s;
		if(root)
		{
			s.push(root);
		}
		while(!s.empty())
		{
			Node* top = s.top();
			s.pop();
			cout << top->_data << " ";
			if(top->_right)
			{
				s.push(top->_right);
			}
			if(top->_left)
			{
				s.push(top->_left);
			}
		}

	}

	void _InOrder_Recursion(Node* root)
	{
		Node* cur = root;
		stack<Node*> s;
		while(cur && !s.empty())
		{
			while(cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			cout << top->_data <<" ";
			s.pop();

			cur = top->_right;
		}
	}

	void PosOrder_NotRecursion(Node* root)
	{
		Node* cur = root;
		Node* prev = NULL;
		stack<Node*> s;
		while(cur && !s.empty())
		{
			while(cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			if(top->_right == NULL || top->_right == prev)
			{
				cout << top->_data<<"";
				s.pop();
				prev = top;
			}
			else
			{
				cur = top->_right;
			}
		}
	}
	Node* _Find(Node* root,size_t x)
	{
		if(root == NULL)
		{
			return NULL;
		}
		if(root->_data == x)
		{
			return root;
		}
		Node* ret = _Find(root->_left,x);
		if(ret)
		{
			return ret;
		}
		return _Find(root->_right,x);
	}
	/*size_t _GetKLevel(Node* root, size_t k)
	{
		if(root == NULL)
		{
			return 0;
		}
		if(k == 1)
		{
			return 1;
		}
		return _GetKLevel(root->_left,k-1) + _GetKLevel(root->_right,k-1);
	}*/
	void _GetKLevel(Node* root, size_t k, size_t& size, size_t level)
	{
		if(root == NULL)
		{
			return;
		}
		if(size == level)
		{
			++size;
			return;
		}
		_GetKLevel(root->_left, k, size, level+1);
		_GetKLevel(root->_right, k, size, level+1);
	}

protected:
	Node* _root;
};