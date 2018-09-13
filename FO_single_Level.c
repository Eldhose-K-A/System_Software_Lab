#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int File_count;
char dir_name[20];

struct dir{
	char filename[20];
	struct dir *next;
}*dirroot;

int main(void)
{
	int ch,flg=0;
	char tmp[20];
	struct dir *t1,*t2;
	File_count=0;
	dirroot=t1=t2=NULL;
	printf("\nEnter the Directory Name : ");
	scanf(" %s",dir_name);
	while(1)
	{
		printf("\nMain Menu\n1.Create file\n2.Delete File\n3.List\n4.Search\n5.Exit");
		printf("\nEnter Your choice : ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1 : printf("Enter file Name : ");
				 scanf(" %s",tmp);
				 t1=dirroot;
				 t2=(struct dir *)malloc(sizeof(struct dir));
				 strcpy(t2->filename,tmp);
				 t2->next=NULL;
				 if(t1==NULL)
				 {
					dirroot=t2;
					printf("File Created!.....");
				 }
				 else
				 {
					flg=1;
					while(t1->next!=NULL)
					{
						if(strcmp(t1->filename,tmp)==0) flg=0;
						t1=t1->next;
					}
					if(strcmp(t1->filename,tmp)==0) flg=0;
					if(flg==0)
					{
						printf("File Already Exists!......");
						free(t2);
					}
					else
					{
						t1->next=t2;
						printf("\nFile Created!......");
					}
				 }
				 break;
			case 2 : if(dirroot!=NULL)
				 {
					printf("Enter file Name : ");
				 	scanf(" %s",tmp);
				 	t1=dirroot;
				 	flg=0;
					t2=NULL;
					while(t1!=NULL)
					{
						if(strcmp(t1->filename,tmp)==0)
						{
							flg=1;
							break;
						}
						t2=t1;
						t1=t1->next;
					}
					if(flg==1)
					{
						if(t2==NULL)
						{
							dirroot=t1->next;
							free(t1);
							printf("File Deleted!.....");
						}
						else
						{
							t2->next=t1->next;
							free(t1);
							printf("\nFile Deleted!.....");
						}
				 	}
					else
						printf("File Not Found!......");
				}
				else
					printf("Directory Empty!.......");
				break;
			case 3 : if(dirroot!=NULL)
				 {
				 	t1=dirroot;
					printf("\n%s\n",dir_name);
					while(t1!=NULL)
					{
						printf("\t%s\n",t1->filename);
						t1=t1->next;
					}
				}
				else
					printf("Directory Empty!.......");
				break;
			case 4 : if(dirroot!=NULL)
				 {
					printf("Enter file Name : ");
				 	scanf(" %s",tmp);
				 	t1=dirroot;
				 	flg=0;
					while(t1!=NULL)
					{
						if(strcmp(t1->filename,tmp)==0)
						{
							flg=1;
							break;
						}
						t1=t1->next;
					}
					if(flg==1)
					{
						printf("File Found!.....");
				 	}
					else
						printf("File Not Found!......");
				}
				else
					printf("Directory Empty!.......");
				 break;
			case 5 : return 0;
			default: printf("Invalid Choice!............");
		}
	}
}
