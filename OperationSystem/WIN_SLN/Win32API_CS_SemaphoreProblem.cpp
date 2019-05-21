#include <iostream>
#include <Windows.h>
#include <process.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

constexpr unsigned BUFFER = 10;

HANDLE empty;
HANDLE full;
HANDLE mutex;
int in = 0, out = 0;
int buffer[BUFFER];

void print()
{
	for (int i = 0; i < BUFFER; ++i)
	{
		std::cout << buffer[i]<<' ';
	}
	std::cout << std::endl;
}
HANDLE WINAPI producer(LPVOID lpParameter)
{
	do
	{
		WaitForSingleObject(empty, INFINITE);
		WaitForSingleObject(mutex, INFINITE);
		buffer[in] = rand() % BUFFER;
		in = (++in) % BUFFER;
		std::cout << "product at " << in << std::endl;
		print();
		ReleaseSemaphore(mutex, 1, nullptr);
		ReleaseSemaphore(full, 1, nullptr);
		Sleep(1000);
	} while (true);
	return 0L;
}
HANDLE WINAPI consumer(LPVOID lpParameter)
{
	do
	{
		WaitForSingleObject(full, INFINITE);
		WaitForSingleObject(mutex, INFINITE);
		buffer[out] = -1;
		out = (out + 1) % BUFFER;
		std::cout << "consume at " << out << std::endl;
		print();
		ReleaseSemaphore(mutex, 1, nullptr);
		ReleaseSemaphore(empty, 1, nullptr);
		Sleep(1000);
	} while (true);
	return 0L;
}

int main()
{
	srand((unsigned)time);
	for (int i = 0; i < BUFFER; ++i)
	{
		buffer[i] = -1;
	}
	DWORD	DW;
	empty = CreateSemaphore(nullptr, BUFFER, BUFFER, nullptr);
	full = CreateSemaphore(nullptr, 0, BUFFER, nullptr);
	mutex = CreateSemaphore(nullptr, 1, 1, nullptr);
	HANDLE p = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)producer, nullptr, 0L, nullptr);
	HANDLE c = CreateThread(nullptr,0, (LPTHREAD_START_ROUTINE)consumer, nullptr, 0L, nullptr);
	HANDLE p1 = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)producer, nullptr, 0L, nullptr);
	HANDLE c1 = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)consumer, nullptr, 0L, nullptr);
	WaitForSingleObject(p, INFINITE);
	WaitForSingleObject(c, INFINITE);
	WaitForSingleObject(p1, INFINITE);
	WaitForSingleObject(c1, INFINITE);
	return 0;
}
