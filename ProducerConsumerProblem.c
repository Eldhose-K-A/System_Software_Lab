#include<stdio.h>
#include<pthread.h>

#define N 5

int f,r,BUFFER[N];

//---------------------------------------------------------
struct semaphore_variable{
	int value;
}full,empty,mutex;

void wait(struct semaphore_variable *lock)
{
	while(lock->value<=0);
	lock->value--;
}

void signal(struct semaphore_variable *lock)
{
	lock->value++;
}

void init(struct semaphore_variable *lock,int v)
{
	lock->value=v;
}
//---------------------------------------------------------
void *producer()
{
	int lc=1,sc=1,value=1000;
	printf("\nProducer Thread Created!.......");
	while(1)
	{
		wait(&empty);
		wait(&mutex);
		printf("\nProducer produced value %d and added it to BUFFER",value);
		r=(r+1)%N;
		BUFFER[r]=value++;
		if((r+1)%N==f)
			printf("\nBUFFER Full!.......");
		signal(&mutex);
		signal(&full);
		lc++;
		if(lc==8)
		{
			sc=(sc>5)?1:7;
			lc=1;
		}
		sleep(sc);
	}
}
//---------------------------------------------------------
void *consumer()
{
	int lc=1,sc=7;
	printf("\nConsumer Thread Created!.......");
	while(1)
	{
		wait(&full);
		wait(&mutex);
		printf("\nConsumer consumed value %d from BUFFER!.......",BUFFER[f]);
		f=(f+1)%N;
		if((r+1)%N==f)
			printf("\nBUFFER Empty!........");
		signal(&mutex);
		signal(&empty);
		lc++;
		if(lc==8)
		{
			sc=(sc>5)?1:7;
			lc=1;
		}
		sleep(sc);
	}
}
//----------------------------------------------------------
int main(void)
{
	pthread_t t1,t2;
	
	f=0; r=-1;
	
	init(&full,0);
	init(&empty,N);
	init(&mutex,1);

	pthread_create(&t1,NULL,producer,NULL);
	pthread_create(&t2,NULL,consumer,NULL);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	return(0);
}
