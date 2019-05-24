#pragma once
//#include"resourceRow.h"
#include"processCol.h"


//extern const unsigned ROW_COUNT = 4;
//extern const unsigned MAX_PROCESS = 512;
//extern HANDLE mutex;
//extern HANDLE Rmutex;
//extern Container* container;

class Container
{
public:
	ProcessCol list[MAX_PROCESS];
	unsigned processCount;
	ResourceRow avilable;

	void print();
	Container();
	bool pushProcess(ProcessCol* process);
	void release(unsigned pid);
	void requests(unsigned pid, ResourceRow request);
}; 