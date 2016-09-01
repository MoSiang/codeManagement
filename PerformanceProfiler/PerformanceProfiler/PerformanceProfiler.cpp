#include"PerformanceProfiler.h"

void PPSection::Begin(int id)
{
	//id != -1时表示多线程场景
	if (id != -1)
	{
		lock_guard<mutex> lock(_mtx);

		//分别统计线程和总的花费时间、调用次数
		if (_RefCountMap[id]++ == 0)
		{
			_BeginTimeMap[id] = clock();
		}
	}
	else
	{
		if (_TotalRefCount++ == 0)
		{
			_TotalBeginTime = clock();
		}
	}
}

void PPSection::End(int id)
{
	if (id != -1)
	{
		lock_guard<mutex> lock(_mtx);

		if (--_RefCountMap[id] == 0)
		{
			_CostTimeMap[id] += clock() - _BeginTimeMap[id];
		}
		++_CallCountMap[id];
	}
	else
	{
		if (--_TotalRefCount == 0)
		{
			_TotalCostTime += clock() - _TotalBeginTime;
		}
		++_TotalCallCount;
	}
}


PPSection* PerformanceProfiler::CreateSection(const char* filename, const char* function, size_t line, const char* desc)
{
	PPNode node(filename, function, line, desc);
	PPSection* section = NULL;

	//RAII
	lock_guard<mutex> lock(_mtx);

	PP_MAP::iterator it = _PPMap.find(node);
	if (it != _PPMap.end())
	{
		section = it->second;
	}
	else
	{
		section = new PPSection;
		_PPMap.insert(pair<PPNode, PPSection*>(node, section));
	}
	return section;
}

void PerformanceProfiler::Output()
{
	int options = ConfigManager::GetInstance()->GetOptions();
	if (options & SAVE_TO_CONSOLE)
	{
		ConsoleSaveAdapter csa;
		_Output(csa);
	}
	
	if (options & SAVE_TO_FILE)
	{
		FileSaveAdapter fsa("PerformanceProfilerReport.txt");
		_Output(fsa);
	}
}

void PerformanceProfiler::_Output(SaveAdapter& sa)
{
	vector<PP_MAP::iterator> vInfos;
	PP_MAP::iterator ppIt = _PPMap.begin();
	while (ppIt != _PPMap.end())
	{
		PPSection* section = ppIt->second;
		map<int, LongType>::iterator timeIt;
		timeIt = section->_CostTimeMap.begin();
		while (timeIt != section->_CostTimeMap.end())
		{
			PPSection* section = ppIt->second;
			section->_TotalCallCount += section->_CallCountMap[timeIt->first];

			++timeIt;
		}
		vInfos.push_back(ppIt);
		++ppIt;
	}
	struct SortByCostTime
	{
		bool operator()(PP_MAP::iterator l, PP_MAP::iterator r) const
		{
			return l->second->_TotalCostTime > r->second->_TotalCostTime;
		}
	};
	// 按花费时间排序
	sort(vInfos.begin(), vInfos.end(), SortByCostTime());

	int num = 1;
	//PP_MAP::iterator ppIt = _ppMap.begin();

	for (size_t i = 0; i < vInfos.size(); ++i)
	{
		ppIt = vInfos[i];
		const PPNode& node = ppIt->first;
		PPSection* section = ppIt->second;

		// node信息
		sa.Save("No.%d, Desc:%s\n", num++, node._desc.c_str());
		sa.Save("Filename:%s, Line:%d, Function:%s\n"
			, node._filename.c_str()
			, node._line
			, node._function.c_str());

		// section信息
		map<int, LongType>::iterator timeIt;
		timeIt = section->_CostTimeMap.begin();
		while (timeIt != section->_CostTimeMap.end())
		{
			int id = timeIt->first;
			sa.Save("ThreadId:%d, CostTime:%.2f s, CallCount:%lld\n"
				, id
				, (double)timeIt->second / 1000
				, section->_CallCountMap[id]);

			section->_TotalCostTime += timeIt->second;
			section->_TotalCallCount += section->_CallCountMap[id];

			++timeIt;
		}

		sa.Save("TotalCostTime:%.2f s, TotalCallCount:%lld, AverCostTime:%lld ms\n\n"
			, (double)section->_TotalCostTime / 1000
			, section->_TotalCallCount
			, section->_TotalCostTime / section->_TotalCallCount);

		++ppIt;
	}
}