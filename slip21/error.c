#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct sym{
    char sname[20];
    int used,defined,redeclared;
    struct sym *next;
}sym;

sym *head,*last;

void addSymbol(char *s){
    sym *new;
    new = (sym*)malloc(sizeof(sym));
    strcpy(new->sname,s);
    new->defined=0;
    new->redeclared=0;
    new->used=0;
    if(head==NULL){
        head = new;
    }
    else
    {
        last->next=new;
    }
    last=new;
    
}

sym *searchSymbol(char *s){
    sym *new;
    for(new=head;new!=NULL;new=new->next){
        if(strcmp(new->sname,s)==0){
            return new;
        }
    }
    return NULL;
}

void displayError(){
    sym *new;
    for(new=head;new!=NULL;new=new->next){
        if(new->used==1 && new->defined==0){
            printf("Symbol %s used but not defined\n",new->sname);
        }
        if(new->defined==1 && new->used==0){
            printf("Symbol %s defined but not used\n",new->sname);
        }
        if(new->redeclared==1){
            printf("Symbol %s redeclared\n",new->sname);
        }
    }
}


int main(void){

    FILE *fp;
    int n;
    char fname[20],buff[80],op1[20],op2[20],op3[20],op4[20];
    printf("Enter the file name\n");
    scanf("%s",fname);
    sym *symb;

    fp = fopen(fname,"r");

    while(fgets(buff,80,fp)!=NULL){
       n= sscanf(buff,"%s %s %s %s",op1,op2,op3,op4);

    switch (n)
    {
    case 2:
            if(strcmp(op1,"START")==0){
            }   
            else {
                if(searchSymbol(op2)==NULL){
                    addSymbol(op2);
                    symb=searchSymbol(op2);
                    symb->used=1;
                }
            }
        break;
    case 3: if(strcmp(op2,"DS")==0){
            symb=searchSymbol(op1);
            if(symb==NULL){
                addSymbol(op1);
                symb=searchSymbol(op1);
                symb->defined=1;
            }
            else{
                if(symb->defined==1){
                    symb->redeclared=1;
                }
                else
                {
                    symb->defined=1;
                }
                
            }
         }
         else{
             symb=searchSymbol(op3);
             if(symb==NULL){
                 addSymbol(op3);
                 symb=searchSymbol(op3);
                 symb->used=1;
             }
             else
             {
                 symb->used=1;
             }
             
         }
         break;
    case 4: symb=searchSymbol(op1);
            if(symb==NULL){
                addSymbol(op1);
                symb=searchSymbol(op1);
                symb->defined=1;
            }
            else
            {
                symb->redeclared=1;
            }
            
            symb=searchSymbol(op4);
            if(symb==NULL){
                addSymbol(op4);
                symb=searchSymbol(op4);
                symb->used=1;
            }
            else
            {
                symb->used=1;
            }
        default:
        break;
    }
    }

    displayError();
}


