#pragma once

#include<iostream>

#include"Heap.h"

using namespace std;

template<class T>
struct HuffmanTreeNode
{
	HuffmanTreeNode(const T& x)
	:_left(NULL)
	, _right(NULL)
	, _weight(x)
	{}

	HuffmanTreeNode<T>* _left;
	HuffmanTreeNode<T>* _right;
	T _weight;
};


template<class T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T> Node;
public:
	HuffmanTree(const T* a, size_t n, const T& invalid)
	{
		struct Compare
		{
			bool operator()(const Node* l, const Node* r)
			{
				return l->_weight < r->_weight;
			}
		};

		Heap<Node*, Compare> minHeap;
		for (size_t i = 0; i<n; i++)
		{
			if (a[i] != invalid)
			{
				minHeap.push(new Node(a[i]));
			}
		}

		while (minHeap.size() > 1)
		{
			Node* left = minHeap.top();
			minHeap.pop();

			Node* right = minHeap.top();
			minHeap.pop();

			Node* parent = new Node(left->_weight + right->_weight);
			parent->_left = left;
			parent->_right = right;
			minHeap.push(parent);
		}
		_root = minHeap.top();
	}
	~HuffmanTree()
	{
		Destory(_root);
		_root = NULL;
	}
	Node* GetRoot()
	{
		return _root;
	}
protected:
	void Destory(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		Destory(root->_left);
		Destory(root->_right);

		delete root;
	}
private:
	Node* _root;
};