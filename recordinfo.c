#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

typedef struct recoinfo{       
	char name[10];
	int size;
}recoinfo;

int ifd; 
ssize_t cin;
char list[1024];

int records(int);

int main(int argc,char **argv)
{	printf("filename\t  size(Byte)\n\n");
	if(argc != 2 ){
		printf("can't disply records info ");
		return -1;
	}
	ifd=open(argv[1],O_RDONLY);
	int Total = records(ifd);
	printf("\n");
	printf("total records on disk is %d\n",Total);
	close(ifd);
	return (0);
}

int records(int ifd)
{	recoinfo *f1;int Rcount=0;
	char buff[1];
	while(1){
		cin=read(ifd,&buff,1);
		if(buff[0]==0x0){
			if(Rcount==0)
			{
				printf("record  not found\n");
			}
			break;
		}
		Rcount++;		
		lseek(ifd,-1,SEEK_CUR);
		f1=(recoinfo *)malloc(sizeof(recoinfo));
		read(ifd,f1,sizeof(recoinfo));
		fprintf(stdout,"%s\t",f1->name);
		fprintf(stdout,"   %d\n",f1->size);	
		lseek(ifd,(f1->size),SEEK_CUR);
	}	
	return Rcount;
}

