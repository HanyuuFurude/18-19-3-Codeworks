#include"banker.h"
extern Container* container;
//struct Func
//{
//	void (*request)(unsigned, ResourceRow);
//	void (*release)(unsigned);
//	void* ptr;
//	void (*print)();
//};

int main()
{
	srand((int)time(0));
	container = new Container();
	for (unsigned i = 0; i < 4; ++i)
		container->pushProcess(new ProcessCol());
	container->avilable.res[0] = 10;
	container->avilable.res[1] = 10;
	container->avilable.res[2] = 20;
	container->avilable.res[3] = 9;
	HANDLE* hdl = new HANDLE[container->processCount];
	for (unsigned i = 0; i < container->processCount; ++i)
	{
		//Func func;
		//func.print = &print;
		//func.request = &HanyuuRequests;
		//func.release = &HanyuuRelease;
		//hdl[i]=container->list[i]->start(func);
		hdl[i] = container->list[i].start();
	}
	for (unsigned i = 0; i < container->processCount; ++i)
	{
		WaitForSingleObject(hdl[i],INFINITE);
	}
	Sleep(40000);
}