#include"BigData.h"
#include<cassert>


BigData::BigData(INT64 value)
	:_value(value)
{

	size_t count = 0;
	INT64 num = _value;
	while (num)
	{
		count++;
		num /= 10;
	}

	_strData.resize(count + 1);
	char cSymbol = '+';
	if (_value < 0)
	{
		cSymbol = '-';
	}
	_strData[0] = cSymbol;

	size_t i = 0, j = 0;
	num = _value;
	INT64 ret = 1;
	for (i = 0; i < count - 1; ++i)
	{
		ret *= 10;
	}
	if (cSymbol == '-')
	{
		ret = 0 - ret;
	}
	for (j = 1; i < count + 1; ++j)
	{
		if (ret)
		{
			_strData[j] = num / ret + '0';
			num %= ret;
			ret /= 10;
		}
		else
		{
			break;
		}
	}
	
}

BigData::BigData(char* pData)
{
	assert(pData);
	char cSymbol =  pData[0];
	
	if(pData[0] >= '0' && pData[0] <= '9')
	{
		cSymbol = '+';
	}
	else if(cSymbol == '+' || cSymbol == '-')
	{
		pData++;
	}
	else
	{
		_value = UN_INIT;
		return;
	}
	while(*pData == '0')
	{
		pData++;
	}
	_strData.resize(strlen(pData) + 1);
	_strData[0] = cSymbol;

	_value  = 0;
	int icount = 1;
	while(*pData >= '0' && *pData <= '9')
	{
		_strData[icount++] = *pData;
		_value = _value * 10 + *pData - '0';
		pData++;
	}
	if(cSymbol == '-')
	{
		_value = 0 - _value;
	}
	_strData.resize(icount);
}


bool BigData::IsINT64Overflow()const
{
	string temp("+9223372036854775807");
	if(_strData[0] == '-')
	{
		temp = ("-9223372036854775808");
	}
	if(_strData.size() < temp.size())
	{
		return false;
	}
	else if(_strData.size() == temp.size() && _strData <= temp)
	{
		return false;
	}
	return true;
}
ostream& operator<<(ostream& os,const BigData& bigData)//ostream不能加const?
{
	if(!bigData.IsINT64Overflow())
	{
		os << bigData._value;
	}
	else
	{
		char* pData = (char*)bigData._strData.c_str();
		if (bigData._strData[0] == '+')
		{
			pData++;
		}
		os << pData;
	}
	return os;
}

bool BigData::IsLeftBig(const char* pLeft, int LSize, const char* pRight, int RSize)
{
	if (LSize > RSize
		|| LSize == RSize && strcmp(pLeft, pRight) >= 0)
	{
		return true;
	}
	return false;
}

char BigData::SubLoop(char* pLeft, int LSize, char* pRight, int RSize)
{
	assert(pLeft && pRight);
	char count = '0';
	while (true)
	{
		if (!IsLeftBig( pLeft, LSize, pRight, RSize))
		{
			break;
		}

		//相当于-=
		int LLen = LSize -1;
		int RLen = RSize - 1;
		while (LLen >= 0 && RLen >= 0)
		{
			char ret = pLeft[LLen] - '0';
			ret -= pRight[RLen] - '0';
			if (ret < 0)
			{
				pLeft[LLen - 1] -= 1;
				ret += 10;
			}
			pLeft[LLen] = ret + '0';
			LLen--;
			RLen--;
		}
		//去掉前面的0（090）
		while (*pLeft == '0' && LSize > 0)
		{
			pLeft++;
			LSize--;
		}
		count++;
	}
	return count;
}


BigData BigData::operator+(const BigData& bigData)
{
	if (!IsINT64Overflow() && !bigData.IsINT64Overflow())
	{
		if (_strData[0] != bigData._strData[0])
		{
			return BigData(_value + bigData._value);
		}
		else
		{
			if ((_strData[0] == '+' && MAX_INT64 - _value >= bigData._value)
				|| (_strData[0] == '-' && MIN_INT64 - _value <= bigData._value))
			{
				return BigData(_value + bigData._value);
			}
		}
	}
	
	if (_strData[0] == bigData._strData[0])
	{
		return BigData((char*)Add(_strData, bigData._strData).c_str());
	}
	return BigData((char*)Sub(_strData, bigData._strData).c_str());
}

BigData BigData::operator-(const BigData& bigData)
{
	if (!IsINT64Overflow() && !bigData.IsINT64Overflow())
	{
		if (_strData[0] == bigData._strData[0])
		{
			return BigData(_value - bigData._value);
		}
		else
		{
			if((_strData[0] == '+' && MAX_INT64 - _value >= bigData._value)
				|| (_strData[0] == '-' && MIN_INT64 - _value >= bigData._value))
			{
				return BigData(_value - bigData._value);
			}
		}
	}
	
	if (_strData[0] != bigData._strData[0])
	{
		return BigData((char*)Add(_strData, bigData._strData).c_str());
	}
	return BigData((char*)Sub(_strData, bigData._strData).c_str());
}

BigData BigData::operator*(const BigData& bigData)
{
	if (!IsINT64Overflow() && bigData.IsINT64Overflow())
	{
		if (_strData[0] == bigData._strData[0])
		{
			if (_strData[0] == '+' && MAX_INT64 / _value >= bigData._value ||
				 _strData[0] == '-' && MIN_INT64 / _value <= bigData._value)
			{
				return BigData(_value * bigData._value);
			}
		}
		else
		{
			if (_strData[0] == '+' && MAX_INT64 / _value >= bigData._value ||
				_strData[0] == '-' && MIN_INT64 / _value <= bigData._value)
			{
				return BigData(_value * bigData._value);
			}
		}
	}
	return BigData((char*)Mul(_strData, bigData._strData).c_str());
}

BigData BigData::operator/(const BigData& bigData)
{
	if (bigData._strData[1] == '0')
	{
		assert(false);
	}

	if (!IsINT64Overflow() && !IsINT64Overflow())
	{
		return BigData(_value / bigData._value);
	}

	if ( _strData.size() < bigData._strData.size()
		|| (_strData.size() == bigData._strData.size() && strcmp(_strData.c_str() + 1, bigData._strData.c_str() + 1) < 0))
	{
		return BigData(INT64(0));
	}

	if (bigData._strData == "+1" || bigData._strData == "-1")
	{
		string ret = _strData;
		if (_strData[0] != bigData._strData[0])
		{
			ret[0] = '-';
		}
		return BigData((char*)ret.c_str());
	}

	if (strcmp(_strData.c_str() + 1, bigData._strData.c_str() + 1) == 0)
	{
		string ret;
		ret.append(1, '+');
		ret.append(1, '1');
		if (_strData[0] != bigData._strData[0])
		{
			ret[0] = '-';
		}
		return BigData((char*)ret.c_str());
	}

	return BigData((char*)Div(_strData, bigData._strData).c_str());
}

string BigData::Add(string left, string right)
{
	int LSize = left.size();
	int RSize = right.size();
	if (LSize < RSize)
	{
		swap(left, right);
		swap(LSize, RSize);
	}

	string strRet;
	strRet.resize(LSize + 1);
	strRet[0] = left[0];
	char cStep = 0;

	for (int index = 1; index < LSize; ++index)
	{
		char cRet = left[LSize - index] + cStep - '0';
		if (index < RSize)
		{
			cRet += right[RSize - index] - '0';
		}
		strRet[LSize - index + 1] = cRet % 10 + '0';
		cStep = cRet/10;
	}
	strRet[1] = cStep + '0';
	return strRet;
}

string BigData::Sub(string left, string right)
{
	int LSize = left.size();
	int RSize = right.size();
	char cSymbol = left[0];
	if (LSize < RSize || (LSize == RSize && left < right))
	{
		swap(left, right);
		swap(LSize, RSize);
		if (cSymbol == '+')
		{
			cSymbol = '-';
		}
		else
		{
			cSymbol = '+';
		}
	}

	string strRet;
	strRet.resize(LSize);
	strRet[0] = cSymbol;
	
	for (int index = 1; index < LSize; ++index)
	{
		char cRet = left[LSize - index] - '0';
		if (index < RSize)
		{
			cRet -= right[RSize - index] - '0';
		}

		if (cRet < 0)
		{
			left[LSize - index -1] -= 1;
			cRet += 10;
		}
		strRet[LSize - index] = cRet + '0';
	}
	return strRet;
}

string BigData::Mul(string left, string right)
{
	int LSize = left.size();
	int RSize = right.size();
	if (LSize < RSize)
	{
		swap(left, right);
		swap(LSize, RSize);
	}

	char cSymbol = '+';
	if (left[0] != right[0])
	{
		cSymbol = '-';
	}

	string strRet;
	strRet.resize(LSize + RSize -1, '0');
	strRet[0] = cSymbol;
	char cStep = 0;
	int DataLen = strRet.size();
	int offset = 0;

	for (int LIndex = 1; LIndex < LSize; ++LIndex)
	{
		char cLeft = left[LSize - LIndex] - '0';
		cStep = 0;
		if (cLeft == '0')
		{
			++offset;
			continue;
		}
		for (int RIndex = 1; RIndex < RSize; ++RIndex)
		{
			char cRet = cLeft * (right[RSize - RIndex] - '0');
			//strRet不初始化时减去‘0‘会出错
			cRet += strRet[DataLen - RIndex - offset] - '0';
			cRet += cStep;
			cStep = cRet / 10;
			//1.不直接在strRet[DataLen - RIndex - offset] += cRet % 10 + '0';
			//而在cRet += strRet[DataLen - RIndex - offset] - '0';
			//是为了防止strRet[DataLen - RIndex - offset] += cRet % 10 + '0'后超过10,cStep加不上
			//2.防止在这个位置cRet % 10 + '0'重复+ '0'
			strRet[DataLen - RIndex - offset] = cRet % 10 + '0';
		}
		strRet[DataLen - RSize - offset] += cStep;
		++offset;
	}
	return strRet;
}

string BigData::Div(string left, string right)
{
	string strRet;
	strRet.append(1, '+');
	if (left[0] != right[0])
	{
		strRet[0] = '-';
	}

	char* pLeft = (char*)left.c_str() + 1;
	char* pRight = (char*)right.c_str() + 1;
	int LSize = left.size() - 1;
	int DataLen = right.size() - 1;
	for (int index = 0; index < LSize;)
	{
		if (*pLeft == '0')
		{
			strRet.append(1,'0');
			pLeft++;
			index++;
			continue;
		}
		if (!IsLeftBig(pLeft, DataLen, pRight, right.size() - 1))
		{
			strRet.append(1,'0');
			DataLen++;
			if (DataLen + index > LSize)
			{
				break;
			}
		}
		else
		{
			strRet.append(1, SubLoop(pLeft, DataLen, pRight, right.size() - 1));
			while (*pLeft == '0' && DataLen > 0)
			{
				pLeft++;
				index++;
				DataLen--;
			}
			DataLen++;
			if (DataLen + index > LSize)
			{
				break;
			}
		}
	}
	return strRet;
}