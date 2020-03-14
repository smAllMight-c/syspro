#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>

void count(char *cm,char *file){
    char cd;
    int fn =open(file,O_RDONLY);
    int lineCount=0,wordCount=0,charCount=0;

    while(read(fn,&cd,1)>0){
        if(cd=='\n')
        lineCount++;
       else if(cd==' ')
        wordCount++;
        else
        charCount++;        
    }
    if(strcmp(cm,"c")==0){
        printf("The number of characters in the file are %d\n",charCount);
    }
    if(strcmp(cm,"w")==0){
        printf("The number of words in the file are %d\t",wordCount);
    }
    if(strcmp(cm,"l")==0){
        printf("The number of lines in the file are %d\n",lineCount);
    }
}

int main(void){
    char cmd[80],op1[20],op2[20],op3[30];
    while(1){
        printf("\n MyShell $ ");
        gets(cmd);
        int pid=fork();
        if(pid==-1){
            printf("Error\n");
        }
        else if(pid > 1){
            wait(NULL);
        }
        else{

        int n=sscanf(cmd,"%s %s %s",op1,op2,op3);
        if(strcmp(op1,"count")==0){
            count(op2,op3);
            exit(0);
        }

        }
    }
}