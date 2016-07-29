//#include <iostream>
//#include <string.h>
//
//using namespace std;
//
//class String
//{
//friend ostream& operator<<(ostream &os, const String &str);
//public:
//	String(char *str = " ")
//		:_str(new char[strlen(str)+1])
//	{
//		strcpy(_str, str);
//	}
//	String(const String &str)
//		:_str(new char[strlen(str._str)+1])
//	{
//		strcpy(_str, str._str);
//	}
//	~String()
//	{
//		if(_str != NULL)
//		{
//			delete[] _str;
//			_str = NULL;
//		}
//	}
//	String& operator=( const String &str)
//	{
//		if(this != &str)
//		{
//			delete[] _str;
//		}
//		_str = new char[strlen(str._str)+1];
//		strcpy(_str, str._str);
//        return *this;
//	}
//	
//private:
//	char *_str;
//};
//
//ostream& operator<<(ostream &os, const String &str)
//{
//	os << str._str <<endl;
//	return os;
//}
//
//int main()
//{
//	String str1("hello");
//	cout << str1 <<endl;
//	String str2(str1);
//	cout << str2 <<endl;
//	String str3;
//	str3 = str2;
//	cout << str3<<endl;
//	getchar();
//	return 0;
//}



//#include <iostream>
//#include <string.h>
//#include <assert.h>
//#include <cstdlib>
//
//using namespace std;
//
//#define DEFAUILT_CAPACITY 3
//
//class String
//{
//	friend ostream& operator<<(ostream &os, const String &str);
//	friend istream& operator>>(istream &in, const String &str);
//public:
//	String(char *str)
//		:_str(new char[strlen(str) + 1])
//		,_size(strlen(str))
//		,_capacity(strlen(str) + 1)
//	{
//		strcpy(_str, str);
//	}
//	String()
//		:_str(new char[1])
//		,_size(1)
//		,_capacity(DEFAUILT_CAPACITY)
//	{
//		*_str = '\0';
//	}
//	~String()
//	{
//		if(_str != NULL)
//		{
//			delete[] _str;
//		}
//		_size = 0;
//		_capacity = 0;
//	}
//	String(const String &str)
//		:_str(NULL)
//		,_size(str._size)
//		,_capacity(str._capacity)
//	{
//		String tmp(str._str);
//		swap(_str,tmp._str);
//	}
//	String& operator=(String str)
//	{
//		swap(_size,str._size);
//		swap(_capacity,str._capacity);
//		swap(_str,str._str);
//		return *this;
//	}
//public:
//	int my_strcmp(const char*str1,const char*str2)
//	{
//		assert(str1);
//		assert(str2);
//		while(*str1 == *str2)
//		{
//			if(*str1 == '\0')
//			{
//				return 0;
//			}
//			str1++;
//			str2++;
//		}
//		return *str1-*str2;
//	}
//public:
//	bool operator==(const String &str)
//	{
//		int ret = my_strcmp(_str,str._str);
//		if(ret == 0)
//		{
//			return true;
//		}
//		return false;
//	}
//	bool operator>(const String &str)
//	{
//		int ret = my_strcmp(_str, str._str);
//		if(ret > 0)
//		{
//			return true;
//		}
//		return false;
//	}
//	bool operator<(const String &str)
//	{
//		return !((*this == str._str) && (*this == str._str));
//	}
//	void _CheckCapacity(int sz)
//	{
//		if(sz > _capacity)
//		{
//			char *tmp = NULL;
//			_capacity = sz;
//			tmp = new char[sz + DEFAUILT_CAPACITY];
//			strcpy(tmp, _str);
//			delete[] _str;
//			_str = tmp;
//		}
//	}
//	void insert(int pos, char ch)
//	{
//		int end = _size;
//		_CheckCapacity(_size + 2);
//		while(pos <= end)
//		{
//			_str[end + 1] = _str[end];
//			end--;
//		}
//		_str[pos] = ch;
//		_size ++;
//	}
//	void insert(int pos, char* str)
//	{
//		int end = _size;
//		int sublen = strlen(str);
//		_CheckCapacity(_size + 1 +sublen);
//		while(pos <=end)
//		{
//			_str[end + sublen] = _str[end];
//			end--;
//		}
//		while(*str)
//		{
//			_str[pos++] = *str++;
//		}
//		_size += sublen;
//	}
//	void insert(int pos, String &str)
//	{
//		insert(pos,str._str);
//	}
//	void PushBack(char ch)
//	{
//		1.
//		String tmp(_str);
//		delete[] _str;
//		int i = 0;
//		int size = strlen(tmp._str)+2;
//		char *pstr = NULL ;
//		_str = new char[size];
//		strcpy(_str,tmp._str);
//		pstr = _str;
//		while(*pstr)
//		{
//			pstr++;
//		}
//		*pstr++ = ch;
//		*pstr = '\0';
//	   2.
//		insert(_size,ch);
//	}
//	int size()
//	{
//		return strlen(_str);
//	}
//private:
//	char *_str;
//	int _size;
//	int _capacity;
//};
//
//ostream& operator<<(ostream &os, const String &str)
//{
//	os << str._str <<endl;
//	return os;
//}
//istream& operator>>(istream &in, const String &str)
//{
//	in >> str._str;
//	return in;
//}

//int main()
//{
//String str1("hello");
//String str2(" world");
/*String str2(str1);
String str3;
str3 = str1;
cout << str1<<endl;
cout << str2<<endl;
cout << str3<<endl;*/
//str1.PushBack('w');
//str1.insert(0, 'a');
//str1.insert(5," world");
//str1.insert(5, str2);
//cout << str1<<endl;
//cout << str1.size() <<endl;
//system("pause");
//return 0;
//}




//#include <iostream>
//#include <string.h>
//
//using namespace std;
//
//class String
//{
//public:
//	String(char *str = " ")
//		:_str(new char[strlen(str) + 1])
//	    ,_pcount(new int(1))
//	{
//		strcpy(_str,str);
//	}
//	~String()
//	{
//		if(_str != NULL)
//		{
//			if(--*_pcount == 0)
//			{
//				delete[] _str;
//				delete _pcount;
//				_str = 0;
//				_pcount = 0;
//			}
//		}
//	}
//	String(const String &str)
//	{
//		_str = str._str;
//		_pcount = str._pcount;
//		++(*_pcount);
//	}
//	String& operator=(const String &str)
//	{
//		if(this != &str)
//		{
//			if(--(*_pcount) == 0)
//			{
//				delete[] _str;
//				delete _pcount;
//			}
//			_str = str._str;
//			_pcount = str._pcount;
//			++(*_pcount);
//		}
//		return *this;
//	}
//private:
//	char *_str;
//	int *_pcount;
//};
//
//int main()
//{
//	String str1("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
//	String str2(str1);
//	String str3("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
//	String str4(str3);
//	str1 = str3;
//	return 0;
//}




#include <iostream>
#include <string.h>

using namespace std;

class String
{
	friend ostream& operator<<(ostream &os, const String &str);
public:
	String(char *str = " ")
		:_str(new char[strlen(str) + 5])
	{
		*(int*)_str = 1;
		_str += 4;
		strcpy(_str, str);
	}
	~String()
	{
		if (_str != NULL)
		{
			_str -= 4;
			if (--*(int*)_str == 0)
			{
				delete[] _str;
			}
		}
	}
	String(const String &str)
	{
		_str = str._str;
		++(*((int*)_str - 4));
	}
	String& operator=(const String &str)
	{
		if (this != &str)
		{
			_str -= 4;
			if (--*(int*)_str == 0)
			{
				delete[] _str;
			}
			_str = str._str;
			++(*((int*)_str - 4));
		}
		return *this;
	}
	char& operator[](int index)
	{
		char *tmp = _str;
		if (--(*((int*)_str - 4)) == 0)
		{
			return _str[index];
		}
		_str = new char[strlen(_str) + 5];
		strcpy(_str += 4, tmp);
		(*((int*)_str - 4)) = 1;
		return _str[index];
	}
private:
	char *_str;
};
ostream& operator<<(ostream &os, const String &str)
{
	os << str._str << endl;
	return os;
}
int main()
{
	String str1("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	String str2(str1);
	String str3("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
	String str4(str3);
	//str1 = str3;
	str1[0] = '5';
	cout << str1 << endl;
	getchar();
	return 0;
}