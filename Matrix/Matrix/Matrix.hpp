#pragma once

#include<iostream>

using namespace std;

//template<typename T>
//class SymmetricMatrix
//{
//public:
//	SymmetricMatrix(T* a,size_t size)
//		:_a(new T[size*(size+1)/2])
//		,_size(size*(size+1)/2)
//		,_n(size)
//	{
//		size_t index = 0;
//		for(size_t i = 0; i<_n; i++)
//		{
//			for(size_t j = 0; j<_n; j++)
//			{
//				if(i >= j)
//				{
//				_a[index++] = a[i*_n+j];
//				}
//				else
//				{
//					break;
//				}
//			}
//		}
//	}
//	~SymmetricMatrix()
//	{
//		if(_a != NULL)
//		{
//			delete[] _a;
//			_a = NULL;
//			_size = 0;
//			_n = 0;
//		}
//	}
//	void Display()
//	{
//		for(size_t i = 0; i<_n; i++)
//		{
//			for(size_t j = 0; j<_n; j++)
//			{
//				if(i >= j)
//				{
//					cout<< _a[i*(i+1)/2+j]<< " ";
//				}
//				else
//				{
//					cout<< _a[j*(j+1)/2+i]<<" ";
//				}
//			}
//			cout <<endl;
//		}
//		cout<<endl;
//	}
//	T& Access(size_t i,size_t j)
//	{
//		if(i < j)
//		{
//			swap(i,j);
//		}
//		return _a[i*(i+1)/2+j];
//	}
//protected:
//	T* _a;
//	size_t _size;
//	size_t _n;
//};





#include<vector>
#include<memory>

template<typename T>
struct Triple
{
	Triple(const T& value = T(),size_t row = 0, size_t col = 0)
		:_value(value)
		,_row(row)
		,_col(col)
	{}
	T _value;
	size_t _row;
	size_t _col;
};
template<typename T>
class SparseMatrix
{
public:
	SparseMatrix()
		:_rowSize(0)
		,_colSize(0)
	{}
	SparseMatrix(T* a, size_t m, size_t n, const T& invalid)
		:_a(NULL)
		,_rowSize(m)
		,_colSize(n)
		,_invalid(invalid)
	{
		for(size_t i = 0; i<m; i++)
		{
			for(size_t j = 0; j<n; j++)
			{
				if(a[i*n+j] != invalid)
				{
				_a.push_back (Triple<T>(a[i*n+j],i,j));
				}
			}
		}
	}
	SparseMatrix<T> Transport()
	{
		SparseMatrix<T> tmp;
		tmp._colSize = _rowSize;
		tmp._rowSize = _colSize;
		tmp._invalid = _invalid;
		for(size_t i = 0; i<_colSize; i++)
		{
			size_t index = 0;
			while(index < _a.size())
			{
				if(_a[index]._col == i)
				{
					Triple<T> t;
					t._value = _a[index]._value;
					t._row = _a[index]._col;
					t._col = _a[index]._row;

					tmp._a.push_back(t);
				}
				index++;
			}
		}
		return tmp;
	}
	SparseMatrix<T> FastTransport()
	{
		SparseMatrix<T> tmp;
		tmp._colSize = _rowSize;
		tmp._rowSize = _colSize;
		tmp._invalid = _invalid;
		int* rowCounts = new int[_colSize];
		int* rowStart = new int[_colSize];
		memset(rowCounts,0,sizeof(int)*_colSize);
		memset(rowStart,0,sizeof(int)*_colSize);
		size_t index = 0;
		
		while(index < _a.size())
		{
			rowCounts[_a[index]._col]++;
			index++;
		}
		rowStart[0] = 0;
		for(size_t i = 1; i<_colSize; i++)
		{
			rowStart[i] = rowStart[i-1] + rowCounts[i-1];
		}
		index = 0;
		tmp._a.resize(_a.size());
        while(index < _a.size())
		{
			size_t rowIndex = _a[index]._col;
			int& start = rowStart[rowIndex];
			Triple<T> t;
			t._value = _a[index]._value;
			t._row = _a[index]._col;
			t._col = _a[index]._row;
			tmp._a[start++] = t;
			++index;
		}
		/*while(index < _a.size())
		{
			size_t rowIndex = _a[index]._col;
			int& start = rowStart[rowIndex];
			Triple<T> t;
			t._value = _a[index]._value;
			t._row = _a[index]._col;
			t._col = _a[index]._row;
			tmp._a[(rowStart[_a[index]._col])++] = t;
		}*/
		return tmp;
	}
	void Display()
	{
		size_t index = 0;
		for(size_t i = 0; i<_rowSize; i++)
		{
			for(size_t j = 0; j<_colSize; j++)
			{
				if(index < _a.size()
					&& _a[index]._row == i
					&& _a[index]._col == j)
				{
					cout<<_a[index]._value<<" ";
					index++;
				}
				else
				{
					cout<<_invalid<<" ";
				}
				
			}
			cout <<endl;
		}
		cout<<endl;
	}
protected:
	vector<Triple<T> > _a;
	size_t _rowSize;
	size_t _colSize;
	T _invalid;
};