#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

void typeline(char *n,char *s){
    int fn;
    char fname[20];
    char c;
    strcpy(fname,s);
    fn=open(fname,O_RDONLY);
    if(fn==0){
        printf("File not found");
        return;
    }
    if(strcmp(n,"a")==0){
        while(read(fn,&c,1)>0){
            printf("%c",c);
        }
        close(fn);
        return;

    }
    int num=atoi(n);
    if(num>0){
        int i=0;
        while(read(fn,&c,1)>0){
            if(c =='\n'){
                i++;
            }
            if(i==num){
                break;
            }
            printf("%c",c);
        }
    }

    if(num<0){
        int i=0,j=0;
        while(read(fn,&c,1)>0){
            if(c=='\n'){
                i++;
            }
        }
        int fr=open(fname,O_RDONLY);
        while(read(fr,&c,1)>0){
            if(c=='\n'){
                j++;
            }
            if(i==(j-num)){
                break;
            }
        }
        while(read(fr,&c,1)>0){
            printf("%c",c);
        }
    }

}

int main(void){
    char cmd[80],op1[20],op2[20],op3[20];
    int n,pid;
    while(1){
        printf("\n MyShell $ ");
        gets(cmd);
        n=sscanf(cmd,"%s %s %s",op1,op2,op3);
        pid=fork();
        if(pid==-1){
            printf("Error\n");
        }
        else if(pid>0){
            wait(NULL);
        }
        else{
            if(strcmp(op1,"typeline")==0){
                typeline(op2,op3);
                exit(0);
            }
        }
    }
}