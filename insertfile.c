#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>

ssize_t cin,cout;
char list[1024];

int  insertf(int,int,char *);

typedef struct fileinfo
{
	char name[10];
	int size;     
}fileinfo;

int main(int argc,char **argv)
{  	int ofd,ofd1;
	if(argc !=3 )
	{
		printf("can't inserted file \n");
		return -1;
	}
	ofd=open(argv[1],O_RDONLY);
	ofd1=open(argv[1],O_WRONLY);
	insertf(ofd,ofd1,argv[2]);
	close(ofd);
	close(ofd1);
	return (0);
}

int insertf(int ofd,int ofd1,char *filename)
{	int ifd,Fsize;
	fileinfo *f1; 
	char buff[1];
	ifd=open(filename,O_RDONLY);	
	//fprintf(stdout,"%s",filename);  
	f1=(fileinfo *)malloc(sizeof(fileinfo));
	while(1)
	{
		cin=read(ofd,&buff,1);
		if(buff[0]==0x00)  
		{	fprintf(stdout,"%d",buff[0]);
			break;
		}
		lseek(ofd,-1,SEEK_CUR);
		read(ofd,f1,sizeof(fileinfo));
		lseek(ofd,f1->size,SEEK_CUR);
		fprintf(stdout,"%d",f1->size);
		lseek(ofd1,f1->size + sizeof(fileinfo),SEEK_CUR);
	}		
	f1=(fileinfo *)malloc(sizeof(fileinfo));
	strcpy((f1->name),filename);	
	lseek(ifd,0L,SEEK_SET);	
	Fsize=lseek(ifd,0L,SEEK_END);
	fprintf(stdout,"%d",f1->size);
	f1->size=Fsize;
	lseek(ifd,0L,SEEK_SET);
	write(ofd1,f1,sizeof(fileinfo));
	cin=read(ifd,&list,1024);
	while( cin > 0)
	{
		cout = write (ofd1, &list, (ssize_t) cin);
		if(cout != cin)
		{
			printf ("error copying file");
			return -1;
		}
		cin = read (ifd, &list, 1024);
	}
	close(ifd);
}		
