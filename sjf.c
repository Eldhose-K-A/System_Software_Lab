#include<stdio.h>

struct process
{
	int pid;
	int wt,ct,bt;
}p[10],temp;

int main(void)
{
	int i,j,n,awt=0,att=0;
	float awtf,attf;

	printf("\nEnter the No of Processes : ");
	scanf(" %d",&n);
	printf("\nEnter the Burst time of each Process : \n");
	for(i=0;i<n;++i)
	{
		printf("P%d : ",i);
		scanf(" %d",&p[i].bt);
		p[i].pid=i;
		p[i].wt=0;
		p[i].ct=0;
	}
	for(i=0;i<n;++i)
		for(j=0;j<(n-i-1);++j)
			if((p[j].bt)>(p[j+1].bt))
			{
				temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
			}
	p[0].wt=0;
	p[0].ct=p[0].bt;
	att=p[0].bt;
	printf("\nOrder of Scheduling :-\n-> P%d",p[0].pid);
	for(i=1;i<n;++i)
	{
		p[i].wt=p[i-1].wt+p[i-1].bt;
		p[i].ct=p[i].wt+p[i].bt;
		att+=p[i].ct;
		awt+=p[i].wt;
		printf("-> P%d",p[i].pid);
	}
	attf=((float)att)/n;
	awtf=((float)awt)/n;
	printf("\nThe Average Waiting Time is  : %f",awtf);
	printf("\nThe Average Turnaround Time is  : %f\n",attf);
	return(0);
}
