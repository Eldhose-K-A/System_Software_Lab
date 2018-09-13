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
		printf("first Directory Added!....");
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
	printf("\nDirectory Added!.....");
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
		printf("*-");
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
	printf("\nFile Added!.....");
}


void listdir(struct dirnode *cr)
{
	int k;
	struct dirnode *var;
	if(cr!=NULL)
	{
		tfile=cr->filelist;
		printf("Directory name :- %s | Files:- ",cr->name);
		if(tfile==NULL) printf(" (empty) ");
		while(tfile!=NULL)
		{
			printf("%s, ",tfile->name);
			tfile=tfile->next;
		}
		var=cr->subdirlist;
		printf(" | SubDirectories :- ");
		if(var==NULL) printf(" (empty) ");
		while(var!=NULL)
		{
			printf("%s, ",var->name);
			var=var->next;
		}
		printf("\n");
		var=cr->subdirlist;
		while(var!=NULL)
		{
			listdir(var);
			var=var->next;
		}
	}
}

struct filenode findfile(struct dirnode *cr,char *sname)
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
			printf("%s, ",var->name);
			var=var->next;
		}
		printf("\n");
		var=cr->subdirlist;
		while(var!=NULL)
		{
			listdir(var);
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
			printf("\n%s File of %s deleted, ",tfile->name,cr->name);
			t2file=tfile;
			free(t2file);
			tfile=tfile->next;
		}
		var=cr->subdirlist;
		while(var!=NULL)
		{
			removedir(var);
			tmpdir=var;
			printf("\n%s Directorty od %s deleted, ",tmpdir->name,cr->name);
			free(tmpdir);
			var=var->next;
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

int main(void)
{
	int ch;
	char cmd[10];//ls,find touch,mkdir,rmdir,rm,cd
	tmpdir=newdir=rootdir=pwd=NULL;
	newfile=tfile=NULL;

	rootdir=(struct dirnode *)malloc(sizeof(struct dirnode));
	rootdir->next=rootdir->parent=rootdir->subdirlist=NULL;
	rootdir->filelist=NULL;
	pwd=rootdir;

	printf("\Enter the name of root Directory : ");
	scanf(" %s",rootdir->name);
	
	while(1)
	{
		printf("\nPwd :- %s",pwd->name);
		printf("\n(Commands allowded : ls, find, touch, mkdir, rmdir, rm, cd, exit)");
		printf("\n$ ");
		scanf(" %s",cmd);
		if(strcmp(cmd,"exit")==0)
			return 0;
		else if(strcmp(cmd,"mkdir")==0)
			createdir();
		else if(strcmp(cmd,"ls")==0)
			listdir(pwd);
		else if(strcmp(cmd,"touch")==0)
			touchfile();
		else if(strcmp(cmd,"rm")==0)
			removefile();
		else if(strcmp(cmd,"rmdir")==0)
		{
			tmp2dir=pwd->subdirlist;
			removedir(pwd);
		}
		else if(strcmp
		else
			printf("To be added soon!.....");
	}
}
