#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

const int BUFFER = 10;

sem_t empty, full;
pthread_mutex_t mutex;
int in = 0;
int out = 0;
int buffer[BUFFER];

void print()
{
	for (int i = 0; i < BUFFER; ++i)
	{
		printf("%d ", buffer[i]);
	}
	printf("\n");
}
void *Lproducer(void *arg)
{
	do
	{
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		std::cout << "product at " << in<<std::endl;
		buffer[in] = rand() % BUFFER;
		in = (++in) % BUFFER;
		print();
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
		sleep(1);
	} while (true);
	return NULL;
}
void *Lconsumer(void *arg)
{
	do
	{
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		std::cout << "consumer at" << out<<std::endl;
		buffer[out] = -1;
		out = (++out) % BUFFER;
		print();
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
		sleep(1);
	} while (true);
	return NULL;
}
int main()
{
	for (int i = 0; i < BUFFER; ++i)
	{
		buffer[i] = -1;
	}
	pthread_t c,c1;
	pthread_t p,p1;
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, BUFFER);
	pthread_create(&c, NULL, Lconsumer, NULL);
	pthread_create(&c, NULL, Lconsumer, NULL);
	pthread_create(&p, NULL, Lproducer, NULL);
	pthread_create(&p, NULL, Lproducer, NULL);
	pthread_join(c, NULL);
	pthread_join(p, NULL);
	pthread_join(c1, NULL);
	pthread_join(p1, NULL);
	return 0;
}