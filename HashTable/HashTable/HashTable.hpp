//1.处理哈希冲突的闭散列：线性探测
//2.处理哈希冲突的闭散列：二次探测
//3.处理哈希冲突的开散列：开链法(哈希桶)


//1.
#pragma once

#include<iostream>

using namespace std;

enum State
{
	EMPTY,
	DELETE,
	EXITS,
};

template<class K>
class HashTable
{
public:
	HashTable(size_t capacity = 10)
		:_tables(new K[capacity])
		,_states(new K[capacity])
		,_size(0)
		,_capacity(capacity)
	{
		for(size_t i = 0; i<_capacity; i++)
		{
			_states[i] = EMPTY;
		}
	}
	~HashTable()
	{
		if(_tables)
		{
			delete[] _tables;
			delete[] _states;
		}
	}
public:
	bool Insert(const K& key)
	{
		_CheckCapacity();
		size_t index = _HashFunc(key);
		while(_states[index] == EXITS)
		{
			if(_tables[index] == key)
			{
				return false;
			}
			++index;
			if(index == _capacity)
			{
				index = 0;
			}
		}
		_tables[index] = key;
		_states[index] = EXITS;
		++_size;
		return true;
	}
	bool Find(const K& key)
	{
		size_t index = _HashFunc(key);
		szie_t start = index;
		while(_states[index] !=	EMPTY)
		{
			if(_tables[index] == key)
			{
				if(_states[index] == DELETE)
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			++index;
			if(index == _capacity)
			{
				index = 0;
			}
			if(index == start)
			{
				return false;
			}
		}
		return false;
	}
	bool Remove(const K& key) 
	{
		size_t index = _HashFunc(key);
		szie_t start = index;
		while(_states[index] !=	EMPTY)
		{
			if(_tables[index] == key)
			{
				_stables[index] = DELETE;
				--size;
				retrun true;
			}
			++index;
			if(index == _capacity)
			{
				index = 0;
			}
			if(index == start)
			{
				return false;
			}
		}
		return false;
	}
	void Print()
	{
		for(size_t i = 0; i<_capacity; i++)
		{
			printf("_tables[%d]:",i);
			cout<<_states[i]<<":";
			cout<<_tables[i] <<" ";
		}
		cout<<endl;
	}
protected:
	void _CheckCapacity()
	{
		if(_size*10/_capacity == 7)
		{
			HashTable<K> tmp(2*_capacity);
			for(size_t i = 0; i<_capacity; i++)
			{
				if(_states[i] == EXITS)
				{
					tmp.Insert(_tables[i]);
				}
			}
			this->Swap(tmp);
		}
	}
	void Swap(HashTable<K>& ht)
	{
		swap(_tables,ht._tables);
		swap(_states,ht._states);
		swap(_size,ht._size);
		swap(_capacity,ht._capacity);
	}
	size_t _HashFunc(const K& key)
	{
		return key%_capacity;
	}
private:
	K* _tables;
	K* _states;
	size_t _size;
	size_t _capacity;
};











//3.
//#pragma once
//
//#include<iostream>
//#include<vector>
//#include<string>
//
//using namespace std;
//
//
//template<class K,class V>
//struct HashTableNode
//{
//	HashTableNode(const K& key,const V& value)
//		:_key(key)
//		,_value(value)
//		,_next(NULL)
//	{}
//	K _key;
//	V _value;
//	HashTableNode<K,V>* _next;
//};
//template<class K>
//struct __HashFunc
//{
//	size_t operator()(const K& key)
//	{
//		return key;
//	}
//};
//template<>
//struct __HashFunc<string>
//{
//	size_t BKDRHash(const char *str)  
//	{  
//    register size_t hash = 0;  
//    while (*str)  
//    {         
//        hash = hash * 131 + *str++;        
//    }  
//    return hash;  
//	}  
//	size_t operator()(const string& key)
//	{
//		return BKDRHash(key.c_str());
//	}
//};
//template<class K,class V,class HF = __HashFunc<K>>
//class HashTable
//{
//	typedef HashTableNode<K,V> Node;
//public:
//	HashTable()
//		:_size(0)
//	{}
//	HashTable(size_t capacity)
//		:_size(0)
//	{
//		_tables.resize(_GetNextPrime(capacity));
//	}
//	HashTable(const HashTable& ht)
//		:_size(0)
//	{
//		_tables.resize(ht._tables.size());
//		for(size_t i = 0; i<ht._tables.size(); i++)
//		{
//			Node * cur = ht._tables[i];
//			while(cur)
//			{
//				this->Insert(cur->_key,cur->_value);
//				cur = cur->_next;
//			}
//		}
//	}
//	HashTable& operator=(HashTable ht)
//	{
//		if(this != &ht)
//		{
//			HashTable tmp(ht);
//			_tables.swap(tmp._tables);
//			swap(_size,tmp._size);
//		}
//		return *this;
//	}
//	~HashTable()
//	{
//		for(size_t i = 0; i<_tables.size(); i++)
//		{
//			Node* cur = _tables[i];
//			while(cur)
//			{
//				Node* del = cur;
//				cur = cur->_next;
//				delete del;
//			}
//			_tables[i] = NULL;
//		}
//	}
//public:
//	bool Insert(const K& key,const V& value)
//	{
//		_CheckCapacity();
//		size_t index = _HashFunc(key,_tables.size());
//		//检查是否存在
//		Node* cur = _tables[index];
//		while(cur)
//		{
//			if(cur->_key == key)
//			{
//				return false;
//			}
//			cur = cur->_next;
//		}
//		Node* tmp = new Node(key,value);
//		tmp->_next = _tables[index];
//		_tables[index] = tmp;
//		++_size;
//		return true;
//	}
//	Node* Find(const K& key)
//	{
//		size_t index = _HashFunc(key,_tables.size());
//		Node* cur  = _tables[index];
//		while(cur)
//		{
//			if(cur->_key == key)
//			{
//				return cur;
//			}
//			cur = cur->_next;
//		}
//		return NULL;
//	}
//	bool Remove(const K& key)
//	{
//		size_t index = _HashFunc(key,_tables.size());
//		Node* cur = _tables[index];
//		if(cur == NULL)
//		{
//			return false;
//		}
//		if(cur->_key == key)
//		{
//			_tables[index] = cur->_next;
//			delete cur;
//			return true;
//		}
//		Node* prev = cur;
//		cur = cur->_next;
//		while(cur)
//		{
//			if(cur->_key == key)
//			{
//				prev->_next = cur->_next;
//				delete cur;
//				return true;
//			}
//			prev = cur;
//			cur = cur->_next;
//		}
//		return false;
//	}
//	void Print()
//	{
//		for(size_t i = 0; i<_tables.size(); i++)
//		{
//			printf("_tables[%d] ",i);
//			Node* cur = _tables[i];
//			while(cur)
//			{
//				cout <<"["<<cur->_key<<"]:"<<"["<<cur->_value<<"]"<<"->";;
//				cur = cur->_next;
//			}
//			cout <<"NULL"<<endl;
//		}
//	}
//protected:
//	void _CheckCapacity()
//	{
//		if(_size == _tables.size())
//		{
//			size_t nextPrime = _GetNextPrime(_size);
//			vector<Node*> newTables;
//			newTables.resize(nextPrime);
//			for(size_t i = 0; i<_tables.size(); i++)
//			{
//				Node* cur = _tables[i];
//				while(cur)
//				{
//					//摘结点
//					Node* tmp = cur;
//					cur = cur->_next;
//
//					//计算在表中的位置，头插
//					size_t index = _HashFunc(tmp->_key,newTables.size());
//					tmp->_next = newTables[i];
//					newTables[i] = tmp;
//				}
//				_tables[i] = NULL;
//			}
//			_tables.swap(newTables);
//		}  
//	}
//	size_t _GetNextPrime(size_t size)
//	{
//		const int _PrimeSize = 28;
//		static const unsigned long _PrimeList [_PrimeSize] =
//		{
//			53ul,         97ul,         193ul,       389ul,       769ul,
//			1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
//			49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
//			1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
//			50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
//			1610612741ul, 3221225473ul, 4294967291ul
//		};
//		for(int i = 0; i<_PrimeSize; i++)
//		{
//			if(_PrimeList[i] > size)
//			{
//				return _PrimeList[i];
//			}
//		}
//		return _PrimeList[_PrimeSize-1];
//	}
//	size_t _HashFunc(const K& key,size_t capacity)
//	{
//		__HashFunc<K> hashfunc;
//		return hashfunc(key)%capacity;
//	}
//private:
//	vector<Node*> _tables;//vector中的size表示哈希的容量
//	size_t _size;//哈希表中的有效个数
//};