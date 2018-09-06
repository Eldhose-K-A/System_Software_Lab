#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

sem_t mutex;
sem_t chopstick[5];
int status[5];

void test(int p)
{
	if((status[p]==1)&&(status[(p+1)%5]!=0)&&(status[(p+4)%5]!=0))
	{
		status[p]=0;
		sleep(2);
		printf("\nPhilosopher %d is now EATING",p+1);
		sem_post(&chopstick[p]);
	}
}

void getChopstick(int p)
{
	sem_wait(&mutex);
	status[p]=1;
	printf("\nPhilosopher %d is HUNGRY!....",p+1);
	test(p);
	sem_post(&mutex);
	sem_wait(&chopstick[p]);
	sleep(1);
}

void putChopstick(int p)
{
	sem_wait(&mutex);
	status[p]=2;
	printf("\nPhilosopher %d have finished EATING and is now THINKING",p+1);
	test((p+4)%5);
	test((p+1)%5);
	sem_post(&mutex);
}

void *mainforthread(int pno)
{
	while(1)
	{
		sleep(1);
		getChopstick(pno);
		sleep(0);
		putChopstick(pno);
	}
	
}

int main(void)
{
	pthread_t thread[5];
	int i;

	sem_init(&mutex,0,1);
	for(i=0;i<5;++i)
	{
		sem_init(&chopstick[i],0,0);
		status[i]=2;
	}
	for(i=0;i<5;++i)
		pthread_create(&thread[i],NULL,mainforthread,(void *)i);	
	for(i=0;i<5;++i)
		pthread_join(&thread[i],NULL);
	return(0);
}
