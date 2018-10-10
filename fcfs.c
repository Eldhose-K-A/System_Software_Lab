#include<stdio.h>

int main(void)
{
	int i,j,n,bt[10],wt[10],ct[10],awt=0,att=0;
	float awtf,attf;

	printf("\nEnter the No of Processes : ");
	scanf(" %d",&n);
	printf("\nEnter the Burst time of each Process : \n");
	for(i=0;i<n;++i)
	{
		printf("P%d : ",i);
		scanf(" %d",&bt[i]);
	}
	wt[0]=0;
	ct[0]=bt[0];
	att=bt[0];
	for(i=1;i<n;++i)
	{
		wt[i]=wt[i-1]+bt[i-1];
		ct[i]=wt[i]+bt[i];
		att+=ct[i];
		awt+=wt[i];
	}
	attf=((float)att)/n;
	awtf=((float)awt)/n;
	printf("\nThe Average Waiting Time is  : %f",awtf);
	printf("\nThe Average Turnaround Time is  : %f\n",attf);
	return(0);
}
