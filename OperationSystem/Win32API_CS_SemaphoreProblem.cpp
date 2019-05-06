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
		std::cout << buffer[i]<<'\t';
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
		print();
		ReleaseSemaphore(mutex, 1, nullptr);
		ReleaseSemaphore(full, 1, nullptr);
		Sleep(200);
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
		print();
		ReleaseSemaphore(mutex, 1, nullptr);
		ReleaseSemaphore(empty, 1, nullptr);
		Sleep(200);
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
    std::cout << "Hello World!\n";
	DWORD	DW;
	empty = CreateSemaphore(nullptr, BUFFER, BUFFER, nullptr);
	full = CreateSemaphore(nullptr, 0, BUFFER, nullptr);
	mutex = CreateSemaphore(nullptr, 1, 1, nullptr);
	HANDLE p = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)producer, nullptr, 0L, nullptr);
	Sleep(BUFFER * 200);
	HANDLE c = CreateThread(nullptr,0, (LPTHREAD_START_ROUTINE)consumer, nullptr, 0L, nullptr);
	WaitForSingleObject(p, INFINITE);
	WaitForSingleObject(c, INFINITE);
	return 0;
}
