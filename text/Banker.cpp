#include <iostream>
// #include <Windows.h>
// #include <process.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

const unsigned ROW_COUNT = 4;
const unsigned MAX_PROCESS = 512;
struct ResourceRow
{
public:
	unsigned res[ROW_COUNT];
	ResourceRow()
	{
		for(unsigned i = 0; i < ROW_COUNT; ++i)
		{
			res[i]=0;
		}
	}
	ResourceRow(unsigned* input)
	{
		for(int i = 0;i<ROW_COUNT;++i)
		{
			res[i]=input[i];
		}
	}
};
bool operator>=(const ResourceRow &a,const ResourceRow &b)
{
	for (int i=0;i<ROW_COUNT;++i)
	{
		if(a.res[i]<b.res[i])
			return false;
	}
	return true;
}
class ProcessCol
{
public:
	unsigned pid;
	ResourceRow allocation;
	ResourceRow max;
	ResourceRow need;
	ProcessCol(unsigned pid)
	{
		this->pid = pid;
	}
	ProcessCol()
	{
		this->pid = 0; 
	}
};
class Container
{
public:
	ProcessCol* list[MAX_PROCESS];
	unsigned processCount;
	ResourceRow avilable;
	HANDLE mutex;
	Container()
	{
		processCount = 0;
		mutex = CreateSemaphore(nullptr, 1, 1, nullptr);
	}
	bool pushProcess(ProcessCol* process)
	{
		if (processCount>=MAX_PROCESS-1)
		{return false;}
		process->pid=processCount;
		list[processCount] = process;
		processCount+=1;
		return true;
	}
	bool release(unsigned pid)
	{
		WaitForSingleObject(mutex, INFINITE);
		for(unsigned i=0;i<ROW_COUNT;++i)
		{
			avilable.res[i]+=list[pid].allocation.res[i];
			list[pid].allocation.res[i]=0;
			list[pid].need.res[i] = list[pid].max.res[i];
		}
		ReleaseSemaphore(mutex, 1, nullptr);
	}
	bool requests(unsigned pid,ResourceRow request)
	{
		WaitForSingleObject(mutex, INFINITE);
		ResourceRow newAvilable;
		for (int i = 0;i<ROW_COUNT;++i)
		{
			newAvilable.res[i]=avilable.res[i];
		}
		int count = this.processCount;
		bool * flag = new bool[count];
		for(unsigned i = 0;i<count;++i)
		{
			flag[i]=false;
		}
		while(count>0)
		{
			key = false;
			for(unsigned i=0;i<this.processCount;++i)
			{
				if(flag[i]==false)
				{
					if(newAvilable.res>=list[i].need)
					{
						for (unsigned j=0;j<ROW_COUNT;++j)
						{
							newAvilable.res[i]+=list[i].allocation.res[i];
						}
						flag[i]=true;
						key=true;
						count-=1;
					}
				}
			}
			if(key==false)
				return false;
		}
		for (int i=0;i<ROW_COUNT;++i)
		{
			avilable.res[i]-=request.res[i];
			list[pid].allocation.res[i]+=request.res[i];
			list[pid].need.res[i] = list[pid].max.res[i]-list[pid].allocation.res[i];
		}
		ReleaseSemaphore(mutex, 1, nullptr);
	}
	
};
int main()
{
	Container container;
	ProcessCol p1;

	
	// HANDLE p = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)producer, nullptr, 0L, nullptr);
}