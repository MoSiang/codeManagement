#include<iostream>

#include"FileCompress.h"
#include<windows.h>

using namespace std;

void Test()
{
	FileCompress fc;
	int begin = GetTickCount();
	fc.Compress("Input.txt");
	int end = GetTickCount();
	cout << "ѹ���ļ���ʱ��" << end - begin << endl;

	begin = GetTickCount();
	fc.UnCompress("Input.txt");
	end = GetTickCount();
	cout << "��ѹ���ļ���ʱ��" << end - begin << endl;
}

void TestBigFile()
{
	FileCompress fc;
	int begin = GetTickCount();
	fc.Compress("Input.BIG");
	int end = GetTickCount();
	cout << "ѹ���ļ���ʱ��" << end - begin << endl;

	begin = GetTickCount();
	fc.UnCompress("Input.BIG");
	end = GetTickCount();
	cout << "��ѹ���ļ���ʱ��" << end - begin << endl;
}
int main()
{
	//Test();
	TestBigFile();
	getchar();
	return 0;
}