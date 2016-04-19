#pragma once

#include <iostream>

using namespace std;

typedef int DataType;

struct ComplexNode
{
	ComplexNode(DataType x)
		:_data(x)
		,_next(NULL)
		,_random(NULL)
	{}
	DataType _data;
	struct ComplexNode* _next;
	struct ComplexNode* _random;
};

ComplexNode* CopyComplexLinkList(ComplexNode* list)
{
	// 1.¿½±´Á´±í
	ComplexNode* cur = list;
	while(cur)
	{
		ComplexNode* tmp = new ComplexNode(cur->_data);
		tmp->_next = cur->_next;
		cur->_next = tmp;

		cur  = tmp->_next;
	}

	//2.ÖÃrandom
	cur = list;
	while(cur)
	{
		ComplexNode* next = cur->_next;
		if(cur->_random != NULL)
		{
			next->_random = cur->_random ->_next;
		}
		cur = next->_next;
	}

	//3.·ÖÀë
	cur = list;
	ComplexNode* newHead = NULL;
	ComplexNode* newTail = NULL;
	if(cur != NULL)
	{
		newHead = newTail = cur->_next;
		cur->_next = newHead->_next;

		cur = cur->_next;
	}
	while(cur)
	{
		newTail->_next = cur->_next;
		newTail = newTail->_next;
		cur->_next = newTail->_next;
		cur = cur->_next;
	}
	return newHead;
}