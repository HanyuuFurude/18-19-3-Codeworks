#include <stdio.h>
#include <pthread.h>
#include <iostream>
const int BUFFER =10;

int in = 10;
int out = 0;
int buffer[BUFFER];

void print()
{
	for (int i = 0; i < BUFFER; ++i)
	{
		printf("%d \t",buffer[i]);
	}
	printf("\n");
}
void* Lconsumer(void* arg)
{
	std::cout<<"a"<<std::endl;
	std::cout<<getpid()<<"\n";
	return nullptr;
}
void* Lproducer(void* arg)
{
	std::cout<<"b"<<std::endl;
	std::cout<<getpid()<<"\n";
	return nullptr;
}
int main()
{
	pthread_t c;
	pthread_t p;
	pthread_create(&c,NULL,Lconsumer,NULL);
	pthread_create(&p,NULL,Lproducer,NULL);
	printf("HanyuuDesu");
	pthread_join(c,NULL);
	pthread_join(p,NULL);
	return 0;
}