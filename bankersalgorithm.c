#include<stdio.h>
#include<stdlib.h>

int Pmax,Rmax;
int *pstatus;
int *maxres,*available,*allocation,*need,*maxmatrix;
int sequence[20];

int less(int *s1,int *s3,int *s2)
{
	int k;
	if(s3==NULL){
		for(k=0;k<Rmax;++k)
		{
			if(*(s1+k)>*(s2+k))
				return 0;
		}
		return 1;
	}
	for(k=0;k<Rmax;++k)
	{
		if((*(s1+k)+*(s3+k))>*(s2+k))
		{
			return(0);
		}
	}
	return(1);
}

int safety_algorithm()
{
	int *finish,*work;
	int k1,k2,c=0,flag=0;
	finish=work=NULL;
	finish=(int *)malloc(sizeof(int)*Pmax);
	work=(int *)malloc(sizeof(int)*Rmax);
	
	for(flag=0;flag<Pmax;++flag)
		*(finish+flag)=0;
	for(flag=0;flag<Rmax;++flag)
		*(work+flag)=*(available+flag);
	do
	{
		flag=0;
		for(k1=0;k1<Pmax;++k1)
		{
			if((*(finish+k1)==0)&&(less((need+(k1*Rmax)),NULL,work)==1))
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			for(k2=0;k2<Rmax;++k2)
				*(work+k2)=*(work+k2)+*(allocation+(k1*Rmax)+k2);
			*(finish+k1)=1;
			sequence[c]=k1;
			c++;
		}
		
	}while(flag==1);
	for(k1=0;k1<Pmax;++k1)
	{
		if(*(finish+k1)==0)
		{
			return(0);
		}
	}
	return(1);
}

void request_Resource()
{
	int i1,fl,j1,pid,*reqtmp;
	fl=1;
	printf("\nEnter the Process No : ");
	scanf("%d",&pid);
	if(*(pstatus+pid)==1)
	{
		printf("\nProcess Already Completed!.....");
		return;
	}
	reqtmp=NULL;
	reqtmp=(int *)malloc(sizeof(int)*Rmax);
	printf("\nEnter the Request Resource vector : ");
	for(i1=0;i1<Rmax;++i1)
		scanf(" %d",(reqtmp+i1));
	if(less(reqtmp,(allocation+(pid*Rmax)),(maxmatrix+(pid*Rmax)))==0)
	{
		printf("Requested Excess than Needed!......");
		return;
	}
	if(less(reqtmp,NULL,available)==0)
	{
		printf("Request Resources Not available!.......");
		free(reqtmp);
		reqtmp=NULL;
		return;
	}
	for(i1=0;i1<Rmax;++i1)
	{
		*(allocation+(pid*Rmax)+i1)=*(allocation+(pid*Rmax)+i1)+*(reqtmp+i1);
		*(need+(pid*Rmax)+i1)=*(need+(pid*Rmax)+i1)-*(reqtmp+i1);
		if(*(need+(pid*Rmax)+i1)!=0)
			fl=0;
		*(available+i1)=*(available+i1)-*(reqtmp+i1);
	}
	if(safety_algorithm()==0)
	{
		printf("The Request can cause a Deadlock !.......");
		for(i1=0;i1<Rmax;++i1)
		{
			*(allocation+(pid*Rmax)+i1)=*(allocation+(pid*Rmax)+i1)-*(reqtmp+i1);
			*(need+(pid*Rmax)+i1)=*(need+(pid*Rmax)+i1)+*(reqtmp+i1);
			*(available+i1)=*(available+i1)+*(reqtmp+i1);
		}
		free(reqtmp);
		return;
	}
	printf("The Request can be serviced !........");
	printf("\nThe possible safe sequence is :- ");
	for(i1=0;i1<Pmax;++i1)
	{
		printf(" P%d,",sequence[i1]);
	}
	if(fl==1)
	{
		printf("\nProcess %d Completed!........",pid);
		*(pstatus+pid)=1;
		for(i1=0;i1<Rmax;++i1)
		{
			*(need+(pid*Rmax)+i1)=*(allocation+(pid*Rmax)+i1);
			*(available+i1)=*(available+i1)+*(allocation+(pid*Rmax)+i1);
			*(allocation+(pid*Rmax)+i1)=0;
			
		}
	}
}


int main(void)
{
	int i,j,ch;
	maxres=NULL;
	allocation=need=available=NULL;
	maxmatrix=NULL;

	printf("\nEnter the No of Processes : ");
	scanf("%d",&Pmax);
	printf("Enter the No of Resources : ");
	scanf("%d",&Rmax);
	
	pstatus=(int *)malloc(sizeof(int)*Pmax);
	//res=(int *)malloc(sizeof(int)*Rmax);
	maxres=(int *)malloc(sizeof(int)*Rmax);
	available=(int *)malloc(sizeof(int)*Rmax);
	allocation=(int *)malloc(sizeof(int)*Rmax*Pmax);
	need=(int *)malloc(sizeof(int)*Rmax*Pmax);
	maxmatrix=(int *)malloc(sizeof(int)*Rmax*Pmax);
	for(i=0;i<Pmax;++i)
		*(pstatus+i)=0;
	printf("\nEnter the Maximum instance of :-\n");
	for(i=0;i<Rmax;++i)
	{
		printf("\tResource %d : ",i+1);
		scanf("%d",(maxres+i));
		*(available+i)=*(maxres+i);
	}
	
	for(i=0;i<Pmax;++i)
	{
		printf("Enter the Max Resource vector of Process %d :- ",i);
		for(j=0;j<Rmax;++j)
		{
			scanf(" %d",(maxmatrix+(i*Rmax)+j));
			*(need+(i*Rmax)+j)=*(maxmatrix+(i*Rmax)+j);
		}
	}
	
	for(i=0;i<Pmax;++i)
	{
		printf("\nEnter the Allocation vector for process %d :- ",i);
		for(j=0;j<Rmax;++j)
		{
			scanf(" %d",(allocation+(i*Rmax)+j));
			*(need+(i*Rmax)+j)=*(need+(i*Rmax)+j)-*(allocation+(i*Rmax)+j);
			*(available+j)=*(available+j)-*(allocation+(i*Rmax)+j);
		}
				
	}

	if(safety_algorithm()==1)
	{
		printf("\nThe System is Currently in a Safe State");
		printf("\nThe possible safe sequence is :- ");
		for(i=0;i<Pmax;++i)
		{
			printf(" P%d,",sequence[i]);
		}
		printf("\nAvailable Resources : ");
		for(i=0;i<Rmax;++i)
			printf(" R%d : %d, ",i+1,*(available+i));
	}
	else
	{
		printf("\nThe System is Now in an Unsafe State");
	}

	while(1)
	{
		printf("\nMain Menu\n1.Request\n2.Exit\nYour Choice : ");
		scanf(" %d",&ch);
		switch(ch)
		{
			case 1:	request_Resource();
				printf("\nAvailable Resources : ");
				for(i=0;i<Rmax;++i)
					printf(" R%d : %d, ",i+1,*(available+i));
				break;
			case 2: return(0);
			default: printf("Invalid Choice!......");
		}
	}		
}
