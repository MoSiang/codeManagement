#include"PerformanceProfiler.h"

//void Testpp1()
//{
//	PerformanceProfiler pp;
//
//	//����
//	PPSection* ps1 = pp.CreateSection(__FILE__, __FUNCTION__, __LINE__, "����");
//	ps1->Begin();
//	Sleep(500);
//	ps1->End();
//
//	//�м��߼�->Ȩ�޴���
//	PPSection* ps2 = pp.CreateSection(__FILE__, __FUNCTION__, __LINE__, "�м��߼�");
//	ps2->Begin();
//	Sleep(2500);
//	ps2->End();
//
//	//���ݿ�
//	PPSection* ps3 = pp.CreateSection(__FILE__, __FUNCTION__, __LINE__, "���ݿ�");
//	ps3->Begin();
//	Sleep(1500);
//	ps3->End();
//}

//void Testpp2()
//{
//	PERFORMANCE_PROFILER_EE_BEGIN(network, "����");
//	Sleep(1000);
//	PERFORMANCE_PROFILER_EE_END(network);
//
//	PERFORMANCE_PROFILER_EE_BEGIN(mid, "�м��߼�");
//	Sleep(2000);
//	PERFORMANCE_PROFILER_EE_END(mid);
//
//	PERFORMANCE_PROFILER_EE_BEGIN(sql, "���ݿ�");
//	Sleep(3000);
//	PERFORMANCE_PROFILER_EE_END(sql);
//}
//
//LongType Fib(LongType n)
//{
//	PERFORMANCE_PROFILER_EE_BEGIN(in, "����");
//	LongType ret = n;
//	if (n < 2)
//	{
//		ret = n;
//	}
//	else
//	{
//		ret = Fib(n - 1) + Fib(n - 2);
//	}
//	PERFORMANCE_PROFILER_EE_END(in);
//	return ret;
//}
////�����Ĵ�����ǵݹ��
//void TestFib()
//{
//	PERFORMANCE_PROFILER_EE_BEGIN(out, "����");
//	Fib(25);
//	PERFORMANCE_PROFILER_EE_END(out);
//}

void TestSingleThead()
{
	PERFORMANCE_PROFILER_EE_ST_BEGIN(network, "����s");
	// ����
	Sleep(200);
	PERFORMANCE_PROFILER_EE_ST_END(network);

	PERFORMANCE_PROFILER_EE_ST_BEGIN(mid, "�м��߼�s");
	// �м��߼�
	Sleep(300);

	PERFORMANCE_PROFILER_EE_ST_END(mid);

	PERFORMANCE_PROFILER_EE_ST_BEGIN(sql, "���ݿ�s");
	// ���ݿ�
	Sleep(400);

	PERFORMANCE_PROFILER_EE_ST_END(sql);
}
void Fun(size_t n)
{
	while (n--)
	{
		PERFORMANCE_PROFILER_EE_MT_BEGIN(network, "����m");
		Sleep(100);
		PERFORMANCE_PROFILER_EE_MT_END(network);

		PERFORMANCE_PROFILER_EE_MT_BEGIN(mid, "�м��߼�m");
		Sleep(200);
		PERFORMANCE_PROFILER_EE_MT_END(mid);

		PERFORMANCE_PROFILER_EE_MT_BEGIN(sql, "���ݿ�m");
		Sleep(300);
		PERFORMANCE_PROFILER_EE_MT_END(sql);
	}
}
//���ݲ�׼ȷ���̰߳�ȫ����
void TestMultiThread()
{
	thread t1(Fun, 5);
	thread t2(Fun, 4);
	thread t3(Fun, 2);

	t1.join();
	t2.join();
	t3.join();
}

int main()
{
	//Testpp1();
	//Testpp1();
	//Testpp1();

	//PerformanceProfiler::GetInstance()->Output();

	//Testpp2();

	//TestFib();

	SET_CONFIG_OPTIONS(PERFORMANCE_PROFILER
		| SAVE_TO_FILE
		| SAVE_TO_CONSOLE
		| SORT_BY_COSTTIME);

	TestMultiThread();
	TestSingleThead();
	return 0;
}
