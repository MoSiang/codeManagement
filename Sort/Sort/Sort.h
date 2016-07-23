#pragma once

#include<iostream>
#include<cassert>
#include<string>
#include<stack>

using namespace std;

//O(N^2)
void InsertSort(int* a,int size)
{
	assert(a);
	for(int i=0; i<size-1; i++)
	{
		//end是已经有序的数的最后一个数的下标
		int end = i;
		int tmp = a[end+1];
		while(end >= 0 && a[end] > tmp)
		{
			a[end + 1] = a[end];
			end--;
		}
		a[end+1]  = tmp;
	}
}

//当N大时，平均时间复杂度大约在N^1.25 ~ 1.6N^1.25之间
void ShellSort(int *a,int n)
{
	assert(a);
	int gap = n;
	while(gap > 1)
	{
		gap = gap / 3 + 1;
		for(int i = 0; i<n-gap; i++)
		{
			int end = i;
			int tmp = a[end + gap];
			//a[end]要与tmp比较，不能把a[end]与a[end + tmp]比较，
			//循环执行一次后，a[end + gap]可能会改变，就不是原来a[end + gap]的值了
			//比较的是刚开始的a[end + gap]和前面那些end-=gap后a[end]的值
			while(end >= 0 && a[end] > tmp) 
			{
				a[end + gap] = a[end];
				end -= gap;
			}
			a[end + gap] = tmp;
		}
	}
}

//O(N^2)
void SelectSort(int* a, int n)
{
	assert(a);
	//end=0时就可以停止，不需要再进循环
	for(int end = n-1; end>0; end--)
	{
		int maxIndex = 0;
		//比较时从第二个数开始，到数组后面中要交换的下标，不需要到数组结尾
		for(int i = 1; i<=end; i++)
		{
			if(a[i] > a[maxIndex])
			{
				maxIndex = i;
			}
		}
		swap(a[maxIndex],a[end]);
	}
}
void SelectSortOP1(int* a, int n)
{
	assert(a);
	int left = 0;
	int right = n-1;
	while(left < right)
	{
		int maxIndex = left;
		int minIndex = left;
		for(int i = left+1; i<=right; i++)
		{
			if(a[i] > a[maxIndex])
			{
				maxIndex = i;
			}
			if(a[i] < a[minIndex])
			{
				minIndex = i;
			}
		}
		//当最大值在a[0]时，或者最小值在a[n-1]时交换会出错
		swap(a[maxIndex], a[right]);
		swap(a[minIndex], a[left]);
		left++;
		right--;
	}
}
void SelectSortOP2(int* a, int n)
{
	assert(a);
	int left = 0;
	int right = n-1;
	while(left < right)
	{
		for(int i = left; i <= right; i++)
		{
			if(a[i] > a[right])
			{
				swap(a[i],a[right]);
			}
			if(a[i] < a[left])
			{
				swap(a[i],a[left]);
			}
		}
		left++;
		right--;
	}	
}

void _AdjustDown(int* a, int n, int parent)
{
	int child = parent*2+1;
	while(child < n)
	{
		if((child+1)<n && a[child+1] > a[child])
		{
			++child;
		}
		if(a[child] > a[parent])
		{
			swap(a[child], a[parent]);
			parent = child;
			child = parent*2+1;
		}
		else
		{
			break;
		}
	}
}
//O(N*logN)
void HeapSort(int* a, int n)
{
	assert(a);
	for(int i = (n-2)/2; i>=0; --i)
	{
		_AdjustDown(a,n,i);
	}
	for(int i = n-1; i>0; --i)
	{
		swap(a[i],a[0]);
		//向下调整的数组大小不包括已经调好的数据
		_AdjustDown(a, i, 0);
	}
}

//O(N^2)
void BubbleSort(int* a, int n)
{
	assert(a);
	int end = n-1;
	bool exchange;
	while(end > 0)
	{
		for(int i = 1; i<=end; i++)
		{
			exchange = false;
			if(a[i-1] > a[i])
			{
				swap(a[i],a[i-1]);
				exchange = true;
			}
		}
		if(exchange == false)
		{
			break;
		}
		end--;
	}
}

int _GetMidIndex(int* a,int left,int right)
{
	int mid = left + (right - left)/2;
	if(a[left] < a[mid])
	{
		if(a[mid] < a[right])
		{
			return mid;
		}
		else if(a[left] < a[right])
		{
			return right;
		}
		else
		{
			return left;
		}
	}
	else
	{
		if(a[left] < a[right])
		{
			return left;
		}
		else if(a[mid] < a[right])
		{
			return right;
		}
		else
		{
			return left;
		}
	}

}
int _PartSort1(int* a,int left, int right)
{
	int mid= _GetMidIndex(a,left,right);
	swap(a[mid],a[right]);
	int key = a[right];
	int begin = left;
	int end = right-1;

	while(begin < end)
	{
		while(a[begin] < key)
		{
			++begin;
		}
		while(a[end] > key)
		{
			--end;
		}
		if(begin < end)
		{
			swap(a[begin], a[end]);
		}
		else
		{
			break;
		}
	}
	if(a[begin] > a[right])
	{
		swap(a[begin], a[right]);
		return begin;
	}
	else
	{
		return right;
	}
}

int _PartSort2(int* a, int left,int right)
{
	int mid = _GetMidIndex(a,left,right);
	swap(a[mid],a[right]);

	int key = a[right];
	int begin = left;
	int end = right;
	while(begin < end)
	{
		while(begin < end && a[begin] <= key)
		{
			++begin;
		}
		if(begin < end)
		{
			a[end] = a[begin];
		}
		while(begin < end && a[end] >= key)
		{
			--end;
		}
		if(begin < end)
		{
			a[begin] = a[end];
		}
	}
	a[begin] = key;
	return begin;
}

int _PartSort3(int* a, int left, int right)
{
	int mid = _GetMidIndex(a, left, right);
	swap(a[mid], a[right]);

	int key = a[right];
	int cur = left;
	int prev = left - 1;

	while(cur < right)
	{
		if((a[cur] < key) && ((++prev) != cur))
		{
			swap(a[cur],a[prev]);
		}
		++cur;
	}
	swap(a[++prev], a[right]);//交换时应该用a[right],而不是key,出了这个函数key就不存在了。
	return prev;
}

//[left,right]
void QuickSort(int* a,int left, int right)
{
	assert(a);
	if(left < right)
	{
		int div = _PartSort3(a,left,right);
		QuickSort(a, left, div-1);
		QuickSort(a, div+1, right);
	}
}
void QuickSort_OP(int* a, int left, int right)
{
	assert(a);
	if(left >= right)
	{
		return;
	}
	if(left - right < 16)
	{
		InsertSort(a,sizeof(a)/sizeof(a[0]));
	}
	else
	{
		int div = _PartSort3(a,left,right);
		QuickSort_OP(a, left, div-1);
		QuickSort_OP(a, div+1, right);
	}
}
void QuickSort_NONR(int* a, int left, int right)
{
	assert(a);
	stack<int> s;
	s.push(left);
	s.push(right);

	while(!s.empty())
	{
		int end  = s.top();
		s.pop();
		int begin = s.top();
		s.pop();

		int div = _PartSort1(a, begin, end);
		if(begin < div-1)
		{
			s.push(begin);
			s.push(div-1);
		}
		if(div + 1 < end)
		{
			s.push(div + 1);
			s.push(end);
		}		
	}
}




void _Merge(int* a, int* tmp, int begin1, int end1, int begin2, int end2)
{
	int index = begin1;
	while(begin1 <= end1 && begin2 <= end2)
	{
		if(a[begin1] < a[begin2])
		{
			tmp[index] = a[begin1];
			++begin1;
		}
		else
		{
			tmp[index] = a[begin2];
			++begin2;
		}
		++index;
	}
	while(begin1 <= end1)
	{
		tmp[index++] = a[begin1++];
	}
	while(begin2 <= end2)
	{
		tmp[index++] = a[begin2++];
	}
}
void _MergeSort(int* a, int* tmp, int left, int right)
{
	if(left >= right)
	{
		return;
	}
	int mid = left + (right - left)/2;
	_MergeSort(a, tmp, 0, mid);
	_MergeSort(a, tmp, mid+1, right);

	_Merge(a, tmp, left, mid, mid+1, right);
	memcpy(a+left, tmp+left, (right-left+1)*sizeof(int));

}
void MergeSort(int* a, int n)
{
	int* tmp = new int[n];
	_MergeSort(a, tmp, 0, n-1);
	delete[] tmp;
}


//基数排序
//LSD先排低位     LMD先排高位
int _MaxDigit(int* a, int n)
{
	int max = 10;
	int digit =1;
	for(int i = 0; i<n; i++)
	{
		while(a[i] > max)
		{
			digit++;
			max *= 10;
		}
	}
	return digit;
}
void LSDSort(int* a, int n)
{
	int count[10] = {0};
	int start[10] = {0};
	int* butket = new int[n];
	int BaseDigit = 1;
	int digit = _MaxDigit(a, n);

	for(int i = 0; i<digit; i++)
	{
		memset(count, 0, sizeof(int)*10);
		for(i = 0; i<n; i++)
		{
			int num = (a[i]/BaseDigit)%10;
			count[num]++;
		}
		start[0] = 0;
		for(i = 1; i<10; i++)
		{
			start[i] = count[i-1] + start[i-1];
		}
		for(i = 0; i<n; i++)
		{
			int num = (a[i]/BaseDigit)%10;
			int& index = start[num];
			butket[index++] = a[i];
		}
		BaseDigit *= 10;
		memcpy(a, butket, n*sizeof(int));
	}
	delete[] butket;
}

void CountSort(int* a, int n)
{
	int* count = new int[10];
	int* tmp = new int[n];
	int i;
    memset(count, 0, 10*sizeof(int));
	for(i=0; i<n; i++)
	{
		tmp[i] = a[i];
	}

    for(i=0; i<n; i++) 
	{
        count[tmp[i]]++;  
	}  

    for(i=1; i<10; i++) 
	{
        count[i] += count[i-1];  
	}  

    for(int i = n; i>0; i--)  
    {  
        a[count[tmp[i-1]]-1] = tmp[i-1];  
        count[tmp[i-1]]--;    
    }   
   delete[] count;
   delete[] tmp;
}