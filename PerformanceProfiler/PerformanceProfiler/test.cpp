#include"PerformanceProfiler.h"

//void Testpp1()
//{
//	PerformanceProfiler pp;
//
//	//网络
//	PPSection* ps1 = pp.CreateSection(__FILE__, __FUNCTION__, __LINE__, "网络");
//	ps1->Begin();
//	Sleep(500);
//	ps1->End();
//
//	//中间逻辑->权限处理
//	PPSection* ps2 = pp.CreateSection(__FILE__, __FUNCTION__, __LINE__, "中间逻辑");
//	ps2->Begin();
//	Sleep(2500);
//	ps2->End();
//
//	//数据库
//	PPSection* ps3 = pp.CreateSection(__FILE__, __FUNCTION__, __LINE__, "数据库");
//	ps3->Begin();
//	Sleep(1500);
//	ps3->End();
//}

//void Testpp2()
//{
//	PERFORMANCE_PROFILER_EE_BEGIN(network, "网络");
//	Sleep(1000);
//	PERFORMANCE_PROFILER_EE_END(network);
//
//	PERFORMANCE_PROFILER_EE_BEGIN(mid, "中间逻辑");
//	Sleep(2000);
//	PERFORMANCE_PROFILER_EE_END(mid);
//
//	PERFORMANCE_PROFILER_EE_BEGIN(sql, "数据库");
//	Sleep(3000);
//	PERFORMANCE_PROFILER_EE_END(sql);
//}
//
//LongType Fib(LongType n)
//{
//	PERFORMANCE_PROFILER_EE_BEGIN(in, "里面");
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
////剖析的代码的是递归的
//void TestFib()
//{
//	PERFORMANCE_PROFILER_EE_BEGIN(out, "外面");
//	Fib(25);
//	PERFORMANCE_PROFILER_EE_END(out);
//}

void TestSingleThead()
{
	PERFORMANCE_PROFILER_EE_ST_BEGIN(network, "网络s");
	// 网络
	Sleep(200);
	PERFORMANCE_PROFILER_EE_ST_END(network);

	PERFORMANCE_PROFILER_EE_ST_BEGIN(mid, "中间逻辑s");
	// 中间逻辑
	Sleep(300);

	PERFORMANCE_PROFILER_EE_ST_END(mid);

	PERFORMANCE_PROFILER_EE_ST_BEGIN(sql, "数据库s");
	// 数据库
	Sleep(400);

	PERFORMANCE_PROFILER_EE_ST_END(sql);
}
void Fun(size_t n)
{
	while (n--)
	{
		PERFORMANCE_PROFILER_EE_MT_BEGIN(network, "网络m");
		Sleep(100);
		PERFORMANCE_PROFILER_EE_MT_END(network);

		PERFORMANCE_PROFILER_EE_MT_BEGIN(mid, "中间逻辑m");
		Sleep(200);
		PERFORMANCE_PROFILER_EE_MT_END(mid);

		PERFORMANCE_PROFILER_EE_MT_BEGIN(sql, "数据库m");
		Sleep(300);
		PERFORMANCE_PROFILER_EE_MT_END(sql);
	}
}
//数据不准确，线程安全问题
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
