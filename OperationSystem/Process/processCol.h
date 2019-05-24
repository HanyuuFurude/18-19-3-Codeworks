#pragma once
#include <process.h>
#include <Windows.h>
#include"resourceRow.h"
//#include "Container.h"
//#include "banker.h"


//extern const unsigned ROW_COUNT = 4;
//extern const unsigned MAX_PROCESS = 512;
//extern HANDLE mutex;
//extern HANDLE Rmutex;
//extern class Container;
//extern Container* container;

class ProcessCol
{
public:
	unsigned pid;
	ResourceRow allocation;
	ResourceRow max;
	ResourceRow need;
	static DWORD WINAPI running(LPVOID lpThreadParemeter);
	HANDLE start();
	ProcessCol(unsigned pid);
	ProcessCol();
}; 
