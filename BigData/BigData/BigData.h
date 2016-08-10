#pragma once

#include<iostream>
#include<string>

using namespace std;

typedef long long INT64;
#define UN_INIT 0xCCCCCCCCCCCCCCCC
#define MAX_INT64 0x7FFFFFFFFFFFFFFF
#define MIN_INT64 0x8000000000000000

using  namespace std;

class BigData
{
	friend ostream& operator<<(ostream& os,const BigData& bigdata);
public:
	BigData(INT64 value = UN_INIT);
	BigData(char* pData);
public:
	BigData operator+(const BigData& bigData);
	BigData operator-(const BigData& bigData);
	BigData operator*(const BigData& bigData);
	BigData operator/(const BigData& bigData);
private:
	string Add(string left, string right);
	string Sub(string left, string right);
	string Mul(string left, string right);
	string Div(string left, string right);

	bool IsINT64Overflow()const;
	bool IsLeftBig(const char* pLeft, int LSize, const char* pRight, int RSize);
	char SubLoop(char* pLeft, int LSize, char* pRight, int RSize);

private:
	INT64 _value;
	string _strData;
};