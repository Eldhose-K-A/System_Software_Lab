#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct filenode {
	char name[20];
	struct filenode *next;
}*newfile,*tfile,*t2file;
struct dirnode {
	char name[20];
	struct filenode *filelist;
	struct dirnode *next,*parent,*subdirlist;
}*tmpdir,*newdir,*rootdir,*pwd,*tmp2dir;


void createdir()
{
	char nametmp[20];
	
	scanf(" %s",nametmp);
	tmpdir=pwd->subdirlist;
	newdir=NULL;
	newdir=(struct dirnode *)malloc(sizeof(struct dirnode));
	newdir->next=newdir->subdirlist=NULL;
	newdir->filelist=NULL;
	newdir->parent=pwd;
	strcpy(newdir->name,nametmp);
	if(pwd->subdirlist==NULL)
	{
		pwd->subdirlist=newdir;
		printf("Directory Added!....");
		return;
	}
	while(tmpdir->next!=NULL)
	{
		if(strcmp(tmpdir->name,nametmp)==0)
		{	
		  printf("Directory already exists!......");
		  free(newdir);
		  return;
		}
		tmpdir=tmpdir->next;
	}
	if(strcmp((pwd->subdirlist)->name,nametmp)==0)
	{	
	  printf("Directory already exists!......");
	  free(newdir);
	  return;
	}
	tmpdir->next=newdir;
	printf("Directory Added!.....");
}
void touchfile()
{
	char nametmp[20];
	nametmp[0]='\0';
	scanf(" %s",nametmp);
	tfile=pwd->filelist;
	newfile=(struct filenode *)malloc(sizeof(struct filenode));
	newfile->next=NULL;
	strcpy(newfile->name,nametmp);
	if(pwd->filelist==NULL)
	{
		pwd->filelist=newfile;
		printf("File Added!....");
		return;
	}
	while(tfile->next!=NULL)
	{
		if(strcmp(tfile->name,nametmp)==0)
		{	
		  printf("File already exists!......");
		  free(newfile);
		  return;
		}
		tfile=tfile->next;
	}
	if(strcmp((pwd->filelist)->name,nametmp)==0)
	{	
	  printf("File already exists!......");
	  free(newfile);
	  return;
	}
	tfile->next=newfile;
	printf("File Added!.....");
}

void beautify(int v)
{
	int g1;
	printf("\n\e[34m     ");
	for(g1=1;g1<(v-1);++g1)
		printf("|    ");
	for(;g1<v;++g1)
		printf("\u2514--->");
	printf("\e[0m");
}
void listdir(struct dirnode *cr,int spaceval)
{
	struct dirnode *var;
	struct filenode *var2;
	if(cr!=NULL)
	{
		var2=cr->filelist;
		if(spaceval>=2)
			beautify(spaceval);
		else
			printf("\n     ");
		printf("Directory : %s",cr->name);
		while(var2!=NULL)
		{
			beautify(spaceval+1);
			printf("File : %s",var2->name);
			var2=var2->next;
		}
		var=cr->subdirlist;
		while(var!=NULL)
		{
			listdir(var,spaceval+1);
			var=var->next;
		}
	}
}

struct filenode *findfile(struct dirnode *cr,char *sname)
{
	int k;
	struct filenode *rtval;
	struct dirnode *var;
	if(cr!=NULL)
	{
		tfile=cr->filelist;
		while(tfile!=NULL)
		{
			if(strcmp(sname,tfile->name)==0)
			{
				return(tfile);
			}
			tfile=tfile->next;
		}
		var=cr->subdirlist;
		while(var!=NULL)
		{
			rtval=findfile(var,sname);
			if(rtval!=NULL) return(rtval);
			var=var->next;
		}
	}
        return(NULL);
}

void removedir(struct dirnode *cr)
{
	int k;
	struct dirnode *var;
	if(cr!=NULL)
	{
		tfile=cr->filelist;
		while(tfile!=NULL)
		{
			printf("%s File of %s deleted\n",tfile->name,cr->name);
			t2file=tfile;
			free(t2file);
			tfile=tfile->next;
		}
		var=cr->subdirlist;
		while(var!=NULL)
		{
			removedir(var);
			tmpdir=var;
			var=var->next;
			printf("%s Directorty of %s deleted\n",tmpdir->name,cr->name);
			free(tmpdir);
		}
	}
}

void removefile()
{
	char namefile[20];
	scanf(" %s",namefile);
	tfile=pwd->filelist;
	if(tfile==NULL)
	{
		printf("Directory Already Empty!....");
		return;
	}
	t2file=NULL;
	while(tfile!=NULL)
	{
		if(strcmp(tfile->name,namefile)==0)
		{
			if(t2file==NULL)
			{
				pwd->filelist=tfile->next;
				printf("File Deleted!.....");
				free(tfile);
				return;
			}
			t2file->next=tfile->next;
			printf("File Deleted!.......");
			free(tfile);
			return;
		}
		t2file=tfile;
		tfile=tfile->next;
	}
	printf("File Not Found!.....");
}

void printpath(struct dirnode *cr)
{
	if(cr!=NULL)
	{
		if(cr!=rootdir)
		{
			printpath(cr->parent);
			printf("/%s",cr->name);
		}
		else
			printf("%s",cr->name);
	}
}

int main(void)
{
	int ch;
	char cmd[10],findname[20];
	tmpdir=newdir=rootdir=pwd=NULL;
	newfile=tfile=NULL;

	rootdir=(struct dirnode *)malloc(sizeof(struct dirnode));
	rootdir->next=rootdir->parent=rootdir->subdirlist=NULL;
	rootdir->filelist=NULL;
	pwd=rootdir;

	printf("\nEnter the name of root Directory : ");
	scanf(" %s",rootdir->name);
	while(1)
	{
		printf("\e[31m\n>>>\e[0m\e[32m");
		printpath(pwd);
		printf("\e[0m\e[31m $\e[0m ");
		scanf(" %s",cmd);
		if(strcmp(cmd,"exit")==0)
			return 0;
		else if(strcmp(cmd,"mkdir")==0)
			createdir();
		else if(strcmp(cmd,"ls")==0)
			listdir(pwd,1);
		else if(strcmp(cmd,"touch")==0)
			touchfile();
		else if(strcmp(cmd,"rm")==0)
			removefile();
		else if(strcmp(cmd,"help")==0)
		{
			printf("\n\tCOMMAND LIST");
			printf("\nls\t- To list the directory contents");
			printf("\nfind\t- To search a file");
			printf("\ntouch\t- To create a file");
			printf("\nmkdir\t- To make a directory");
			printf("\nrmdir\t- To remove a directory");
			printf("\nrm\t- To remove a file");
			printf("\ncd\t- To change directory");
			printf("\nexit\t- To exit the simulation");
		}
		else if(strcmp(cmd,"find")==0)
		{
			scanf(" %s",findname);
			if(findfile(pwd,findname)!=NULL)
				printf("File Found!.....");
			else
				printf("File Not Found!.....");
		}
		else if(strcmp(cmd,"cd")==0)
		{
			scanf(" %s",findname);
			if(strcmp(findname,"..")==0)
			{
				if(pwd->parent!=NULL)
				{
					pwd=pwd->parent;
					printf("pwd changed!.....");
				}
				else
					printf("Already on Root Directory!.....");
			}
			else
			{
				tmpdir=pwd->subdirlist;
				while(tmpdir!=NULL)
				{
					if(strcmp(findname,tmpdir->name)==0)
						break;
					tmpdir=tmpdir->next;
				}
				if(tmpdir==NULL)
					printf("Directory Not found!....");
				else
				{
					pwd=tmpdir;
					printf("pwd changed!.....");
				}
			}
		}
		else if(strcmp(cmd,"rmdir")==0)
		{
			scanf(" %s",findname);
			tmpdir=pwd->subdirlist;
			tmp2dir=NULL;
			while(tmpdir!=NULL)
			{
				if(strcmp(findname,tmpdir->name)==0)
					break;
				tmp2dir=tmpdir;
				tmpdir=tmpdir->next;
			}
			if(tmpdir==NULL)
				printf("Directory Not found!....");
			else if(tmp2dir==NULL)
			{
				pwd->subdirlist=tmpdir->next;
				newdir=tmpdir;
				removedir(newdir);
				printf("%s Directory Deleted!.......",newdir->name);
				free(newdir);
			}
			else
			{
				tmp2dir->next=tmpdir->next;
				newdir=tmpdir;
				removedir(newdir);
				printf("%s Directory Deleted!.......",newdir->name);
				free(newdir);
			}
		}
		else
			printf("Invalid Entry!.....");
	}
}