#include<stdio.h>

struct process
{
	int pid;
	int cp;
	int wt,ct,bt;
}p[10];

int main(void)
{
	int i,j,n,awt=0,att=0,tc=2,ct=0,flag=1;
	float awtf,attf;

	printf("\nEnter the No of Processes : ");
	scanf(" %d",&n);
	printf("\nEnter the Burst time of each Process : ");
	for(i=0;i<n;++i)
	{
		printf("\nP%d : ",i);
		scanf(" %d",&p[i].bt);
		p[i].pid=i;
		p[i].wt=0;
		p[i].ct=0;
		p[i].cp=0;
	}
	
	p[0].wt=0;
	p[0].ct=0;
	att=0;
	i=0;
	printf("\nOrder of Scheduling :-\n");
	while(flag==1)
	{
		if(p[i].cp<p[i].bt)
		{
			awt=awt+(ct-p[i].wt);
			if((p[i].cp+tc)>p[i].bt)
			{
				p[i].cp+=tc;
				ct=ct+p[i].cp-p[i].bt;
			}
			else
			{
				p[i].cp+=tc;
				ct+=tc;
			}
			p[i].wt=ct;
			printf("-> P%d",p[i].pid);
		}
		i=(i+1)%n;
		flag=0;
		for(j=0;j<n;++j)
			if(p[j].cp<p[j].bt)
				flag=1;
	}
	for(i=0;i<n;++i)
		att+=p[i].wt;
	attf=((float)att)/n;
	awtf=((float)awt)/n;
	printf("\nThe Average Waiting Time is  : %f",awtf);
	printf("\nThe Average Turnaround Time is  : %f\n",attf);
	return(0);
}
