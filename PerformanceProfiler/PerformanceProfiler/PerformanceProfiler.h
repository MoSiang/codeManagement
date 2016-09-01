#pragma once

#include<iostream>
#include<string>
#include<map>
#include<algorithm>

//c++11
#include<unordered_map>
#include<thread>
#include<mutex>

#include<ctime>
#include<cassert>

#ifdef _WIN32
	#include<windows.h>
#else
	#include<pthread.h>
#endif

using namespace std;

typedef long long LongType;

/////////////////////////////////////////////////////////////
//单例的基类->饿汉模式
template<class T>
class Singleton
{
public:
	static T* GetInstance()
	{
		assert(_SInstance);
		return _SInstance;
	}
protected:
	static T* _SInstance;
};
template<class T>
T* Singleton<T>::_SInstance = new T;


class SaveAdapter
{
public:
	virtual void Save(const char* format, ...) = 0;
};

class ConsoleSaveAdapter :public SaveAdapter
{
public:
	virtual void Save(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		vfprintf(stdout, format, args);
		va_end(args);
	}
};

class FileSaveAdapter : public SaveAdapter
{
public:
	FileSaveAdapter(const char* filename)
	{
		_fout = fopen(filename, "w");
		assert(_fout);
	}

	~FileSaveAdapter()
	{
		if (_fout)
		{
			fclose(_fout);
		}
	}

	virtual void Save(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		vfprintf(_fout, format, args);
		va_end(args);
	}

protected:
	FileSaveAdapter(FileSaveAdapter&);
	FileSaveAdapter& operator=(FileSaveAdapter&);
protected:
	FILE* _fout;
};

class SqlSaveAdapter :public SaveAdapter
{};

////////////////////////////////////////////////////////////
//配置管理
enum ConfigOptions
{
	NONE = 0,
	PERFORMANCE_PROFILER = 1,
	SAVE_TO_CONSOLE = 2,
	SAVE_TO_FILE = 4,
	SORT_BY_COSTTIME = 8,
	SORT_BY_CALLCOUNT = 16,
};

class ConfigManager :public Singleton<ConfigManager>
{
public:
	void SetOptions(int options)
	{
		_options = options;
	}

	void AddOption(int option)
	{
		_options |= option;
	}

	void DelOption(int option)
	{
		_options &= (~option);
	}

	int GetOptions()
	{
		return _options;
	}
protected:
	friend class Singleton<ConfigManager>;

	ConfigManager()
		:_options(NONE)
	{}
	ConfigManager(const ConfigManager&);
	ConfigManager& operator=(const ConfigManager&);
protected:
	int _options;
};


//////////////////////////////////////////////////////////////
//PerformanceProfiler
struct PPNode
{
	PPNode(const char* filename, const char* function, size_t line, const char* desc)
	:_filename(filename)
	, _function(function)
	, _line(line)
	, _desc(desc)
	{}

	bool operator==(const PPNode& node)const
	{
		if (_line == node._line && _function == node._function && _filename == node._filename)
		{
			return true;
		}
		return false;
	}

	string _filename;
	string _function;
	size_t _line;
	string _desc;                //附加描述信息
};

struct PPSection
{
	PPSection()
	:_TotalCostTime(0)
	, _TotalCallCount(0)
	, _TotalRefCount(0)
	{}

	void Begin(int id);
	void End(int id);

	//<id,统计信息>
	map<int, LongType> _BeginTimeMap;
	map<int, LongType> _CostTimeMap;
	map<int, LongType> _CallCountMap;
	map<int, LongType> _RefCountMap;

	LongType _TotalBeginTime;
	LongType _TotalCostTime;          //花费时间
	LongType _TotalCallCount;         //调用次数
	LongType _TotalRefCount;          //引用计数，解决递归问题

	mutex _mtx;
};

//PPNode的计算哈希值的仿函数
struct PPNodeHash
{
	static size_t BKDRHash(const char * str)
	{
		unsigned int seed = 131; // 31 131 1313 13131 131313
		unsigned int hash = 0;
		while (*str)
		{
			hash = hash * seed + (*str++);
		}
		return (hash & 0x7FFFFFFF);
	}

	size_t operator()(const PPNode& node)const
	{
		static string hash;
		hash = node._desc;
		hash += node._function;
		return BKDRHash(hash.c_str());
	}

};

class PerformanceProfiler:public Singleton<PerformanceProfiler>
{
	//o(1)
	typedef unordered_map<PPNode, PPSection*, PPNodeHash> PP_MAP;
public:
	PPSection* CreateSection(const char* filename, const char* function, size_t line, const char* desc);
	void Output();
protected:
	void _Output(SaveAdapter& sa);
	friend class Singleton<PerformanceProfiler>;

	PerformanceProfiler(){}
	PerformanceProfiler(const PerformanceProfiler&);
	PerformanceProfiler& operator=(const PerformanceProfiler&);

protected:
	PP_MAP _PPMap;               //统计资源信息的容器
	mutex _mtx;
};

struct Report
{
	~Report()
	{
		PerformanceProfiler::GetInstance()->Output();
	}
};
static Report report;

static int GetThreadId()
{
#ifdef _WIN32
	return GetCurrentThreadId();
#else
	return thread_self();
#endif
}


//#define PERFORMANCE_PROFILER_EE_BEGIN(sign, desc) \
//	PPSection* ps##sign = PerformanceProfiler::GetInstance()->CreateSection(__FILE__, __FUNCTION__, __LINE__, desc);\
//	ps##sign->Begin(GetThreadId());
//
//#define PERFORMANCE_PROFILER_EE_END(sign) \
//	ps##sign->End(GetThreadId());

//剖析单线程场景
#define PERFORMANCE_PROFILER_EE_ST_BEGIN(sign, desc) \
	PPSection* ps##sign = NULL;						 \
	if (ConfigManager::GetInstance()->GetOptions() & PERFORMANCE_PROFILER)\
	{												 \
		ps##sign = PerformanceProfiler::GetInstance()->CreateSection(__FILE__, __FUNCTION__, __LINE__, desc); \
		ps##sign->Begin(-1);						 \
	}
#define PERFORMANCE_PROFILER_EE_ST_END(sign) \
	if (ps##sign)								\
		ps##sign->End(-1);


// 剖析多线程场景
#define PERFORMANCE_PROFILER_EE_MT_BEGIN(sign, desc) \
	PPSection* ps##sign = NULL;						 \
	if (ConfigManager::GetInstance()->GetOptions() & PERFORMANCE_PROFILER)\
	{												 \
		ps##sign = PerformanceProfiler::GetInstance()->CreateSection(__FILE__, __FUNCTION__, __LINE__, desc); \
		ps##sign->Begin(GetThreadId());				 \
	}

#define PERFORMANCE_PROFILER_EE_MT_END(sign)	\
	if (ps##sign)								\
		ps##sign->End(GetThreadId());


#define SET_CONFIG_OPTIONS(option)				\
	ConfigManager::GetInstance()->SetOptions(option);