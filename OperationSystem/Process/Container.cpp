#pragma once
#include<iostream>
#include"Container.h"

Container* container;
extern HANDLE mutex;
extern HANDLE Rmutex;
void Container::print()
{
	std::cout << "[avilable]" << avilable.str() << std::endl;
	for (unsigned i = 0; i < processCount; ++i)
	{
		std::cout << list[i].pid << "    " << list[i].allocation.str() << "    " << list[i].max.str() << "    " << list[i].need.str() << std::endl;
	}
	std::cout << std::endl;
}
Container::Container()
{
	processCount = 0;
	mutex = CreateSemaphore(nullptr, 1, 1, nullptr);
	Rmutex = CreateSemaphore(nullptr, 1, 1, nullptr);
	//for (unsigned i = 0; i < MAX_PROCESS; ++i)
	//{
	//	list[i] = nullptr;
	//}
}
bool Container::pushProcess(ProcessCol* process)
{
	if (processCount >= MAX_PROCESS - 1)
	{
		return false;
	}
	process->pid = processCount;
	list[processCount] = *process;
	processCount += 1;
	return true;
}
void Container::release(unsigned pid)
{
	WaitForSingleObject(mutex, INFINITE);
	for (unsigned i = 0; i < ROW_COUNT; ++i)
	{
		avilable.res[i] += list[pid].allocation.res[i];
		list[pid].allocation.res[i] = 0;
		list[pid].need.res[i] = list[pid].max.res[i];
	}
	std::cout << "pid: " << pid << " 已释放" << std::endl;
	container->print();
	ReleaseSemaphore(mutex, 1, nullptr);
}
void Container::requests(unsigned pid, ResourceRow request)
{
	WaitForSingleObject(mutex, INFINITE);
	ResourceRow newAvilable;
	for (int i = 0; i < ROW_COUNT; ++i)
	{
		newAvilable.res[i] = avilable.res[i];
	}
	unsigned count = this->processCount;
	bool* flag = new bool[count];
	for (unsigned i = 0; i < count; ++i)
	{
		flag[i] = false;
	}
	while (count > 0)
	{
		bool key = false;
		for (unsigned i = 0; i < this->processCount; ++i)
		{
			if (flag[i] == false)
			{
				if (newAvilable.res >= list[i].need)
				{
					for (unsigned j = 0; j < ROW_COUNT; ++j)
					{
						newAvilable.res[i] += list[i].allocation.res[i];
					}
					flag[i] = true;
					key = true;
					count -= 1;
				}
			}
		}
		if (count == 0)
		{
			std::cout << "pid: " << pid << " 请求成功" << std::endl;
			for (unsigned i = 0; i < ROW_COUNT; ++i)
			{
				list[pid].allocation.res[i] += request.res[i];
				list[pid].need.res[i] -= request.res[i];
				avilable.res[i] -= request.res[i];
			}
			container->print();
			ReleaseSemaphore(mutex, 1, nullptr);
			return;
		}
		if (key == false)
		{
			std::cout << "pid: " << pid << "请求失败" << std::endl;
			container->print();
			ReleaseSemaphore(mutex, 1, nullptr);
			return;
		}
	}
	for (int i = 0; i < ROW_COUNT; ++i)
	{
		avilable.res[i] -= request.res[i];
		list[pid].allocation.res[i] += request.res[i];
		list[pid].need.res[i] = list[pid].max.res[i] - list[pid].allocation.res[i];
	}
	//ReleaseSemaphore(mutex, 1, nullptr);
}
