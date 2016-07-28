#pragma once

#include<iostream>
#include<cassert>
 
using namespace std;

enum Type
{
	HEAD,
	VALUE,
	SUB,
};

struct GeneralizedNode
{
	GeneralizedNode(Type type = HEAD,char value = 0)
		:_type(type)
		,_next(NULL)
	{
		if(_type == VALUE)
		{
			_value = value;
		}
		else if(_type == SUB)
		{
			_sublink = NULL;
		}
	}
	Type _type;
	GeneralizedNode* _next;//指向下一个数值结点的指针
	union
	{
		char _value;
		GeneralizedNode* _sublink;//指向子表的指针
	};
};

class GeneralizedList
{
public:
	//无参时的构造
	GeneralizedList()
		:_head(new GeneralizedNode(HEAD))
	{}
	//有参时的构造
	GeneralizedList(const char* str)
	{
		_head = _CreateList(str);
	}
	GeneralizedList(const GeneralizedList& g)
	{
		_head = _Copy(g._head);
	}
	GeneralizedList& operator=(GeneralizedList g)
	{
		swap(_head,g._head);
		return *this;
	}
	~GeneralizedList()
	{
		_Destory(_head);
		_head = NULL;
	}
public:
	GeneralizedNode* _Copy(GeneralizedNode* head)
	{
		assert(head->_type == HEAD);
		head = head->_next;

		GeneralizedNode* cur = head;
		GeneralizedNode* newHead = new GeneralizedNode(HEAD);
		GeneralizedNode* newCur = newHead;
		
		while(cur)
		{
			if(cur->_type == VALUE)
			{
				newCur->_next =  new GeneralizedNode(VALUE,cur->_value);
				newCur = newCur->_next;
			}
			else if(cur->_type == SUB)
			{
				newCur->_next =  new GeneralizedNode(SUB);
				newCur = newCur->_next;

				newCur->_sublink = _Copy(cur->_sublink);
			}
			cur = cur->_next;
		}
		return newHead;
	}
	void _Destory(GeneralizedNode* head)
	{
		GeneralizedNode* cur = head;
		while(cur)
		{
			/*GeneralizedNode* del = cur;
			if(cur->_type == SUB)
			{
				_Destory(cur->_sublink);
			}
			cur = cur->_next;
			delete del;*/

			//第二种
			GeneralizedNode* del = cur;
			cur = cur->_next;
			if(del->_type == SUB)
			{
				_Destory(del->_sublink);//传进去的应该是原来的cur(即del),而不是现在的cur;
			}
			delete del;
		}
	}
	size_t Size()
	{
		return _Size(_head);
	}
	size_t Depth()
	{
		return _Depth(_head);
	}
	void Print()
	{
         _Print(_head);
		 cout <<endl;
	}
protected:
	bool _IsValue(char ch)
	{
		if((ch >= '0' && ch <= '9')
			||(ch >= 'a' && ch <= 'z')
			||(ch >= 'A' && ch <= 'Z'))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	GeneralizedNode* _CreateList(const char*& str)
	{
		assert(str && *str == '(');
		++str;
		GeneralizedNode* head = new GeneralizedNode(HEAD);
		GeneralizedNode* cur = head;
		while(*str)
		{
			if(_IsValue(*str))
			{
				cur->_next = new GeneralizedNode(VALUE, *str);
				cur = cur->_next;
				++str;
			}
			else if(*str == '(')
			{
				cur->_next = new GeneralizedNode(SUB);
				cur = cur->_next;

				cur->_sublink = _CreateList(str);
			}
			else if(*str == ')')
			{
				str++;
				return head;
			}
			else
			{
				str++;
			}
		}
		assert(false);
		return head;
	}
size_t _Size(GeneralizedNode* head)
{
	GeneralizedNode* cur = head;
	size_t size = 0;
	while(cur)
	{
		if(cur->_type == VALUE)
		{
			size++;
		}
		else if(cur->_type == SUB)
		{
			size += _Size(cur->_sublink);
		}
		cur = cur->_next;
	}
	return size;
}
size_t _Depth(GeneralizedNode* head)
{
	GeneralizedNode* cur = head;
	size_t depth = 1;//表为空时，深度也为一
	while(cur)
	{
		if(cur->_type == SUB)
		{
		 size_t subdepth = _Depth(cur->_sublink);
		 if(depth < subdepth+1)
		 {
			 depth = subdepth+1;
		 }
		}
		cur = cur->_next;
	}
	return depth;
}
void _Print(GeneralizedNode* head)
{
	GeneralizedNode* cur = head;
	while(cur)
	{
		if(cur->_type == HEAD)
		{
			cout << "(" ;
		}
		else if(cur->_type == VALUE)
		{
			cout << cur->_value <<" ";
			if(cur->_next)
			{
			cout << ",";
			}
		}
		else
		{
			_Print(cur->_sublink);
			if(cur->_next)
			{
			cout << ",";
			}
		}
		cur = cur->_next;
	}
	cout << ")";
}
protected:
	GeneralizedNode* _head;
};