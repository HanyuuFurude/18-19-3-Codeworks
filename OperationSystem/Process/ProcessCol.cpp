#pragma once
#include<iostream>
#include"processCol.h"
#include"Container.h"
extern Container* container;
HANDLE mutex;
HANDLE Rmutex;

DWORD WINAPI ProcessCol::running(LPVOID lpThreadParemeter)
{
	//Func copy = *(Func*)(lpThreadParemeter);
	//ProcessCol copyPro = *(ProcessCol*)copy.ptr;
	unsigned pid = (unsigned)lpThreadParemeter;
	while (true)
	{
		WaitForSingleObject(Rmutex, INFINITE);
		if (rand() % 2 == 1)
		{
			// request
			ResourceRow temp;
			//ResourceRow* src = &((ProcessCol*)((Func*)(lpThreadParemeter))->ptr)->need;
			ResourceRow* src = &container->list[pid].need;
			for (unsigned i = 0; i < ROW_COUNT; ++i)
			{
				if (src->res[i] == 0)
				{
					temp.res[i] = 0;
				}
				else
				{
					temp.res[i] = unsigned(rand() % (src->res[i]));
				}
			}
			//((Func*)(lpThreadParemeter))->request(((ProcessCol*)((Func*)(lpThreadParemeter))->ptr)->pid, temp);
			//copy.request(copyPro.pid, temp);
			container->requests(pid, temp);
			//((Func*)(lpThreadParemeter))->print();
			//copy.print();
			container->print();
		}
		else
		{
			//release
			//((Func*)(lpThreadParemeter))->release(((ProcessCol*)((Func*)(lpThreadParemeter))->ptr)->pid);
			//copy.release(copyPro.pid);
			container->release(pid);
			//std::cout << ((ProcessCol*)((Func*)(lpThreadParemeter))->ptr)->pid << "已释放" << std::endl;
			std::cout << pid << "已释放" << std::endl;
		}
		ReleaseSemaphore(Rmutex, 1, nullptr);
		Sleep(1000);
	}
	CloseHandle(__threadhandle);
}
HANDLE ProcessCol::start()
{
	//Func copy = func;
	//copy.ptr = (void*)this;
	HANDLE thr;
	thr = CreateThread(
		nullptr,
		0,
		(LPTHREAD_START_ROUTINE)this->running,
		(LPVOID)pid,
		0,
		nullptr
	);
	return thr;
}
ProcessCol::ProcessCol(unsigned pid)
{
	this->pid = pid;
	for (unsigned i = 0; i < ROW_COUNT; ++i)
	{
		max.res[i] = rand() % 10;
		allocation.res[i] = 0;
		need.res[i] = max.res[i];
	}
}
ProcessCol::ProcessCol()
{
	this->pid = 0;
	for (unsigned i = 0; i < ROW_COUNT; ++i)
	{
		max.res[i] = rand() % 10;
		allocation.res[i] = 0;
		need.res[i] = max.res[i];
	}
}

