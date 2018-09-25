#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *optabfile,*sourcecode,*intermediate,*symtabfile;

int opcheck(char *s1)
{
	char opcodestr[20],mneumonic[20];
	optabfile=NULL;
	optabfile=fopen("OPTAB.txt","r");
	if(optabfile==NULL)
		return -2;
	while(!feof(optabfile))
	{
		fscanf(optabfile," %s",mneumonic);
		fscanf(optabfile," %s",opcodestr);
		if(strcmp(mneumonic,s1)==0)
		{
			fclose(optabfile);
			optabfile=NULL;
			return(1);
		}
		if(feof(optabfile))
			break;
	}
	fclose(optabfile);
	optabfile=NULL;
	return(0);
}
int symcheck(char *s1,int loc)
{
	char label[20],location[20];
	symtabfile=NULL;
	symtabfile=fopen("SYMTAB.txt","r+");
	if(symtabfile==NULL)
	{
		symtabfile=fopen("SYMTAB.txt","w");
		fprintf(symtabfile,"%20s",s1);
		fprintf(symtabfile," %7d\n",loc);
		fclose(symtabfile);
		symtabfile=NULL;
		return(0);
	}
	while(!feof(symtabfile))
	{
		fscanf(symtabfile," %s",label);
		fscanf(symtabfile," %s",location);
		if(strcmp(label,s1)==0)
		{
			fclose(symtabfile);
			symtabfile=NULL;
			return(1);
		}
		if(feof(symtabfile))
			break;
	}
	fprintf(symtabfile,"%20s",s1);
	fprintf(symtabfile," %7d\n",loc);
	fclose(symtabfile);
	symtabfile=NULL;
	return(0);
}
int main(void)
{
	int StartAddress=0,LOCCTRp=0,LOCCTR=0,errorflag=0,c=0,k=0;
	char labelfield[20],opcodefield[20],operandfield[20];

	optabfile=sourcecode=intermediate=symtabfile=NULL;
	
	sourcecode=fopen("input.txt","r");
	if(sourcecode==NULL)
		return(0);
	intermediate=fopen("intermediate.txt","w");
	if(sourcecode==NULL)
	{
		fclose(sourcecode);
		return(0);
	}

	fscanf(sourcecode," %s %s %s",labelfield,opcodefield,operandfield);

	if(strcmp(opcodefield,"START")==0)
	{
		StartAddress=atoi(operandfield);
		LOCCTR=StartAddress;
		fprintf(intermediate,"%7d %10s %10s %20s\n",LOCCTR,labelfield,opcodefield,operandfield);
		if(!feof(sourcecode))
		{
			fscanf(sourcecode," %s %s %s",labelfield,opcodefield,operandfield);
		}
	}
	
	while(!feof(sourcecode))
	{
		if(*(labelfield)!='.')
		{
			if(strcmp(labelfield,"**")!=0)
			{
				if(symcheck(labelfield,LOCCTR)==1)
					errorflag=1;
			}
			if(opcheck(opcodefield)==1)
			{
				LOCCTRp=LOCCTR;
				if(strcmp(opcodefield,"WORD")==0)
				{
					LOCCTR+=3;
				}
				else if(strcmp(opcodefield,"RESW")==0)
				{
					LOCCTR=LOCCTR+(3*atoi(operandfield));
				}
				else if(strcmp(opcodefield,"RESB")==0)
				{
					LOCCTR=LOCCTR+atoi(operandfield);
				}
				else if(strcmp(opcodefield,"BYTE")==0)
				{
					LOCCTR=LOCCTR+1;
					k=c=0;
					while(*(operandfield+c)!='\0')
					{
						if(*(operandfield+c)==';')
							k=k+1;
						c=c+1;
					}
					if(k>=2)
						LOCCTR=LOCCTR+k-1;
				}
				else if(strcmp(opcodefield,"END")==0)
				{
					break;
				}
				else
				{
					LOCCTR=LOCCTR+3;			
				}
			}
			else
				errorflag=2;
		}
		fprintf(intermediate,"%7d %10s %10s %20s\n",LOCCTRp,labelfield,opcodefield,operandfield);
		LOCCTRp=LOCCTR;
		if(!feof(sourcecode))
		{
			fscanf(sourcecode," %s %s %s",labelfield,opcodefield,operandfield);
		}
		else
			break;
	}
	
	fclose(sourcecode);
	fprintf(intermediate,"%7d %10s %10s %20s\n",LOCCTRp,labelfield,opcodefield,operandfield);
	fprintf(intermediate,"Program Length : %d\n",LOCCTR-StartAddress);
	fclose(intermediate);
	printf("\nCompleted Parsing\n");
	return(0);
}
