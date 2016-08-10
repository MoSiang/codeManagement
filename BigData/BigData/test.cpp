#include"BigData.h"


void FuncTest()
{
	BigData bd1("+99999999a99999999584444444444");
	cout << bd1 << endl;
	BigData bd2("-9999999999999999584444444444");
	cout << bd2 << endl;
	BigData bd3("+00009999999999999999584444444444");
	cout << bd3 << endl;
	BigData bd4("+9999999999999999584444444444999999999999999999999999999999999999999");
	cout << bd4 << endl;
}

void TestAdd()
{
	BigData left1("9223372036854775807");
	BigData right1("12");
	cout << "加法：" << endl;
	cout << left1 + right1 << endl;

	BigData left2(9223372036854775807);
	BigData right2(12);
	cout << left2 + right2 << endl;

}

void TestSub()
{
	BigData left1("-9223372036854775808");
	BigData right1("1");
	cout << "减法：" << endl;
	cout << left1 - right1 << endl;

	BigData left2(-9223372036854775808);
	BigData right2(1);
	cout << left2 - right2 << endl;
}

void TestMul()
{
	BigData left1("9223372036854775807");
	BigData right1("2");
	cout << "乘法：" << endl;
	cout << left1 * right1 << endl;

	BigData left2(9223372036854775807);
	BigData right2(2);
	cout << left2 * right2 << endl;

	BigData left3("-9223372036854775807");
	BigData right3("2");
	cout << left3 * right3 << endl;
}

void TestDiv()
{
	BigData left1("22222222222222222222222222222222222222");
	BigData right1("33");
	cout << "除法：" << endl;
	cout << left1 / right1 << endl;

	BigData left2("-33333333333333333333333333333");
	BigData right2("33333333333333333333333333333");
	cout << left2 / right2 << endl;

	BigData left3("9223372036854775807");
	BigData right3("-1");
	cout << left3 / right3 << endl;
}

int main()
{
	//FuncTest();
	//TestAdd();
	//TestSub();
	//TestMul();
	TestDiv();
	getchar();
	return 0;
}